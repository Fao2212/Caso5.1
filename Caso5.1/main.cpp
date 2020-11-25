#include <iostream>
#include "Grid.h"
#include <cctype>

int main () 
{
	Grid* grid = new Grid();
	grid->setScaleSectors();
	grid->showRanges();
	return 0;
}