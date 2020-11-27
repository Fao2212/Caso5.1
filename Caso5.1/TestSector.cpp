#include "TestSector.h"

TestSector::TestSector(std::pair<int, int> pSectorStart, std::pair<int, int> pSectorEnd) {
	sectorStart = pSectorStart;
	sectorEnd = pSectorEnd;
	selectionProbability = 100;
}

std::pair<int, int> TestSector::selectPos()
{
	//Genera un random entre su pos de inicio y su pos final y retorna esa pos
	int randomX = 1+sectorStart.first + (rand() % sectorStart.first-1);
	int randomY = 1+sectorStart.second + (rand() % sectorStart.second-1);//Se puede convertir en una libreria
	return std::pair<int, int>(randomX, randomY);
}

bool TestSector::canTest(int pNumber)
{
	return pNumber > selectionProbability;
}

void TestSector::decreaseProbability()
{
	selectionProbability -= 5;
}


