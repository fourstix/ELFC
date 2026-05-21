#include <stdio.h>
#include <mathi32.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int i, j, k;
    int q, d;
    int nines = 0;
    int predigit = 0;
    int32_t x, y, r;
    int *a;
    int len, digits;

    if (argc != 2)
    {
        printf("usage: pi <num_digits>\n");
        return 1;
    }
    
    digits = atoi(argv[1]) + 1;
    len = ((10 * digits) / 3);
    
    a = (int *)malloc((len + 1) * sizeof(int));

    if (a == NULL)
    {
        printf("Not enough memory for %d digits.", digits);
        return 1;
    }
    
    printf("start: %s", cstime());

    for (j = 1; j <= len; j++)
        a[j] = 2;

    for (j = 1; j <= digits; j++)
    {
        q = 0;

        for (i = len; i >= 1; i--)
        {
            x = addi32(toi32(10 * a[i]), toi32(q * i));            
            d = 2 * i - 1;
            y = divi32(x, toi32(d), &r);
            a[i] = r.low;
            q = y.low;
        }

        a[1] = q % 10;
        q /= 10;

        if (q == 9)
        {
            nines++;
        }
        else if (q == 10)
        {
            putch(predigit + 1 + 0x30);

            for (k = 1; k <= nines; k++)
                putch('0');

            predigit = 0;
            nines = 0;
        }
        else
        {
            if (j > 1)
                putch(predigit + 0x30);
            if (j == 2)
                putch('.');

            predigit = q;

            if (nines != 0)
            {
                for (k = 1; k <= nines; k++)
                    putch('9');

                nines = 0;
            }
        }
    }

    printf("\nend: %s", cstime());
}
