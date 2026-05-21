#include <stdio.h>
#include <stdlib.h>
#include <mathu32.h>

int main(int argc, char *argv[])
{
    uint32_t op1;
    uint32_t op2;
    char *operation;
    uint32_t result;
    char op1_buf[12];
    char op2_buf[12];
    char result_buf[12];
    int comp;
    char *end;

    if (argc != 4) {
        puts("Usage: calc <num> <op> <num>");
        return 1;
    }

    op1 = strtou32(argv[1], &end, 0);
    if (*end != '\0') {
        printf("'%s' is not an unsigned number\n", argv[1]);
        return -1;
    }

    operation = argv[2];

    op2 = strtou32(argv[3], &end, 0);
    if (*end != '\0') {
        printf("'%s' is not an unsigned number\n", argv[3]);
        return -1;
    }

    if (strcmp(operation, "+") == 0) {
        result = addu32(op1, op2);
    }
    else if (strcmp(operation, "-") == 0) {
        result = subu32(op1, op2);
    }
    else if (strcmp(operation, "*") == 0) {
        result = mulu32(op1, op2);
    }
    else if (strcmp(operation, "/") == 0) {
        result = divu32(op1, op2, NULL);
    }
    else if (strcmp(operation, "%") == 0) {
        divu32(op1, op2, &result);
    }
    else if (strcmp(operation, ">>") == 0) {
        result = shru32(op1, op2.low);
    }
    else if (strcmp(operation, "<<") == 0) {
        result = shlu32(op1, op2.low);
    }
    else if (strcmp(operation, "?") == 0) {
        comp = cmpu32(op1, op2);
        if (comp == 0) {
            result_buf[0] = '=';
        }
        else if (comp > 0) {
            result_buf[0] = '>';
        }
        else {
            result_buf[0] = '<';
        }

        printf("%s %c %s\n", u32toa(op1, op1_buf), result_buf[0],
            u32toa(op2, op2_buf));

        return 0;
    }
    else {
        printf("Unrecognized operation: '%s'\n", operation);
        return -1;
    }

    printf("%s %s %s = %s\n", u32toa(op1, op1_buf), operation,
        u32toa(op2, op2_buf), u32toa(result, result_buf));

    return 0;
}

