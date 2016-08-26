#include "_interactable.h"
#include "exit.h"
#include "map.h"


size_t O_Max = 1;

void randomExit()
{
	
	
	 size_t X = 0;
	 size_t Y = 0;
	 size_t O_spawn = 0;
	
	 static bool hasSpawn = false;

	
	 if (!hasSpawn){

		 X = rand() % (mapWidth - 1);
		 Y = rand() % (mapHeight - 1);
		 g_Map[Y][X] = 'o';

		 hasSpawn = true;
	 }
	  
	 
	
			
		
}
		
	
