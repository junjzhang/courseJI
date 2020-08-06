#include "./SRHeader.h"
#include "./crc32.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h> // struct stat
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
// The size of packet would is len(header) + len(payload) = 4*4 + 1456 = 1472
#define MAX_MESSAGE_SIZE 1472

int logInfo(struct SRHeader header, FILE *fp) {
  if (header.flag == SYN) {
    fprintf(fp, "%s %u %u %u\n", "SYN", header.seq, header.len, header.crc);
    printf("%s %u %u %u\n", "SYN", header.seq, header.len, header.crc);
  } else if (header.flag == FIN) {
    fprintf(fp, "%s %u %u %u\n", "FIN", header.seq, header.len, header.crc);
    printf("%s %u %u %u\n", "FIN", header.seq, header.len, header.crc);
  } else if (header.flag == DATA) {
    fprintf(fp, "%s %u %u %u\n", "DATA", header.seq, header.len, header.crc);
    printf("%s %u %u %u\n", "DATA", header.seq, header.len, header.crc);
  } else if (header.flag == ACK) {
    fprintf(fp, "%s %u %u %u\n", "ACK", header.seq, header.len, header.crc);
    printf("%s %u %u %u\n", "ACK", header.seq, header.len, header.crc);
  } else if (header.flag == NACK) {
    fprintf(fp, "%s %u %u %u\n", "NACK", header.seq, header.len, header.crc);
    printf("%s %u %u %u\n", "NACK", header.seq, header.len, header.crc);
  }
  return 0;
}

