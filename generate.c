#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

extern int world[MAXCOLS][MAXROWS];

int generate(void){
  
  int x,y,r,c,pass;
  
  printf("Generating the world....\n");
  
  //
  // GRASS
  //
  // First set everything to plain old grass
  printf("Planting grass...");
  c=0;
  for(x=0;x<MAXCOLS;x++){
    for(y=0;y<MAXROWS;y++){
      world[x][y]=PLAIN_GRASS;
      c++;
    }
  }
  printf("done. Made %d blocks of grass.\n",c);
  // Form clumps of long grass
  printf("Letting the grass grow...\n");
  // 'seed' the plain grass with long grass
  c=0;
  for(x=0;x<MAXCOLS;x++){
    for(y=0;y<MAXROWS;y++){
      r=rand()&63;
      if(r < 4){
	world[x][y]=LONG_GRASS;
	c++;
      }
    }
  }
  printf("done. Seeded %d patches of long grass.\n",c);
  // Pass through the grass and make long grass more likely when there's long grass beside it
  printf("Letting the long grass spread...");
  c=0;
  for(x=1;x<MAXCOLS-1;x++){
    for(y=1;y<MAXROWS-1;y++){
      if(world[x-1][y]==LONG_GRASS||
	 world[x+1][y]==LONG_GRASS||
	 world[x][y-1]==LONG_GRASS||
	 world[x][y+1]==LONG_GRASS){
	r=rand()&7;
	if(r < 5){
	  world[x][y]=LONG_GRASS;
	  c++;
	}
      }
    }
  }
  printf("done. %d new patches of long grass\n",c);
  
  //
  // TREES
  //
  // Plant some trees
  printf("Planting trees...");
  c=0;
  for(x=0;x<MAXCOLS;x++){
    for(y=0;y<MAXROWS;y++){
      r=rand()&127;
      if(r < 2){
	world[x][y]=TREE;
	c++;
      }
    }
  }
  printf("done. %d new saplings planted.\n",c);
  // Pass through the trees and make more trees more likely when there's tree beside it
  printf("Letting the trees spread...");
  c=0;
  for(x=1;x<MAXCOLS-1;x++){
    for(y=1;y<MAXROWS-1;y++){
      if(world[x-1][y]==TREE||
	 world[x+1][y]==TREE||
	 world[x][y-1]==TREE||
	 world[x][y+1]==TREE){
	r=rand()&7;
	if(r < 3){
	  world[x][y]=TREE;
	  c++;
	}
      }
    }
  }
  printf("done.\n");
  //
  // WATER
  //
  // Place some water around
  printf("Seeding deep water...");
  c=0;
  for(x=0;x<MAXCOLS;x++){
    for(y=0;y<MAXROWS;y++){
      r=rand()&16383;
      if(r < 2){
	world[x][y]=DEEP_WATER;
	c++;
      }
    }
  }
  printf("done. Seeded %d patches of deep water.\n",c);

  // Grow deep water
  printf("Growing deep water pass: ");
  pass=0;
  while(pass < 10){
    for(x=0;x<MAXCOLS;x++){
      for(y=0;y<MAXROWS;y++){
	if(world[x][y]==DEEP_WATER){
	  // Found a spot of deep water. It's likely there'll be more deep water around it - 50% chance. 25% chance
	  // Vertically as the generator is running in that direction. Ten passes over the map
	  r=rand()&7;
	  if(r < 4){
	    if(x>0){
	      world[x-1][y]=DEEP_WATER;
	    }
	  }
	  r=rand()&7;
	  if(r < 3){
	    if(y>0){
	      world[x][y-1]=DEEP_WATER;
	    }
	  }
	  r=rand()&7;
	  if(r < 4){
	    if(x < MAXCOLS){
	      world[x+1][y]=DEEP_WATER;
	    }
	  }
	  r=rand()&7;
	  if(r < 3){
	    if(y<MAXROWS){
	      world[x][y+1]=DEEP_WATER;
	    }
	  }
	}
      }
    }
    printf("%d...",pass);
    pass++;
  }
  printf("done.\n");
  // Add shallow water
  // If the deep water has grass beside it, make the grass shallow water
  for(x=0; x<MAXCOLS; x++){
    for(y=0; y<MAXROWS; y++){
      if(world[x][y] == DEEP_WATER || world[x][y] == SHALLOW_WATER) {
	if(x>0){
	if(world[x-1][y] != DEEP_WATER){
	  world[x-1][y] = SHALLOW_WATER;
	  }
	}
	if (x<MAXCOLS){
	  if(world[x+1][y] != DEEP_WATER){
	    world[x+1][y] = SHALLOW_WATER;
	  }
	}
	if(y>0){
	  if(world[x][y-1] != DEEP_WATER){
	    world[x][y-1] = SHALLOW_WATER;
	  }
	}
	if (y<MAXROWS){
	  if(world[x][y+1] != DEEP_WATER){
	    world[x][y+1] = SHALLOW_WATER;
	  }
	}
      }
    }
  }

  
  printf("Drawing a square in the top left for debugging\n");
  world[1][1]=TREE;
  world[1][2]=TREE;
  world[1][3]=TREE;
  world[2][1]=TREE;
  world[2][2]=TREE;
  world[2][3]=TREE;
  world[3][1]=TREE;
  world[3][2]=TREE;
  world[3][3]=TREE;

  return EXIT_SUCCESS;
}
