#include <stdio.h>
#include <mathi32.h>
#include <time.h>

// Using fixed-point arithmetic (scaling factor 1000)
#define SCALE 1000
#define ITER 20
#define WIDTH 80
#define HEIGHT 40

static char buffer[15];

int main() {
    int i, x, y;
    int32_t cr, ci;
    int32_t zr, zi;
    int32_t next_zr, next_zi;
    int32_t scale;
    int32_t scale_squaredx4;

    // Pre-calculate constants
    scale = toi32(SCALE);
    scale_squaredx4 = muli32x16(muli32(scale, scale), 4);

    printf("start: %s", cstime());

    for (y = -HEIGHT / 2; y < HEIGHT / 2; y++) {
        for (x = -WIDTH / 2; x < WIDTH / 2; x++) {
            // Map screen coords to Mandelbrot plane (-2.0 to 1.0)
            // cr = (x * 3000 / WIDTH) - 500; // -1500 to 500
            cr = subi32(divi32(muli32x16(toi32(x), 3000), toi32(WIDTH), NULL), toi32(500));
            // ci = (y * 3000 / HEIGHT);      // -1500 to 1500
            ci = divi32(muli32x16(toi32(y), 3000), toi32(HEIGHT), NULL);
            zr = toi32(0), zi = toi32(0);
            
            for (i = 0; i < ITER; i++) {
                // Integer complex multiplication and addition
                // (zr+zi*i)^2 = zr^2 - zi^2 + 2*zr*zi*i
                // next_zr = (zr * zr - zi * zi) / SCALE + cr;
                next_zr = addi32(divi32(subi32(muli32(zr, zr), muli32(zi, zi)), scale, NULL), cr);
                // next_zi = (2 * zr * zi) / SCALE + ci;
                next_zi = addi32(divi32(muli32x16(muli32(zr, zi), 2), scale, NULL), ci);

                zr = next_zr;
                zi = next_zi;

                // Escape radius check (2^2 = 4, but with scaling: 4 * SCALE^2)
                // zr * zr + zi * zi > 4 * SCALE * SCALE
                if (cmpi32(addi32(muli32(zr, zr), muli32(zi, zi)), scale_squaredx4) == 1) {
                    break;
                }
            }
            // Print ASCII character based on iteration count
            putch(i == ITER ? '#' : (i > 10 ? '*' : (i > 5 ? '.' : ' ')));
        }
        putch('\n');
    }
    
    printf("end: %s", cstime());
    
    return 0;
}