int runSender(char *recvIP, int recvPort, int senderPort,
              unsigned int windowSize, char *fileToSend, char *logFile) {
  FILE *logfp = fopen(logFile, "w+");
  // create UDP socket.
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // use IPPROTO_UDP
  if (sockfd < 0) {
    perror("socket creation failed");
    exit(1);
  }

  // below is the same as TCP socket.
  struct sockaddr_in myAddr;
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = INADDR_ANY;
  // bind to a specific port
  myAddr.sin_port = htons(senderPort);
  bind(sockfd, (struct sockaddr *)&myAddr, sizeof(myAddr));

  struct sockaddr_in recvAddr;
  struct hostent *host = gethostbyname(recvIP);
  memcpy(&(recvAddr.sin_addr), host->h_addr, host->h_length);
  recvAddr.sin_family = AF_INET;
  recvAddr.sin_port = htons(recvPort);

  // 1. The num of packets to be sent
  // 1.1 Read file length
  struct stat statBuffer;
  size_t fileLen = 0;
  size_t numSend = 0;
  size_t divFlag = 0;
  // Read the file length
  if (stat(fileToSend, &statBuffer) < 0) {
    // Handling reding file error
    perror("Error: Can not read file\n");
    exit(-1);
  }
  fileLen = statBuffer.st_size;
  // 1.2 Calculate num of packets to be sent
  divFlag = fileLen % MAX_PAYLOAD_SIZE;
  numSend = divFlag > 0 ? (1 + (fileLen / MAX_PAYLOAD_SIZE))
                        : fileLen / MAX_PAYLOAD_SIZE;
  printf("File size is %lu, need %lu packets to send\n", fileLen, numSend);

  // 2. send
  unsigned int randSeq = 0;
  char packet[MAX_MESSAGE_SIZE];
  char msg[MAX_MESSAGE_SIZE];
  struct SRHeader header;
  memset(packet, 0, sizeof(packet));
  // 2.1 send SYN, has random seq number
  srand((unsigned)time(NULL));
  randSeq = rand();
  header.flag = SYN;
  header.seq = randSeq;
  header.len = 0;
  header.crc = crc32(NULL, 0); // without payload;
  memcpy(packet, (char *)&header, sizeof(header));
  sendto(sockfd, (void *)packet, sizeof(header), 0,
         (const struct sockaddr *)&recvAddr, sizeof(struct sockaddr_in));
  logInfo(header, logfp);
  printf("Send SYN to set up the connection\n");
  // 2.2 wait for ACK and SYN packet
  socklen_t sLen = sizeof(struct sockaddr_in);
  struct sockaddr_in siOther;
  struct SRHeader recvHeader;
  struct timeval start, stop;
  gettimeofday(&start, NULL);
  gettimeofday(&stop, NULL);

  // receive ack
  while (1) {
    if (recvfrom(sockfd, msg, MAX_MESSAGE_SIZE, MSG_DONTWAIT,
                 (struct sockaddr *)&siOther, &sLen) > 0) {
      memcpy(&recvHeader, msg, sizeof(recvHeader));
      logInfo(recvHeader, logfp);
      if (recvHeader.flag == ACK) {
        printf("Connection set up \n");
        break;
      }
    } else {
      // resend SYN
      sendto(sockfd, (void *)packet, sizeof(header), 0,
             (const struct sockaddr *)&recvAddr, sizeof(struct sockaddr_in));
      logInfo(header, logfp);
    }
    // time out for ACK
    gettimeofday(&stop, NULL);
    if ((double)(stop.tv_sec - start.tv_sec) * 1000 +
            (double)(stop.tv_usec - start.tv_usec) / 1000 >
        5000) {
      perror("Error: do not receive ACK for SYN within 5 s. Give up\n");
      fclose(logfp);
      exit(4);
    }
  }
  // 2.3 Send data
  char *buf = malloc(windowSize * MAX_MESSAGE_SIZE);
  memset(buf, 0, windowSize * MAX_MESSAGE_SIZE);
  FILE *fp = fopen(fileToSend, "r");
  // open file
  if (!fp) {
    // Handling file open error
    perror("Error: Can not read file\n");
    free(buf);
    fclose(logfp);
    fclose(fp);
    exit(-1);
  }

  unsigned int currentSeq = 0; // send 0 for initial
  unsigned int bufNum = 0;
  int endFlag = 1;
  unsigned dupCnt = 0;
  unsigned dupSeq = 0;
  size_t payloadLen = MAX_PAYLOAD_SIZE;
  gettimeofday(&start, NULL);
  while (endFlag) {
    // check if timeout
    gettimeofday(&stop, NULL);
    // if timeout, resend all buffer
    if ((double)(stop.tv_sec - start.tv_sec) * 1000 +
            (double)(stop.tv_usec - start.tv_usec) / 1000 >
        400) {
      printf(
          "No ack within 400ms, resend all packets in buffer. Start from %u\n",
          currentSeq);
      // resend
      for (unsigned int ii = 0; ii < bufNum; ii++) {
        payloadLen = ((currentSeq + ii == numSend - 1) && (divFlag > 0))
                         ? divFlag
                         : MAX_PAYLOAD_SIZE;
        sendto(sockfd, (void *)(buf + ii * sizeof(packet)),
               payloadLen + sizeof(header), 0,
               (const struct sockaddr *)&recvAddr, sizeof(struct sockaddr_in));
        struct SRHeader tempHeader;
        memcpy(&tempHeader, buf + ii * sizeof(packet), sizeof(header));
        logInfo(tempHeader, logfp);
      }
      // reset time
      gettimeofday(&start, NULL);
    }
    // send and buffer

    if ((bufNum < windowSize) && ((bufNum + currentSeq) < numSend)) {
      payloadLen = ((currentSeq + bufNum == numSend - 1) && (divFlag > 0))
                       ? divFlag
                       : MAX_PAYLOAD_SIZE;
      // form a packet
      fread(packet + sizeof(header), payloadLen, 1, fp);
      header.flag = DATA;
      header.seq = currentSeq + bufNum;
      header.len = payloadLen;
      header.crc = crc32(packet + sizeof(header), payloadLen);
      memcpy(packet, (char *)(&header), sizeof(header));
      // send
      sendto(sockfd, (void *)packet, payloadLen + sizeof(header), 0,
             (const struct sockaddr *)&recvAddr, sizeof(struct sockaddr_in));
      logInfo(header, logfp);
      // buffer the packet
      memcpy(buf + bufNum * MAX_MESSAGE_SIZE, packet, sizeof(packet));
      bufNum++;
    }
    // receive ACK
    if (recvfrom(sockfd, msg, MAX_MESSAGE_SIZE, MSG_DONTWAIT,
                 (struct sockaddr *)&siOther, &sLen) != -1) {
      memcpy(&recvHeader, msg, sizeof(recvHeader));
      logInfo(recvHeader, logfp);
      // duplicate ACK
      if ((dupCnt == 0) || (recvHeader.seq != dupSeq)) {
        dupSeq = recvHeader.seq;
        dupCnt = 1;
      } else if (recvHeader.seq == dupSeq) {
        dupCnt++;
        if (dupCnt >= 3) {
          // resend it immediately
          payloadLen = ((dupSeq == numSend - 1) && (divFlag > 0))
                           ? divFlag
                           : MAX_PAYLOAD_SIZE;
          sendto(sockfd, (void *)(buf + (dupSeq - currentSeq) * sizeof(packet)),
                 payloadLen + sizeof(header), 0,
                 (const struct sockaddr *)&recvAddr,
                 sizeof(struct sockaddr_in));
          struct SRHeader tempHeader;
          memcpy(&tempHeader, buf + (dupSeq - currentSeq) * sizeof(packet),
                 sizeof(header));
          logInfo(tempHeader, logfp);
          // reset Cnt
          dupCnt = 0;
        }
      }
      // Advance window
      if (recvHeader.flag == ACK) {
        if (recvHeader.seq > currentSeq) {
          // move buffer
          if (recvHeader.seq > currentSeq + bufNum) {
            // clear buf
            memset(buf, 0, windowSize * MAX_MESSAGE_SIZE);
            bufNum = 0;
          } else {
            char *temp = malloc(windowSize * MAX_PAYLOAD_SIZE);
            memcpy(temp, buf + (recvHeader.seq - currentSeq) * MAX_MESSAGE_SIZE,
                   (bufNum + currentSeq - recvHeader.seq) * MAX_MESSAGE_SIZE);
            memset(buf, 0, windowSize * MAX_MESSAGE_SIZE);
            memcpy(buf, temp, windowSize * MAX_MESSAGE_SIZE);
            free(temp);
            bufNum = bufNum + currentSeq - recvHeader.seq;
          }
          // advance
          currentSeq = recvHeader.seq;
          if (currentSeq > (numSend - 1))
            endFlag = 0;
        }
      }
      // reset time
      gettimeofday(&start, NULL);
    }
  }
  // Send FIN
  header.flag = FIN;
  header.seq = randSeq;
  header.len = 0;
  header.crc = crc32(NULL, 0); // without payload;
  memcpy(packet, (char *)&header, sizeof(header));
  sendto(sockfd, (void *)packet, sizeof(header), 0,
         (const struct sockaddr *)&recvAddr, sizeof(struct sockaddr_in));
  logInfo(header, logfp);
  printf("Tranmission finished: Send FIN");
  // receive ack for FIN
  while (1) {
    if (recvfrom(sockfd, msg, MAX_MESSAGE_SIZE, MSG_DONTWAIT,
                 (struct sockaddr *)&siOther, &sLen) != -1) {
      memcpy(&recvHeader, msg, sizeof(recvHeader));
      logInfo(recvHeader, logfp);
      if (recvHeader.flag == ACK) {
        printf("Receive ACK for FIN, done\n");
        break;
      }
    } else {
      // resend FIN
      sendto(sockfd, (void *)packet, sizeof(header), 0,
             (const struct sockaddr *)&recvAddr, sizeof(struct sockaddr_in));
      logInfo(header, logfp);
    }
    // time out for ACK
    gettimeofday(&stop, NULL);
    if ((double)(stop.tv_sec - start.tv_sec) * 1000 +
            (double)(stop.tv_usec - start.tv_usec) / 1000 >
        400) {
      perror("Error: do not receive ACK for FIN within 400 ms. Give up\n");
      fclose(fp);
      fclose(logfp);
      free(buf);
      exit(4);
    }
  }
  fclose(fp);
  fclose(logfp);
  free(buf);
  return 0;
}

