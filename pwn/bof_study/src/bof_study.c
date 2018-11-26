#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void flag2() {
    char flag[0x100];
    puts("Wow! You find 2nd stage!!");
    puts("Now you can control PC");
    FILE *fp = fopen("flag2.txt", "r");
    fgets(flag, 0x100, fp);
    fclose(fp);
    printf("flag2: %s\n", flag);
}

void flag1() {
    char flag[0x100];
    puts("Okay, now you understand Buffer Overflow!");
    FILE *fp = fopen("flag1.txt", "r");
    fgets(flag, 0x100, fp);
    fclose(fp);
    printf("flag1: %s\n", flag);
}

void bof() {
    char check[16] = "\x12\x34\x56\x78\x9a\xbc\xde\xf0";
    char buffer[8];
    puts("\n\n\nWe're in the BOF world!");
    sleep(1);
    puts("Give me some bytes");
    gets(buffer);

    if (memcmp(check, "\x11\x22\x33\x44\x55\x66", 6) == 0)
        flag1();

    puts("So tasty :)");
}

int main() {
    int i;

    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    puts("This problem is for baby pwners");
    sleep(1);
    puts("So, what's BOF?");
    sleep(1);
    puts("Let's learn about it!");
    sleep(1);
    for (i=0; i<3; i++) {
        printf(".");
        sleep(1);
    }
    bof();
    return 0;
}
