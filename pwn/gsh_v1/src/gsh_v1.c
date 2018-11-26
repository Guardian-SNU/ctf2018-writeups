#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void help() {
    puts("gsh - Guardian SHell like /bin/sh");
    puts("help - show this message");
    puts("ls - list directory contents");
    puts("echo - display a line of text");
    puts("id - print user and group ID");
    puts("flag - read flag");
    puts("exit - cause normal process termination");
}

void ls() {
    system("ls");
}

void id() {
    puts("uid=0(root) gid=0(root) groups=0(root)");
}

void gsh() {
    char buf[0x30];
    char flag[0x100];

    memset(flag, 0, sizeof(flag));

    while (1) {
        printf("$ ");
        read(0, buf, 0x30);
        if (!strncmp(buf, "gsh", 3))
            gsh();
        else if (!strncmp(buf, "help", 4))
            help();
        else if (!strncmp(buf, "ls", 2))
            ls();
        else if (!strncmp(buf, "id", 2))
            id();
        else if (!strncmp(buf, "flag", 4)) {
            FILE *fp = fopen("flag1.txt", "r");
            fgets(flag, 0x100, fp);
            fclose(fp);
        }
        else if(!strncmp(buf, "echo", 4)) {
            if (buf[4] == ' ')
                printf(&buf[5]);
            else
                help();
        }
        else if (!strncmp(buf, "exit", 4))
            return;
        else
            help();
    }
}

int main() {
    char feedback[0x100];
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    puts("This is easy and simple shell made by Guardian");
    puts("Plz test our new shell");
    gsh();

    puts("\nAny feedbacks?");
    read(0, feedback, 0x100);
    puts("Well-made shell? Thank you! Have a nice day~");


    return 0;
}
