#include <iostream>
#include "Grid.h"
#include <cctype>
#include <time.h>

int main () 
{
	srand((unsigned)time(0));
	Grid* grid = new Grid();
	grid->setScaleSectors();
	grid->showRanges();
	return 0;
}