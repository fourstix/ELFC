#define _STGROM_
#include <stdio.h>

/* Stack Frame Example 1 */
int fn1(int n, char c, int *p) {
   int  i1 = 4;
   char c1 = c+3;
   char a[3] = {'x','y','z'};

   /* Example 1 Breakpoint */
   BRKPT

   return i1;
}

struct scrabble_tile {
  char letter;
  int  score;
};

/* get the tile from a player's rack */
struct scrabble_tile rack(int pos) {
    struct scrabble_tile tile;

    /* get the scrabble tile from rack */
    tile.letter = 'D';  /* Pretend it is 'D' for demo */
    tile.score = 2;

   /* Example 2 Breakpoint */
    BRKPT

    /* return tile at position in rack */
    return tile;
  }

  struct point {
    int x;
    int y;
  };

  /* scale a point by a value */
  struct point scale(int n, struct point p) {
      int factor;

      /* negative or zero is not valid */
      factor = (n < 1) ? 1 : n;

      /* multiple (x,y) values by scaling factor */
      p.x = factor * (p.x);
      p.y = factor * (p.y);

      /* Example 3 Breakpoint */
      BRKPT

      /* return point */
      return p;
  }

int main() {
  int i = 42;
  int *p;
  int rslt;
  struct scrabble_tile t;
  struct point pt, double;

  p = &i;
  rslt = fn1(i, 'a', p);
  printf("result = %d\n", rslt);

  /* Pretend Scrabble tile 'D' is at position 3 */
  t = rack(3);
  printf("Tile 3 = %c score = %d\n", t.letter, t.score);

  pt.x = -1;
  pt.y =  1000;

  double = scale(2, pt);

  printf("point.x = %d, point.y = %d\n", pt.x, pt.y);
  printf("double.x = %d, double.y = %d\n", double.x, double.y);

  return 0;
}
