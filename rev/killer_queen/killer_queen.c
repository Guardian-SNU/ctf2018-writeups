#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 40

char flag2[] = { 0x32, 0x14, 0x13, 0x16, 0x0d, 0x08, 0x0f, 0x2d, 0x17, 0x12, 0x3d, 0x23, 0x17, 0x1d, 0x0d, 0x36, 0x1a, 0x2c, 0x29, 0x13, 0x17, 0x0b, 0x26, 0x3a, 0x04, 0x12, 0x0a, 0x04, 0x7d, 0x00 };

void encode(char* input, int length) {
    for (int i = 0; i < length - 1; i++) {
        input[i] = input[i] ^ input[i + 1];
    }
}

int main() {
    char buf[BUF_SIZE];

    read(0, buf, BUF_SIZE - 1);

    for (int i = 0; i < BUF_SIZE - 1; i++) {
        if (buf[i] == 0x0a) {
            buf[i] = 0;
        }
    }
    buf[BUF_SIZE - 1] = 0;

    encode(buf, BUF_SIZE);

    if (!strcmp(buf, flag2)) {
        printf("Wow! that is correct input! Get your flag here\n");
    }
    else {
        printf("No..that is not the answer..try hard!\n");
    }

    fflush(stdin);
    exit(0);
}
