#include <stdio.h>

/*
 * Demo to print series of Fibonacci numbers
 */


/* Recursive function to calculate a Fibonacci number */
int fib(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

int main() {
    int i;
    int f;
    
    printf("First ten Fibonacci numbers:\n");

    for (i=0; i < 10; i++) {
      f = fib(i);
      printf("%d", f);
      /* don't print comma after last number in series */
      if (i == 9) 
        printf("\n");
      else       
        printf(", ");
    }
    
    return f;
}
