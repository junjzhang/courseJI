#include <arpa/inet.h>  // htons(), ntohs()
#include <netdb.h>      // gethostbyname(), struct hostent
#include <netinet/in.h> // struct sockaddr_in
#include <stdio.h>      // perror(), fprintf()
#include <stdlib.h>     // atoi()
#include <string.h>     // memcpy()
#include <sys/socket.h> // getsockname()
#include <sys/stat.h>   // struct stat
#include <unistd.h>     // close(), stderr

static const size_t MAX_MESSAGE_SIZE_RECEIVE = 256;
static const size_t MAX_MESSAGE_SIZE_SEND = 1024;

int printProcess(int t, int n) {
  int progress = 100 * t / n;
  putchar('[');
  for (int ii = 1; ii < 50; ii++) {
    putchar(ii < progress / 2 ? '#' : ' ');
  }
  putchar(']');
  printf("%3d%%", progress);

  for (int ii = 0; ii != n + 6; ii++) {
    putchar('\b');
  }

  // Exit
  return 0;
}

/**
 * Endlessly runs a server that listens for connections and serves
 * them _synchronously_.
 *
 * Parameters:
 **	port: The port on which to listen for incoming
 *    connections.
 ** queue_size: Size of the listen() queue
 * Returns: -1 on failure, does not return on success.
 */
int runServer(int port, int queueSize) {
  // 1) Create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Error: Can not open stream socket\n");
    return -1;
  }

  // 2) Set the "reuse port" socket option
  int yesval = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yesval, sizeof(yesval)) ==
      -1) {
    perror("Error: Can not set socket options\n");
    return -1;
  }

  // 3) Create a sockaddr_in struct for the proper port and bind() to it.
  struct sockaddr_in addr;
  // 3)a. Make sockaddr_in
  addr.sin_family = AF_INET;
  // Let the OS map it to the correct address.
  addr.sin_addr.s_addr = INADDR_ANY;
  // Use htons to convert from local byte order to network byte order.
  addr.sin_port = htons(port);
  // Bind to the port.
  if (bind(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Error: Can not bind stream socket\n");
    return -1;
  }

  // 3)b. Detect which port was chosen.
  // port = get_port_number(sockfd);
  printf("Server listening on port %d...\n", port);

  // 4) Begin listening for incoming connections.
  listen(sockfd, queueSize);

  // 5) Serve incoming connections file transmission request
  while (true) {
    int connectionfd = accept(sockfd, 0, 0);
    if (connectionfd == -1) {
      perror("Error: Can not accept connection\n");
      return -1;
    }

    printf("New connection %d\n", connectionfd);

    // 5.1) Receive file name from client.
    char msg[MAX_MESSAGE_SIZE_RECEIVE];
    memset(msg, 0, sizeof(msg));
    if (recv(connectionfd, msg, MAX_MESSAGE_SIZE_RECEIVE, 0) == -1) {
      perror("Error: Can not read stream\n");
      return -1;
    }
    printf("Client %d wants %s\n", connectionfd,
           msg); // Print the name of file

    // 5.2) Send file length to client
    // 5.2.1) Get the file length
    struct stat statBuffer;
    size_t fileLen = 0;
    if (stat(msg, &statBuffer) < 0) {
      // Handling reding file error
      perror("Error: Can not read file\n");
      return -1;
    }
    fileLen = statBuffer.st_size;
    printf("File size is %lu\n", fileLen);

    // 5.2.2) Send the file length
    if (send(connectionfd, (const char *)&fileLen, sizeof(size_t), 0) == -1) {
      perror("Error: Can not connect stream socket\n");
      return -1;
    }
    sleep(1);

    // 5.3） Send file content
    // 5.3.1) Open file
    FILE *fp = fopen(msg, "r");
    if (!fp) {
      // Handling file open error
      perror("Error: Can not read file\n");
      return -1;
    }

    // 5.3.2) Send file
    char filePacket[MAX_MESSAGE_SIZE_SEND];
    memset(filePacket, 0, sizeof(filePacket));
    printf("***Sending file***\n");
    size_t numSend = fileLen / sizeof(filePacket);
    for (size_t ii = 0; ii < numSend; ii++) {
      fread(filePacket, sizeof(filePacket), 1, fp);
      if (send(connectionfd, filePacket, sizeof(filePacket), 0) == -1) {
        perror("Error: Can not connect stream socket\n");
        return -1;
      }
      printProcess(ii + 1, numSend);
      fflush(stdout);
    }
    if (fileLen % sizeof(filePacket) != 0) {
      // To do
      fread(filePacket, fileLen % sizeof(filePacket), 1, fp);
      if (send(connectionfd, filePacket, fileLen % sizeof(filePacket), 0) ==
          -1) {
        perror("Error: Can not connect stream socket\n");
        return -1;
      }
      printProcess(100, 100);
    }
    printf("\n");
    sleep(1);

    // 5.3.3) Close file
    fclose(fp);

    // 5.4) Close connection
    close(connectionfd);
  }
}

/**
 * Request file from the server.
 * Parameters:
 **  hostName: 	Remote hostname of the server.
 **  port: 		Remote port of the server.
 **  fileName: 	The fileName to be requested, as a C-string.
 **  clientPort: The port that client binds to.
 * Returns: -1 for error, 0 for success.
 */

