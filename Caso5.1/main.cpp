#include <iostream>
#include "Grid.h"
#include <cctype>
#include <time.h>
#include "Comparator.h"

int main () 
{
	srand((unsigned)time(0));

	//Poner las dimensiones de los archivos a usar hardcodeados
	//W1 512*400
	int const ROWS = 400;
	int const COLUMNS = 512;
	std::string gridString = FileManager::readFile("w1.txt");
	int** gridContainer = new int*[ROWS];

	for (size_t i = 0; i < ROWS; ++i)
		gridContainer[i] = new int[COLUMNS];

	int index = 0;

	for (size_t i = 0; i < ROWS-1; ++i)
	{
		for (size_t j = 0; j < COLUMNS-1; ++j)
		{
			if(gridString[index] == '0')
				gridContainer[i][j] = 0;
			else
				gridContainer[i][j] = 1;
			index++;
		}
	}

	Grid* grid = new Grid();
	grid->setScaleSectors();
	grid->samplingGrid(gridContainer,ROWS,COLUMNS);//Ncesito una matriz
	grid->samplingSectors(gridContainer);
	grid->calculateRanges();

	//Comparator* comparator = new Comparator();
	//comparator->readText();
	//comparator->createSectors();
	//comparator->sampleSectors();
	//comparator->checkPlagiarism();
	//comparator->showResults();

	//grid->showRanges();
	return 0;
}