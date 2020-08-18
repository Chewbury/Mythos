#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "globals.h"

#include "generate.h"
#include "display.h"

player_t player;
int numRows,numCols;
int world[MAXCOLS][MAXROWS];
int screenRows, screenCols;

int setupGame(void){

  player.HP = 100;
  player.SP = 100;
  player.SAN = 100;
  player.NRG = 100;
  player.LVL = 1;
  player.curXP = 0;
  player.nextXP = 100;
  player.x = MAXCOLS/2;
  player.y = MAXROWS/2;
  screenRows = numRows - 3;
  screenCols = numCols - 12;
}

int startCurses(void){

  initscr();             // Start Curses mode
  raw();                 // Put keyboard in raw mode
  noecho();              // Turn off echo
  keypad(stdscr, TRUE);  // Turn on function / cursor keys
  start_color();         // Turn on color
  curs_set(0);           // Hide the cursor
  getmaxyx(stdscr,numRows,numCols);
  

  // Define Colors
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  return EXIT_SUCCESS;
}

int endCurses(void){

  curs_set(1);           // Turn the cursor back on
  cbreak();              // Turn off raw mode
  echo();                // Turn on echo
  endwin();              // Turn off curses

  return EXIT_SUCCESS;
}

int initTest(void){

  initscr();                // Start Curses mode
  setupGame();
  printw("Hello World!!");  // Print Hello World
  refresh();                // Output to the screen
  endwin();                 // End curses mode
  return EXIT_SUCCESS;
}

int main (void){

  int x,y,i,k;

  generate();

  startCurses();
  setupGame();
  drawDisplay();
  refresh();

  while((k=getch()) !='q'){
    if(k==KEY_UP){
      player.y--;
      if(player.y<0){
	player.y=0;
      }
    } else if(k==KEY_DOWN){
      player.y++;
      if(player.y > MAXROWS-1){
	player.y=MAXROWS-1;
      }
    } else if(k==KEY_LEFT){
      player.x--;
      if(player.x < 0){
	player.x = 0;
      }
    } else if(k==KEY_RIGHT){
      player.x++;
      if(player.x > MAXCOLS-1){
	player.x = MAXCOLS-1;
      }
    }
    drawDisplay();
    refresh();
  }

  endCurses();

  return EXIT_SUCCESS;
}
