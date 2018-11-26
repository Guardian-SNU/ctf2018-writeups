#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>

void encode(char* input, int length) {
    for (int i = 0; i < length - 1; i++) {
        input[i] = input[i] ^ input[i + 1];
    }
}


int main() {
    char buf[] = "GuardianCTF{XOR_is_very_easy}";

    encode(buf, sizeof(buf)); 
    
    int fd = open("./flag2.txt", O_RDWR);
    write(fd, buf, sizeof(buf));

    return 0;
}