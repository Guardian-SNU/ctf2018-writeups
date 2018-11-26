#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NORMAL 1
#define DIRECTORY 2
#define LINK 3

#define README \
    "Welcome to GSH final version!\n"\
    "\n"\
    "[Stage1]\n"\
    "We made flag1.txt for you!\n"\
    "But accidently we remove flag directory.. :(\n"\
    "Can you repair flag1.txt for me..?\n"\
    "\n"\
    "[Stage2]\n"\
    "Can you escape from this shell?\n"\
    "If you can, I'll give you some points :)\n"\
    "\n"\
    "\n"\
    "Plz enjoy our new shell!!"

struct File {
    char* name;
    void* content;
    struct File* parent;
    struct File* next;
    int type;
};

struct File ROOT;

int parseCmd(char *cmd, char*** argv) {
    int capacity = 3, argc = 0;
    char **tmp = malloc(capacity*sizeof(char*));
    char *token;
    token = strtok(cmd, " ");

    do {
        tmp[argc] = token;
        argc++;
        if (argc > capacity) {
            capacity = capacity*2;
            tmp = realloc(tmp, capacity*sizeof(char*));
        }
    } while (token = strtok(NULL, " "));
    *argv = tmp;
    return argc;
}

int checkArgc(char *cmd, int argc, int min, int max) {
    if (argc < min || argc > max) {
        printf("%s: argument count wrong\n", cmd);
        return 0;
    }
    return 1;
}

void printError(char *cmd, char* msg) {
    printf("%s: %s\n", cmd, msg);
}

struct File *findChild(struct File *parent, char *name) {
    struct File *ptr;

    if (parent->type != DIRECTORY)
        return NULL;
    
    ptr = parent->content;
    if (ptr == NULL)
        return NULL;
    do {
        if (!strcmp(ptr->name, name))
            return ptr;
    } while (ptr = ptr->next);
}

struct File *getFile(struct File *cwd, char *path) {
    char *token, *p;
    struct File *file;

    if (!strncmp(path, "/", 2)) {
        return &ROOT;
    }
    else if (!strncmp(path, "/", 1)) {
        file = &ROOT;
        p = strdup(path+1);
    }
    else {
        file = cwd;
        p = strdup(path);
    }

    token = strtok(p, "/");

    do {
        if (!strcmp(token, "")) {
            continue;
        }
        else if (!strcmp(token, ".")) {
            continue;
        }
        else if (!strcmp(token, "..")) {
            file = file->parent;
        }
        else {
            file = findChild(file, token);
            if (file == NULL)
                return NULL;
        }
    } while (token = strtok(NULL, "/"));

    return file;
}

struct File *getLink(struct File *file) {
    struct File *ptr = file;
    while (ptr->type == LINK) {
        ptr = ptr->content;
    }
    return ptr;
}

void readline(char *buf, unsigned int size) {
    int ret;
    unsigned int cnt = 0;
    char c;
    while (size > cnt) {
        ret = read(0, &c, 1);
        if (!ret) {
            puts("read() error");
            exit(1);
        }
        if (c == '\n') {
            return;
        }
        buf[cnt] = c;
        cnt++;
    }
}

int readint() {
    char buf[8];
    read(0, buf, 8);
    return atoi(buf);
}

void printPath(struct File *file, unsigned int depth) {
    if (file->parent == file) {
        if (depth == 0)
            printf("/");
        return;
    }
    if (depth > 100) {
        printf(".../%s", file->name);
        return;
    }
    printPath(file->parent, depth+1);
    printf("/%s", file->name);
    return;
}

struct File *makeFile(struct File *parent, char *name, char* content) {
    struct File *new_file = malloc(sizeof(struct File));
    memset(new_file, 0, sizeof(struct File));
    new_file->type = NORMAL;
    new_file->parent = parent;
    new_file->next = parent->content;
    new_file->name = strdup(name);
    new_file->content = strdup(content);

    parent->content = new_file;

    return new_file;
}

struct File *makeDirectory(struct File *parent, char *name) {
    struct File *new_dir = malloc(sizeof(struct File));
    memset(new_dir, 0, sizeof(struct File));
    new_dir->type = DIRECTORY;
    new_dir->parent = parent;
    new_dir->next = parent->content;
    new_dir->name = strdup(name);

    parent->content = new_dir;

    return new_dir;
}

