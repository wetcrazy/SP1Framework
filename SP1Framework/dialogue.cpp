#include "dialogue.h"


void dialogue(Console * handle )
{

	
    COORD c = handle->getConsoleSize();
	c.Y=8;
	c.X = c.X / 2 - 4;
	handle->writeToBuffer(c, "testing", 0x03);
}
