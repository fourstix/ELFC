#include <stdio.h>
#include <mathi32.h>
#include <time.h>

typedef int int16_t;

#define DIGITS 400
#define LEN ((10 * DIGITS) / 3)

static int16_t a[LEN + 1];

int main() {
    int16_t i, j, k;
    int16_t q, d;
    int16_t nines = 0;
    int16_t predigit = 0;
    int32_t x, y, r;

    printf("start: %s", cstime());

    for (j = 1; j <= LEN; j++)
        a[j] = 2;

    for (j = 1; j <= DIGITS; j++)
    {
        q = 0;

        for (i = LEN; i >= 1; i--)
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
