#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;

void transform(char st[], int x) {
    int n = 32;
    for (int i = 0; i < n; i++)
        st[n - i - 1] = '0' + (x & 1), x >>= 1;
}

int main() {
    freopen("mainMemory.txt", "w", stdout);
    int n = 256, m = 1000, x;
    char st[33];
    st[32] = 0;
    srand(time(0));
    for (int i = 0; i < n; i++)
        transform(st, x = rand() % m), printf("memory[%d] = 32'b%s; //%d\n", i, st, x);
}