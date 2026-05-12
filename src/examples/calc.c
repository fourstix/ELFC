#include <stdio.h>
#include <stdlib.h>
#include <mathi32.h>

int main(int argc, char *argv[])
{
    int32_t op1;
    int32_t op2;
    char *operation;
    int32_t result;
    char op1_buf[12];
    char op2_buf[12];
    char result_buf[12];
    int comp;

    if (argc != 4) {
        puts("Usage: calc <num> <op> <num>");
        return 1;
    }

    op1 = atoi32(argv[1]);
    operation = argv[2];
    op2 = atoi32(argv[3]);

    if (strcmp(operation, "+") == 0) {
        result = addi32(op1, op2);
    }
    else if (strcmp(operation, "-") == 0) {
        result = subi32(op1, op2);
    }
    else if (strcmp(operation, "*") == 0) {
        result = muli32(op1, op2);
    }
    else if (strcmp(operation, "/") == 0) {
        result = divi32(op1, op2, NULL);
    }
    else if (strcmp(operation, "%") == 0) {
        divi32(op1, op2, &result);
    }
    else if (strcmp(operation, "?") == 0) {
        comp = cmpi32(op1, op2);
        if (comp == 0) {
            result_buf[0] = '=';
        }
        else if (comp > 0) {
            result_buf[0] = '>';
        }
        else {
            result_buf[0] = '<';
        }

        printf("%s %c %s\n", i32toa(op1, op1_buf), result_buf[0],
            i32toa(op2, op2_buf));

        return 0;
    }
    else {
        printf("Unrecognized operation: '%s'\n", operation);
        return -1;
    }

    printf("%s %s %s = %s\n", i32toa(op1, op1_buf), operation,
        i32toa(op2, op2_buf), i32toa(result, result_buf));

    return 0;
}

