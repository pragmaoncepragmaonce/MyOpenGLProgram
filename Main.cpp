#include "Game.h"



int main()
{
	Game game("SILENT HILL", 600, 400, 4, 5, false);

	//MAIN LOOP
	while (!game.getWindowShouldClose())
	{
		//UPDATE INPUT --- 
		game.update();
		game.render();
	}
	
	return 22;
}