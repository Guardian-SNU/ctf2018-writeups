#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char FLAG1[0x100];

void readFlag1() {
    FILE *fp = fopen("flag1.txt", "r");
    fgets(FLAG1, 0x100, fp);
}

void vuln() {
    char buf[0x10];
    read(0, buf, 0x1000);
}

int main() {
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    vuln();
    puts("Bye~");
}
