#include<cstdio>
#include<algorithm>
#include<cmath>
#include<ctime>
#define size 256
using namespace std;

int cpu[size], number[10010], address[10010], rw[10010];

int main() {
    freopen("testGen.txt", "w", stdout);
    int n = 1000, m = 1000, addr = 600, readWrite = 0, writeData;
    srand(time(0));
    for (int i = 0; i < 256; i++)
        cpu[i] = i;
    printf("#0 ");
    for (int i = 0; i < n; i++) {

        addr += rand() % 25 - 12;
        addr = min(max(addr, 0), 1023);

        readWrite = rand() & 1;

        writeData = readWrite? (rand() % m): -1;

        address[i] = addr;
        if (readWrite) cpu[addr>>2] = writeData, number[i] = writeData;
        else number[i] = cpu[addr>>2];
        
        printf("readWrite = %d; writeData = %3d; addr = %4d;//Round %4d, addr>>2 = %3d\n#10 ", readWrite, writeData, addr, i, addr>>2);
        //write test code here
    }
    fclose(stdout);
    freopen("result.txt", "w", stdout);
    for (int i = 0; i < n; i++)
        printf("Round %d: readWrite = %d, data = %d, address = %d\n", i, rw[i], number[i], address[i]);
    fclose(stdout);
}