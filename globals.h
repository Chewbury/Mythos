#define MAXROWS 1024
#define MAXCOLS 1024

// COLOURS
#define RED 1
#define GREEN 2
#define CYAN 3
#define WHITE 4
#define BLUE 5

// Objects
#define PLAIN_GRASS 1
#define LONG_GRASS 2
#define TREE 3
#define SHALLOW_WATER 4
#define DEEP_WATER 5

typedef struct player_t {
  int HP;
  int SP;
  int SAN;
  int NRG;
  int LVL;
  int curXP;
  int nextXP;
  int x,y;
} player_t;

//player_t player;

//int numCols, numrows;
