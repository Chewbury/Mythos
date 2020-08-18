#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "globals.h"

extern int numCols,numRows;
extern int screenCols, screenRows;
extern player_t player;
extern int world[MAXCOLS][MAXROWS];

int drawHUD(void){

  int i,x,y;
  char relname[]="Mythos v0.1";

  // Doing the whole HUD in red bold
  attron(A_BOLD);
  attron(COLOR_PAIR(RED)); // Red on black
  // Draw boundary round screen
  mvaddch(0,0,ACS_ULCORNER); // Top left corner
  for(i=1;i<numCols-1;i++){  // Horizontal line from...
    mvaddch(0,i,ACS_HLINE);  // ... top left to top right...
    mvaddch(numRows-1,i,ACS_HLINE); // ... and bottom left to bottom right
  }
  mvaddch(0,numCols-1,ACS_URCORNER); // Then add upper right corner

  mvaddch(numRows-1,0,ACS_LLCORNER); // Lower left corner
  for(i=1;i<numRows-1;i++){          // Vertical lines from....
    mvaddch(i,0,ACS_VLINE);          // Top left to bottom left and...
    mvaddch(i,numCols-1,ACS_VLINE);  // Top right to bottom right
  }
  mvaddch(numRows-1,numCols-1,ACS_LRCORNER); // Lower right corner

  // Draw player Status are - needs to be 10 cols x 7 rows
  // Need a top tee at numCols - 11
  mvaddch(0,numCols-11,ACS_TTEE);
  // Then the vertical line
  for(i=0;i<8;i++){
    mvaddch(1+i,numCols-11,ACS_VLINE);
  }
  // Then the angle
  mvaddch(9,numCols-11,ACS_LLCORNER);
  // Then the horizontal line
  for(i=0;i<9;i++){
    mvaddch(9,numCols-10+i,ACS_HLINE);
  }
  // Finally, the Right Tee
  mvaddch(9,numCols-1,ACS_RTEE);

  // We want a line a row up from the bottom to act as a status area
  mvaddch(numRows-3,0,ACS_LTEE);
  // Then the line
  for(i=1; i<numCols-1; i++){
    mvaddch(numRows-3,i,ACS_HLINE);
  }
  // Then the right tee
  mvaddch(numRows-3,numCols-1,ACS_RTEE);

  attroff(A_BOLD);
  attroff(COLOR_PAIR(RED));

  // Let's add some status text
  attron(COLOR_PAIR(GREEN)); // Green on Black
  attron(A_BOLD);
  mvprintw(numRows-2, numCols-1-(strlen(relname)),relname);
  attroff(A_BOLD);
  attroff(COLOR_PAIR(1));

  mvprintw(numRows-2,numCols-30,"%d,%d",player.x, player.y);

  // And the player status text
  attron(A_BOLD);
  attron(COLOR_PAIR(CYAN)); // Cyan on Black
  mvprintw(1,numCols-10,"HP");
  mvprintw(2,numCols-10,"SP");
  mvprintw(3,numCols-10,"SAN");
  mvprintw(4,numCols-10,"NRG");
  mvprintw(5,numCols-10,"LVL");

  mvprintw(6,numCols-10,"XP");
  // XP needs a dividing line between aaa and bbb
  mvprintw(6,numCols-5,"/");
  attroff(COLOR_PAIR(3));

  // now fill in the stats
  attron(COLOR_PAIR(WHITE)); // White on black
  mvprintw(1,numCols-4,"%d",player.HP);
  mvprintw(2,numCols-4,"%d",player.SP);
  mvprintw(3,numCols-4,"%d",player.SAN);
  mvprintw(4,numCols-4,"%d",player.NRG);
  mvprintw(5,numCols-4,"%d",player.LVL);
  mvprintw(6,numCols-7,"%d",player.curXP);
  mvprintw(6,numCols-4,"%d",player.nextXP);

  attroff(A_BOLD);

  return EXIT_SUCCESS;
}

int drawDisplay(void){

  int xOffset,yOffset,c,x,y,sx,sy;
  int tx,ty,r;
  x=0;
  y=0;

  xOffset=screenCols/2;
  yOffset=screenRows/2;

  for(x=1;x<screenCols;x++){
    for(y=1;y<screenRows;y++){

     tx=player.x-xOffset+x;
     ty=player.y-yOffset+y;

      if(tx<0 || tx>MAXCOLS-1||ty<0||ty>MAXROWS-1){
	attron(COLOR_PAIR(WHITE));
	mvaddch(y,x,ACS_CKBOARD);
	attroff(COLOR_PAIR(WHITE));
      }
      else
	{
	  switch(world[tx][ty]){

	  case PLAIN_GRASS:
	    attron(COLOR_PAIR(GREEN));
	    attron(A_BOLD);
	    mvprintw(y,x,".");
	    attroff(COLOR_PAIR(GREEN));
	    attroff(A_BOLD);
	    break;

	  case LONG_GRASS:
	    attron(COLOR_PAIR(GREEN));
	    mvprintw(y,x,",");
	    attroff(COLOR_PAIR(GREEN));
	    break;

    case TREE:
	    attron(COLOR_PAIR(RED));
	    mvprintw(y,x,"X");
	    attroff(COLOR_PAIR(RED));
	    break;

    case SHALLOW_WATER:
	    attron(COLOR_PAIR(CYAN));
	    mvaddch(y,x,ACS_CKBOARD);
	    attroff(COLOR_PAIR(CYAN));
	    break;

    case DEEP_WATER:
	    attron(COLOR_PAIR(BLUE));
	    mvaddch(y,x,ACS_CKBOARD);
	    attroff(COLOR_PAIR(BLUE));
	    break;

	  }
	if(tx==player.x && ty==player.y){
	  // Draw the player
	  attron(COLOR_PAIR(WHITE));
	  attron(A_BOLD);
	  mvprintw(y,x,"@");
	  attroff(A_BOLD);
	  attroff(COLOR_PAIR(WHITE));
	  switch (world[tx][ty]){
	  case PLAIN_GRASS:
	    mvprintw(numRows-2,2,"Short grass     ");
	    break;
	  case LONG_GRASS:
	    mvprintw(numRows-2,2,"Long grass      ");
	    break;
	  case TREE:
	    mvprintw(numRows-2,2,"Gnarled tree    ");
	    break;
    case SHALLOW_WATER:
  	    mvprintw(numRows-2,2,"Shallow water    ");
  	    break;
        case DEEP_WATER:
    	    mvprintw(numRows-2,2,"Deep water    ");
    	    break;
	  }
	}
      }
    }
  }
  // Overlay the HUD
  drawHUD();

  // Debug Code

  // Test routine to see that it's drawing in the right place
  //attron(COLOR_PAIR(2));
  //for(x=2;x<screenCols;x++){
  //  for(y=1;y<screenRows;y++){
  //    c=rand()&5;
  //    if(c==1){
	// Long grass
  //	mvprintw(y,x,",");
  //  } else {
  //mvprintw(y,x,".");
  //  }
  //}
  //}


}