int runReceiver(int port, unsigned int windowSize, char *recvDir,
                char *logFile) {
  FILE *logfp = fopen(logFile, "w+");
  // Set up connection
  struct sockaddr_in siMe;
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd == -1) {
    fputs("socket creation failed!", stderr);
    exit(2); // error, exit with 2
  }
  memset((char *)&siMe, 0, sizeof(struct sockaddr_in));
  siMe.sin_family = AF_INET;
  siMe.sin_port = htons(port);
  siMe.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(sockfd, (struct sockaddr *)&siMe, sizeof(struct sockaddr_in));

  socklen_t sLen = sizeof(struct sockaddr_in);
  struct sockaddr_in siOther;
  struct timeval start, stop;
  int connectCnt = 0;
  while (1) {
    // 1. Ready for receiving SYN
    char msg[MAX_MESSAGE_SIZE];
    memset(msg, 0, MAX_MESSAGE_SIZE);
    char ACKMsg[MAX_MESSAGE_SIZE];
    memset(ACKMsg, 0, sizeof(ACKMsg));
    unsigned SYNFINSeq = 0;
    struct SRHeader recvHeader;
    struct SRHeader ACKHeader;

    gettimeofday(&start, NULL);
    gettimeofday(&stop, NULL);
    while (1) {
      if (recvfrom(sockfd, msg, MAX_MESSAGE_SIZE, MSG_DONTWAIT,
                   (struct sockaddr *)&siOther, &sLen) > 0) {
        memcpy(&recvHeader, msg, sizeof(recvHeader));
        logInfo(recvHeader, logfp);
        if (recvHeader.flag == SYN) {
          SYNFINSeq = recvHeader.seq;
          // ACK for SYN
          ACKHeader.flag = ACK;
          ACKHeader.seq = SYNFINSeq;
          ACKHeader.len = 0;
          ACKHeader.crc = crc32(NULL, 0);
          memcpy(ACKMsg, (char *)&ACKHeader, sizeof(ACKHeader));
          sendto(sockfd, (void *)ACKMsg, sizeof(ACKHeader), 0,
                 (const struct sockaddr *)&siOther, sizeof(struct sockaddr_in));
          logInfo(ACKHeader, logfp);
          break;
        }
      }
      gettimeofday(&stop, NULL);
      if ((double)(stop.tv_sec - start.tv_sec) * 1000 +
              (double)(stop.tv_usec - start.tv_usec) / 1000 >
          5000) {
        printf("I do not receive SYN within 5 s. Give up\n");
        return 0;
      }
    }
    // 2. Recive data

    // 2.1 open file
    // create file name
    char fileName[30];
    char name[13];
    sprintf(name, "file_%d.txt", connectCnt);
    strcpy(fileName, recvDir);
    strcat(fileName, name);
    FILE *fp = fopen(fileName, "w");
    unsigned int currentACKSeq = 0;
    char *buf = malloc(windowSize * (MAX_PAYLOAD_SIZE + 8)); // valid. len
    memset(buf, 0, windowSize * (MAX_PAYLOAD_SIZE + 8));
    int FINflag = 1; // 0 for receive FIN flag

    // 2.2 receive data
    printf("Start to receive file\n");
    while (FINflag) {
      // receive data
      if (recvfrom(sockfd, msg, MAX_MESSAGE_SIZE, MSG_DONTWAIT,
                   (struct sockaddr *)&siOther, &sLen) != -1) {
        memcpy(&recvHeader, msg, sizeof(recvHeader));
        logInfo(recvHeader, logfp);
        // If it's data
        if (recvHeader.flag == DATA) {
          if (recvHeader.crc ==
              (crc32(msg + sizeof(recvHeader), recvHeader.len))) {
            // check the condition for window operation
            if (recvHeader.seq >= currentACKSeq + windowSize) {
              continue;
            } else if (recvHeader.seq < currentACKSeq) {
              // send ACK currentACKSeq
              ACKHeader.flag = ACK;
              ACKHeader.seq = currentACKSeq;
              ACKHeader.len = 0;
              ACKHeader.crc = crc32(NULL, 0);
              memcpy(ACKMsg, (char *)&ACKHeader, sizeof(ACKHeader));
              sendto(sockfd, (void *)ACKMsg, sizeof(ACKHeader), 0,
                     (const struct sockaddr *)&siOther,
                     sizeof(struct sockaddr_in));
              logInfo(ACKHeader, logfp);
            } else if ((recvHeader.seq > currentACKSeq) &&
                       (recvHeader.seq < currentACKSeq + windowSize)) {
              // buffer it
              unsigned int temp = 1;
              memcpy(buf + (recvHeader.seq - currentACKSeq) *
                               (MAX_PAYLOAD_SIZE + 8),
                     (char *)(&temp), sizeof(temp));
              memcpy(buf +
                         (recvHeader.seq - currentACKSeq) *
                             (MAX_PAYLOAD_SIZE + 8) +
                         4,
                     (char *)(&recvHeader.len), sizeof(temp));
              memcpy(buf +
                         +(recvHeader.seq - currentACKSeq) *
                             (MAX_PAYLOAD_SIZE + 8) +
                         8,
                     msg + sizeof(recvHeader), recvHeader.len);
              // send current ACK
              ACKHeader.flag = ACK;
              ACKHeader.seq = currentACKSeq;
              ACKHeader.len = 0;
              ACKHeader.crc = crc32(NULL, 0);
              memcpy(ACKMsg, (char *)&ACKHeader, sizeof(ACKHeader));
              sendto(sockfd, (void *)ACKMsg, sizeof(ACKHeader), 0,
                     (const struct sockaddr *)&siOther,
                     sizeof(struct sockaddr_in));
              logInfo(ACKHeader, logfp);
            } else if (recvHeader.seq == currentACKSeq) {
              // calculate the highest avalible packet
              unsigned int numWrite = 1;
              for (numWrite = 1; numWrite < windowSize; numWrite++) {
                unsigned int temp;
                memcpy(&temp, buf + numWrite * (8 + MAX_PAYLOAD_SIZE),
                       sizeof(temp));
                if (temp == 0)
                  break;
              }
              fwrite(msg + sizeof(recvHeader), 1, recvHeader.len, fp);
              for (unsigned int ii = 1; ii < numWrite; ii++) {
                unsigned tempLen;
                memcpy(&tempLen, buf + ii * (8 + MAX_PAYLOAD_SIZE) + 4,
                       sizeof(tempLen));
                fwrite(buf + ii * (8 + MAX_PAYLOAD_SIZE) + 8, 1, tempLen, fp);
              }
              // clear buff
              memset(buf, 0, windowSize * (MAX_PAYLOAD_SIZE + 4));
              // ACK
              currentACKSeq = currentACKSeq + numWrite;
              // send current ACK
              ACKHeader.flag = ACK;
              ACKHeader.seq = currentACKSeq;
              ACKHeader.len = 0;
              ACKHeader.crc = crc32(NULL, 0);
              memcpy(ACKMsg, (char *)&ACKHeader, sizeof(ACKHeader));
              sendto(sockfd, (void *)ACKMsg, sizeof(ACKHeader), 0,
                     (const struct sockaddr *)&siOther,
                     sizeof(struct sockaddr_in));
              logInfo(ACKHeader, logfp);
            }
          }
        } else if (recvHeader.flag == FIN) {
          FINflag = 0;
          // send ACK
          ACKHeader.flag = ACK;
          ACKHeader.seq = SYNFINSeq;
          ACKHeader.len = 0;
          ACKHeader.crc = crc32(NULL, 0);
          memcpy(ACKMsg, (char *)&ACKHeader, sizeof(ACKHeader));
          sendto(sockfd, (void *)ACKMsg, sizeof(ACKHeader), 0,
                 (const struct sockaddr *)&siOther, sizeof(struct sockaddr_in));
          logInfo(ACKHeader, logfp);
          // end
          fclose(fp);
          free(buf);
          connectCnt++;
          fclose(logfp);
        }
      }
    }
  }
  fclose(logfp);
  return 0;
}