int requestFile(const char *hostName, int port, const char *fileName,
                int clientPort) {
  // Check the file name
  if (strlen(fileName) > MAX_MESSAGE_SIZE_RECEIVE) {
    perror("Error: File name exceeds maximum length\n");
    return -1;
  }

  // 1) Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // 2) Create a sockaddr_in to specify remote host and port
  // 2.1) Create
  struct sockaddr_in serverAddr; // specify server's address
  serverAddr.sin_family = AF_INET;

  // 2.2) Specify
  // The socket will be a client, so call this unix helper function to convert a
  // hostname string to a useable `hostent` struct. hostname here may
  // be 10.0.0.1
  struct hostent *host = gethostbyname(hostName);
  if (host == nullptr) {
    fprintf(stderr, "%s: unknown host\n", hostName);
    return -1;
  }
  memcpy(&(serverAddr.sin_addr), host->h_addr, host->h_length);
  // if we also we also want to bind client's socket to a port number...
  struct sockaddr_in myAddr;
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = INADDR_ANY; // INADDRY_ANY == 0.0.0.0
  myAddr.sin_port = htons(clientPort);
  bind(sockfd, (struct sockaddr *)&myAddr, sizeof(myAddr));

  // 2.3) Set the port value
  // Use htons to convert from local byte order to network byte order.
  serverAddr.sin_port = htons(port);

  // 3) Connect to remote server
  if (connect(sockfd, (sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    perror("Error: Can not connect stream socket\n");
    return -1;
  }

  // 4) Request file
  // 4.1) Send file name to remote server
  if (send(sockfd, fileName, strlen(fileName), 0) == -1) {
    perror("Error: Can not send file name on stream socket\n");
    return -1;
  }
  sleep(1);

  // 4.2) Receive file length
  size_t fileLen = 0;
  size_t recvd = 0;
  ssize_t rval;
  do {
    rval = recv(sockfd, (char *)&fileLen, sizeof(size_t), 0);
    if (rval == -1) {
      perror("Error: Can not read stream\n");
      return -1;
    }
    recvd += rval;
  } while (recvd < sizeof(size_t)); // Quit when the filelength is enough
  printf("The file length returned by server is %lu\n", fileLen);

  // 4.3) Open file and write
  FILE *fp = fopen(fileName, "w");
  char filePacket[MAX_MESSAGE_SIZE_SEND];
  memset(filePacket, 0, sizeof(filePacket));
  printf("***Rececive file***\n");
  size_t numRecv = fileLen / sizeof(filePacket);
  for (size_t ii = 0; ii < numRecv; ii++) {
    rval = 0;
    recvd = 0;
    do {
      rval = recv(sockfd, filePacket + recvd, sizeof(filePacket) - recvd, 0);
      if (rval == -1) {
        perror("Error: Can not read stream\n");
        return -1;
      }
      recvd += rval;
    } while (recvd != sizeof(filePacket) && rval != 0);
    // printProcess((int)(ii / numSend * 100));
    fwrite(filePacket, 1, sizeof(filePacket), fp);
    printProcess(ii + 1, numRecv);
    fflush(stdout);
  }
  if (fileLen % sizeof(filePacket) != 0) {
    // To do
    rval = 0;
    recvd = 0;
    do {
      rval = recv(sockfd, filePacket + recvd,
                  fileLen % sizeof(filePacket) - recvd, 0);
      if (rval == -1) {
        perror("Error: Can not read stream\n");
        return -1;
      }
      recvd += rval;
    } while (recvd != (fileLen % sizeof(filePacket)) && rval != 0);
    fwrite(filePacket, 1, fileLen % sizeof(filePacket), fp);
    printProcess(100, 100);
  }
  printf("\n");

  // 4.4)Close file
  fclose(fp);

  // 5) Close connection
  close(sockfd);

  // Succssufully return
  return 0;
}

int main(int argc, const char **argv) {
  if (strcmp(argv[1], "-s") == 0) {
    // Server mode
    if ((argc != 4) || (strcmp(argv[2], "-p") != 0)) {
      // Error handling
      printf("Error: Wrong arguments. Usage: ./ftrans -s -p <port>\n");
      return 1;
    }

    // Read parameter
    int port = atoi(argv[3]);
    // Run server
    if (runServer(port, 10) == -1) {
      printf("Error: Can not run server\n");
      return 1;
    }

    // Exit
    return 0;
  } else if (strcmp(argv[1], "-c") == 0) {
    // Client mode
    if ((argc != 10) || (strcmp(argv[2], "-h") != 0) ||
        (strcmp(argv[4], "-sp") != 0) || (strcmp(argv[6], "-f") != 0) ||
        (strcmp(argv[8], "-cp") != 0)) {
      // Error handling
      printf("Error: Wrong arguments. Usage:");
      printf("/ftrans -c -h <server’s "
             "IP/hostname> "
             "-sp <server "
             "port> -f <filename> -cp <client port>\n");
      return 1;
    }

    // Read parameters
    const char *hostName = argv[3];
    int port = atoi(argv[5]);
    const char *fileName = argv[7];
    int clientPort = atoi(argv[9]);

    // Show operation
    printf("Request file %s from %s:%d\n", fileName, hostName, port);
    if (requestFile(hostName, port, fileName, clientPort == -1)) {
      printf("Error: Can not run client\n");
      return 1;
    }

    // Exit
    return 0;
  } else {
    // error handling
    printf("Error: Wrong arguments. Usage: \n");
    printf("Server mode: ./ftrans -s -p <port>\n");
    printf("Client mode: ./ftrans -c -h <server’s IP/hostname> -sp <server "
           "port> -f <filename> -cp <client port>\n");
    return 1;
  }
}