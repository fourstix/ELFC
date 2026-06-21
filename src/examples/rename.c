#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        puts("Usage: rename source dest");
        return 2;
    }
    
    if (rename(argv[1], argv[2]) != 0) {
        puts("File not found");
        return 1;
    }

    return 0;
}