int main(int argc, char **argv) {
  // Sender mode
  if (strcmp(argv[1], "-s") == 0) {
    // Error for number of arguments
    if (argc != 8) {
      perror(
          "./sr -s <receiver’s IP> <receiver’s port> <sender’s port> <window "
          "size> <file to send> <log file>");
      return 1; // error: exit with 1
    }
    char *recvIP = argv[2];
    int recvPort = atoi(argv[3]);
    int senderPort = atoi(argv[4]);
    unsigned int windowSize = atoi(argv[5]);
    char *fileToSend = argv[6];
    char *logFile = argv[7];
    runSender(recvIP, recvPort, senderPort, windowSize, fileToSend, logFile);
    return 0;
  }

  // Receiver mode
  else if (strcmp(argv[1], "-r") == 0) {
    // Error for number of arguments
    if (argc != 6) {
      perror("./sr -r <port> <window size> <recv dir> <log file>");
      return 1; // error: exit with 1
    }
    // int runReceiver(int port, unsigned int windowSize, char *recvDir,
    //            char *logFile)
    int port = atoi(argv[2]);
    unsigned int windowSize = atoi(argv[3]);
    char *recvDir = argv[4];
    char *logFile = argv[5];
    runReceiver(port, windowSize, recvDir, logFile);
    return 0;
  } else {
    perror("./sr -s <receiver’s IP> <receiver’s port> <sender’s port> <window "
           "size> <file to send> <log file>\n ./sr -r <port> <window size> "
           "<recv dir> <log file>\n");
    return 1;
  }
  return 0;
}