#include "TestSector.h"

TestSector::TestSector(std::pair<int, int> pSectorStart, std::pair<int, int> pSectorEnd) {
	sectorStart = pSectorStart;
	sectorEnd = pSectorEnd;
	selectionProbability = 100;
}

std::pair<int, int> TestSector::selectPos()
{
	//Genera un random entre su pos de inicio y su pos final
	//Y retorna esa pos
}

bool TestSector::canTest(int pNumber)
{
	return pNumber > selectionProbability;
}


