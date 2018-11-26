#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define WITHDRAW 0
#define DEPOSIT 1

unsigned int balance = 0;

unsigned int cash = 500;

typedef struct {
    unsigned int amount;
    int type;
} WorkerArg;

void menu() {
    puts("[1] Deposit money");
    puts("[2] Withdraw money");
    puts("[3] My info");
    puts("[4] Print flag");
    puts("[0] Run away");
}

int getint() {
    char buf[32];
    read(0, buf, 32);
    return atoi(buf);
}

void printFlag() {
    char flag[0x100];

    if (cash < 0xf0000000) {
        puts("You're bank robber..!");
        puts("You have to rob bank if you want flag");
        return;
    }
    puts("Oh..!");
    puts("You really rob a bank!!");
    puts("Wait a second..");

    sleep(1);

    memset(flag, 0, sizeof(flag));
    FILE *fp = fopen("flag.txt", "r");
    fgets(flag, 0x100, fp);
    printf("Here you are: %s", flag);
}

void *worker(void *args) {
    unsigned int amount;
    int i;
    WorkerArg *arg;
    arg = (WorkerArg *)args;
    amount = arg->amount;

    sleep(1);

    if (arg->type == DEPOSIT) {
        cash -= amount;
        balance += amount;
    } else {
        cash += amount;
        balance -= amount;
    }
}

void withdraw() {
    pthread_t thread;
    WorkerArg *args = malloc(sizeof(WorkerArg));
    unsigned int amount;
    int thr_id;

    if (args == NULL) {
        puts("malloc() error");
        exit(1);
    }

    printf("Amount: ");
    amount = getint();

    if (balance < amount) {
        puts("Not enough money!");
        return;
    }
    args->amount = amount;
    args->type = WITHDRAW;

    thr_id = pthread_create(&thread, NULL, (void *)worker, (void *)args);
    if (thr_id < 0) {
        puts("pthread error");
        exit(1);
    }
}

void deposit() {
    pthread_t thread;
    WorkerArg *args = malloc(sizeof(WorkerArg));
    unsigned int amount;
    int thr_id;

    if (args == NULL) {
        puts("malloc() error");
        exit(1);
    }

    printf("Amount: ");
    amount = getint();

    if (cash < amount) {
        puts("Not enough money!");
        return;
    }
    args->amount = amount;
    args->type = DEPOSIT;

    thr_id = pthread_create(&thread, NULL, (void *)worker, (void *)args);
    if (thr_id < 0) {
        puts("pthread error");
        exit(1);
    }
}

void myInfo() {
    printf("[info]\n"
            "Cash: %u won\n"
            "Balance: %u won\n",
            cash, balance);
}

int main() {
    char name[0x100];
    int choice;
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    puts("Hi, new robber");
    puts("What's you're name?");
    read(0, name, 0x100);
    
    while (1) {
        menu();
        choice = getint();
        switch (choice) {
            case 0:
                puts("Loser..");
                exit(1);
                break;
            case 1:
                deposit();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                myInfo();
                break;
            case 4:
                printFlag();
                break;
            default:
                puts("Invalid choice");
                break;
        }
    }
}
