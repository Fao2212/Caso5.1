#include <iostream>
#include "Grid.h"
#include <cctype>
#include <time.h>
#include "Comparator.h"

int main () 
{
	srand((unsigned)time(0));

	Grid* grid = new Grid();
	grid->setScaleSectors();

	//Comparator* comparator = new Comparator();
	//comparator->readText();
	//comparator->createSectors();
	//comparator->sampleSectors();
	//comparator->checkPlagiarism();
	//comparator->showResults();

	//grid->showRanges();
	return 0;
}