struct File *makeLink(struct File *parent, char *name, struct File *dest) {
    struct File *new_link = malloc(sizeof(struct File));
    memset(new_link, 0, sizeof(struct File));
    new_link->type = LINK;
    new_link->parent = parent;
    new_link->next = parent->content;
    new_link->name = strdup(name);
    new_link->content = dest;
    
    parent->content = new_link;

    return new_link;
}

void removeFile(struct File *dest) {
    struct File *prev, *curr, *parent = dest->parent;

    prev = parent;
    curr = parent->content;
    if (curr == dest)
        parent->content = curr->next;
    else {
        while (curr) {
            if (curr == dest) {
                prev->next = curr->next;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    free(dest->name);
    free(dest);
}

void ls(struct File *cwd, int argc, char **argv) {
    struct File *ptr;
    
    if (!checkArgc("ls", argc, 1, 2))
        return;
    
    if (argc == 2) {
        ptr = getFile(cwd, argv[1]);
        if (ptr == NULL) {
            printError("ls", "wrong path");
            return;
        }
    } else {
        ptr = cwd;
    }

    if (ptr->type == LINK)
        ptr = getLink(ptr);
    
    if (ptr->type == NORMAL) {
        puts(ptr->name);
        return;
    }
    
    ptr = ptr->content;
    if (ptr == NULL)
        return;
    do {
        printf("%s\t", ptr->name);
    } while (ptr = ptr->next);
    puts("");
}

void pwd(struct File *cwd, int argc, char **argv) {
    if (!checkArgc("pwd", argc, 1, 1))
        return;
    printPath(cwd, 0);
    puts("");
}

void touch(struct File *cwd, int argc, char **argv) {
    if (!checkArgc("touch", argc, 2, 2))
        return;

    if (getFile(cwd, argv[1]) != NULL) {
        printError("touch", "already exists");
        return;
    }

    if (strchr(argv[1], '/')) {
        printError("touch", "invalid file name");
        return;
    }

    makeFile(cwd, argv[1], "");
}

void mkdir(struct File *cwd, int argc, char **argv) {
    if (!checkArgc("mkdir", argc, 2, 2))
        return;
    
    if (getFile(cwd, argv[1]) != NULL) {
        printError("mkdir", "already exists");
        return;
    }

    if (strchr(argv[1], '/')) {
        printError("mkdir", "invalid directory name");
        return;
    }

    makeDirectory(cwd, argv[1]);
}

struct File *cdHelper(struct File *cwd, int argc, char **argv) {
    struct File* ptr;
    
    if (!checkArgc("cd", argc, 1, 2))
        return cwd;

    if (argc == 1) {
        ptr = getFile(cwd, "/home/guardian");
    } else {
        ptr = getFile(cwd, argv[1]);
    }
    if (ptr == NULL)
        return cwd;
    if (ptr->type == LINK)
        ptr = getLink(ptr);
    return ptr;
}

void ln(struct File *cwd, int argc, char **argv) {
    struct File* ptr;

    if (!checkArgc("ln", argc, 3, 3))
        return;

    if (strchr(argv[2], '/')) {
        printError("ln", "invalid file name");
        return;
    }

    ptr = getFile(cwd, argv[1]);
    if (ptr == NULL) {
        printError("ln", "file doesn't exist");
        return;
    }

    makeLink(cwd, argv[2], ptr);
}

void vim(struct File *cwd, int argc, char **argv) {
    puts("We don't support vim, sorry :(");
    puts("Instead we give you gvim, Guardian version VIM (not GUI VIM)");
    puts("Plz use gvim for editing files");
    puts("Thank you!");

    return;
}

void gvim(struct File *cwd, int argc, char **argv) {
    struct File *ptr;
    char *content;
    size_t size;

    if (!checkArgc("gvim", argc, 2, 2))
        return;

    ptr = getFile(cwd, argv[1]);
    if (ptr == NULL) {
        printError("gvim", "file doesn't exists");
        return;
    }

    if (ptr->type == LINK)
        ptr = getLink(ptr);
    if (ptr->type == DIRECTORY) {
        printError("gvim", "can't write to directory");
        return;
    }
    puts("[Guardian VIM]");
    printf("File : ");
    printPath(ptr, 0);
    printf("\nNew content length? ");
    
    size = readint();
    content = malloc(size+1);
    if (content == NULL) {
        puts("malloc error");
        exit(1);
    }
    printf("Write new content: ");
    read(0, content, size);
    free(ptr->content);
    ptr->content = content;

    puts("Done!");
    return;
}

void cat(struct File *cwd, int argc, char **argv) {
    struct File *ptr;

    if (!checkArgc("cat", argc, 2, 2))
        return;

    ptr = getFile(cwd, argv[1]);
    if (ptr == NULL) {
        printError("cat", "meow");
        return;
    }
    if (ptr->type == LINK)
        ptr = getLink(ptr);
    if (ptr->type == DIRECTORY) {
        printError("cat", "nyan! http://www.nyan.cat/");
        return;
    }
    puts(ptr->content);

    return;
}

void rm(struct File *cwd, int argc, char **argv) {
    struct File *ptr, *tmp;

    if (!checkArgc("rm", argc, 2, 2))
        return;

    ptr = getFile(cwd, argv[1]);
    if (ptr == NULL) {
        printError("rm", "file doesn't exists");
        return;
    }
    if (ptr->type == DIRECTORY) {
        if (ptr == cwd) {
            printError("rm", "cannot remove current directory");
            return;
        }
        tmp = cwd;
        while (tmp != tmp->parent) {
            tmp = tmp->parent;
            if (ptr == tmp) {
                printError("rm", "cannot remove parent directory");
                return;
            }
        }
    }

    removeFile(ptr);
    return;
}

void id(struct File *cwd, int argc, char **argv) {
    if (!checkArgc("id", argc, 1, 1))
        return;

    puts("uid=1000(guardian) gid=1000(guardian) groups=1000(guardian),27(sudo)");
    return;
}

void echo(struct File *cwd, int argc, char **argv) {
    if (!checkArgc("echo", argc, 2, 2))
        return;

    puts(argv[1]);
    return;
}

void gsh(struct File *start) {
    struct File *cwd = start, *ptr;
    char buf[0x200];
    int argc;
    char **argv;

    while (1) {
        printf("$ ");
        memset(buf, 0, sizeof(buf));
        readline(buf, sizeof(buf));
        argc = parseCmd(buf, &argv);

        if (!strncmp(argv[0], "gsh", 4))
            gsh(cwd);
        else if (!strncmp(argv[0], "ls", 3))
            ls(cwd, argc, argv);
        else if (!strncmp(argv[0], "echo", 5))
            echo(cwd, argc, argv);
        else if (!strncmp(argv[0], "pwd", 4))
            pwd(cwd, argc, argv);
        else if (!strncmp(argv[0], "touch", 6))
            touch(cwd, argc, argv);
        else if (!strncmp(argv[0], "mkdir", 6))
            mkdir(cwd, argc, argv);
        else if (!strncmp(argv[0], "cd", 3))
            cwd = cdHelper(cwd, argc, argv);
        else if (!strncmp(argv[0], "ln", 3))
            ln(cwd, argc, argv);
        else if (!strncmp(argv[0], "vim", 4))
            vim(cwd, argc, argv);
        else if (!strncmp(argv[0], "gvim", 5))
            gvim(cwd, argc, argv);
        else if (!strncmp(argv[0], "cat", 4))
            cat(cwd, argc, argv);
        else if (!strncmp(argv[0], "rm", 3))
            rm(cwd, argc, argv);
        else if (!strncmp(argv[0], "id", 3))
            id(cwd, argc, argv);
        else if (!strncmp(argv[0], "exit", 5)) {
            free(argv);
            return;
        }

        free(argv);
    }
}

struct File *setup(struct File* root) {
    struct File *ptr, *home, *flag;

    flag = makeDirectory(root, "flag");
    makeFile(flag, "flag1.txt", "GuardianCTF{I_w4nt_2_ra1se_cat5..}");
    makeDirectory(root, "tmp");
    makeDirectory(root, "etc");
    makeDirectory(root, "root");
    ptr = makeDirectory(root, "home");
    makeDirectory(ptr, "munji");
    makeDirectory(ptr, "push0ebp");
    home = makeDirectory(ptr, "guardian");
    
    makeFile(home, "README.md", README);

    removeFile(flag);

    return home;
}

int main() {
    struct File *home;

    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    memset(&ROOT, 0, sizeof(struct File));
    ROOT.name = "";
    ROOT.type = DIRECTORY;
    ROOT.parent = &ROOT;

    home = setup(&ROOT);

    puts("We remade gsh");
    puts("gsh v1 is just a prototype");
    puts("Enjoy our masterpiece!");

    gsh(home);

    puts("\nWe don't take any feedback");
    puts("cause it's just P.E.R.F.E.C.T! ;)");

    return 0;
}
