#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INT 1
#define STR 2

typedef union {
    char* s;
    long i;
} Value;

typedef struct {
    int type;
    Value value;
} Object;

typedef struct {
    Object *obj;
    char *name;
    void *next;
} Node;

Node HEAD;

int getint() {
    char buf[0x20];
    read(0, buf, sizeof(buf));
    return atoi(buf);
}

void menu() {
    puts("\n<Simple Calc>");
    puts("[1] New Variable");
    puts("[2] Calculate");
    puts("[3] Show");
    puts("[4] Read flag");
    puts("[0] Exit");
    printf(">> ");
}

Node *getNode(char *name) {
    Node *ptr = HEAD.next;
    while (ptr != NULL) {
        if (!strcmp(ptr->name, name))
            break;
        ptr = ptr->next;
    }
    return ptr;
}

void makeInt(char *name, long value) {
    Node *new_node = malloc(sizeof(Node));
    Object *new_obj = malloc(sizeof(Object));

    if (new_node == NULL || new_obj == NULL) {
        puts("malloc() error");
        exit(1);
    }

    new_obj->type = INT;
    new_obj->value.i = value;

    new_node->name = strdup(name);
    new_node->obj = new_obj;
    new_node->next = HEAD.next;
    HEAD.next = new_node;
}

void makeStr(char *name, char *value) {
    Node *new_node = malloc(sizeof(Node));
    Object *new_obj = malloc(sizeof(Object));

    if (new_node == NULL || new_obj == NULL) {
        puts("malloc() error");
        exit(1);
    }

    new_obj->type = STR;
    new_obj->value.s = strdup(value);

    new_node->name = strdup(name);
    new_node->obj = new_obj;
    new_node->next = HEAD.next;
    HEAD.next = new_node;
}

void newVariable() {
    int choice;
    char name[0x100], value[0x100];

    memset(name, 0, sizeof(name));
    memset(value, 0, sizeof(value));
    
    puts("\n[New Variable]");
    puts("[1] Integer");
    puts("[2] String");
    puts("[0] Back");
    printf(">> ");
    choice = getint();

    switch (choice) {
        case 1:
            printf("Name: ");
            read(0, name, sizeof(name));
            printf("Value: ");
            read(0, value, sizeof(value));
            makeInt(name, atoll(value));
            break;
        case 2:
            printf("Name: ");
            read(0, name, sizeof(name));
            printf("Value: ");
            read(0, value, sizeof(value));
            makeStr(name, value);
            break;
        default:
            return;
    }
}

void calcInt(Node *v1, Node *v2, char op) {
    long result, n1, n2;
    char name[0x100];

    memset(name, 0, sizeof(name));

    n1 = v1->obj->value.i;
    n2 = v2->obj->value.i;
    switch (op) {
        case '+':
            result = n1 + n2;
            break;
        case '-':
            result = n1 - n2;
            break;
        case '*':
            result = n1 * n2;
            break;
        case '/':
            if (n2 == 0) {
                puts("Divide by zero");
                return;
            }
            result = n1 / n2;
            break;
        case '%':
            if (n2 == 0) {
                puts("Divide by zero");
                return;
            }
            result = n1 % n2;
            break;
        case '=':
            v2->obj->value.i = n1;
            return;
        default:
            puts("Invalid operator");
            return;
    }

    printf("Name: ");
    read(0, name, sizeof(name));
    makeInt(name, result);
}

void calcStr(Node *v1, Node *v2, char op) {
    char *result, *s1, *s2, name[0x100];
    s1 = v1->obj->value.s;
    s2 = v2->obj->value.s;

    memset(name, 0, sizeof(name));

    switch (op) {
        case '+':
            result = strcat(s1, s2);
            break;
        case '=':
            if (strlen(s1) > strlen(s2)) {
                v2->obj->value.s = strdup(s1);
            } else {
                strcpy(s2, s1);
            }
            return;
        default:
            puts("Invalid operator");
            return;
    }

    printf("Name: ");
    read(0, name, sizeof(name));
    makeStr(name, result);
}

void calculate() {
    Node *v1, *v2;
    char name1[0x100], name2[0x100], op[2];
    memset(name1, 0, sizeof(name1));
    memset(name2, 0, sizeof(name2));

    printf("Variable1: ");
    read(0, name1, sizeof(name1));
    v1 = getNode(name1);
    if (v1 == NULL) {
        printf("There's no variable names %s\n", name1);
        return;
    }

    printf("Variable2: ");
    read(0, name2, sizeof(name2));
    v2 = getNode(name2);
    if (v2 == NULL) {
        printf("There's no variable names %s\n", name2);
        return;
    }

    printf("Operator: ");
    read(0, op, sizeof(op));

    switch (v1->obj->type) {
        case INT:
            calcInt(v1, v2, op[0]);
            break;
        case STR:
            calcStr(v1, v2, op[0]);
            break;
        default:
            puts("Invalid type...");
            break;
    }
}

void show() {
    Node *ptr;
    char name[0x100];
    memset(name, 0, sizeof(name));
    printf("Name: ");
    read(0, name, sizeof(name));

    ptr = getNode(name);

    if (ptr == NULL) {
        printf("There's no variable names %s\n", name);
        return;
    }

    switch (ptr->obj->type) {
        case INT:
            printf("Type: Integer\n");
            printf("Value: %ld\n", ptr->obj->value.i);
            break;
        case STR:
            printf("Type: String\n");
            printf("Value: %s\n", ptr->obj->value.s);
            break;
        default:
            puts("Invalid type...");
            break;
    }
}

void readFlag() {
    char *flag = malloc(0x100);
    char buf[0x10];
    FILE *fp = fopen("flag1.txt", "r");
    fgets(flag, 0x100, fp);
    fclose(fp);
    while (1) {
        puts("Do you want to see flag?");

        read(0, buf, sizeof(buf));
        if (!strncmp(buf, "no", 2)) {
            puts("Okay :)");
            free(flag);
            return;
        }
        puts("What..?");
    }
    puts(flag);
}

int main() {
    int choice;
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    HEAD.next = NULL;
    HEAD.name = "";
    HEAD.obj = NULL;
    
    while (1) {
        menu();
        choice = getint();
        switch (choice) {
            case 0:
                return 0;
            case 1:
                newVariable();
                break;
            case 2:
                calculate();
                break;
            case 3:
                show();
                break;
            case 4:
                readFlag();
                break;
            default:
                puts("Invalid choice");
                break;
        }
    }
}
