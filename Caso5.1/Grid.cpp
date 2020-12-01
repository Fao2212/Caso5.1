#include "Grid.h"
#include "TestSector.h"
#include <vector>

Grid::Grid() {
	setScaleSectors();
}

void Grid::setScaleSectors()//Setea el modelo de comparacion
{
	int rangeSetterIndex = 0;
	int index = 0;
	for (int indexRow = 0; indexRow < 5; indexRow++)
		for (int indexColumn = 0; indexColumn < 5; indexColumn++) {
			{
				if (UNUSED_SCALE_SECTORS.find(index++) == UNUSED_SCALE_SECTORS.end()) {
					sectors[indexColumn][indexRow] = new Sector(index);
					scaleSectors[indexColumn][indexRow] = new Sector(SCALE_RANGES[rangeSetterIndex], SCALE_RANGES[rangeSetterIndex + 1],index);
					rangeSetterIndex++;
				}
				else
				{
					scaleSectors[indexColumn][indexRow] = NULL;
					sectors[indexColumn][indexRow] = NULL;
				}
			}
	}
}

void Grid::samplingGrid(int* pWorkingGrid[], int pRows, int pColumns) //Basta con obtener el maximo y minimo de los concentrados de 0
{
	int maxZeros = pRows * pColumns;
	int workingTestRows = pRows / SAMPLING_ROWS;
	int workingTestColumns = pColumns / SAMPLING_COLUMNS;
	int numberOfSectors = SAMPLING_ROWS-1;
	double samplingSize = maxZeros * SAMPLE_SIZE_PERCENTAGE;
	int xRange = 0;
	int yRange = 0;
	std::pair<int, int> searchPos;
	std::vector<TestSector*> testSectors;

	for (int sectorsIndex = 0; sectorsIndex < numberOfSectors; sectorsIndex++) {
		std::pair<int, int> sectorStart(xRange, xRange + workingTestRows);
		std::pair<int, int> sectorEnd(yRange, yRange + workingTestColumns);
		testSectors.push_back(new TestSector(sectorStart, sectorEnd));
		xRange += workingTestRows;
		yRange += workingTestColumns;
	}

	for (int zeroIndex = 0; zeroIndex < samplingSize; zeroIndex++) {
		int randomTest = rand()%101; //Ajustar el seed
		for (auto const& testSector:testSectors)
		{
			if (testSector->canTest(randomTest)) {
				searchPos = testSector->selectPos();
				std::cout << searchPos.first << "-" << searchPos.second<<std::endl;
				if (pWorkingGrid[searchPos.first][searchPos.second] == 0) {
					setDimensions(searchPos);
				}
				else 
					testSector->decreaseProbability();
			}
				
		}
	}
	workingRow = maxZeroPos.first - minZeroPos.first;
	workingColumn = maxZeroPos.second - minZeroPos.second;
}

void Grid::setDimensions(std::pair<int, int> pZeroPos)//Que es mas caro? Una comparacion con cada 0 que obtengo o hacer un vector de posciciones y sacar el minimo y el maximo
{
	if (pZeroPos.first >= maxZeroPos.first && pZeroPos.second >= maxZeroPos.second)
		maxZeroPos = pZeroPos;
	else {
		if (pZeroPos.first <= maxZeroPos.first && pZeroPos.second <= maxZeroPos.second) {
			minZeroPos = pZeroPos;
		}
	}
}

void Grid::samplingSectors(int* pWorkingGrid[])//Tengo que tomar en cuenta los sectores que no tienen ceros en el modelo?
{
	int maxZeros = workingRow * workingColumn;
	int samplingSize = maxZeros * SAMPLE_SIZE_PERCENTAGE;
	for (int zeroIndex = 0; zeroIndex < samplingSize; zeroIndex++)
	{
		int randomX = (minZeroPos.first) + (rand()% (maxZeroPos.first - minZeroPos.first + 1));
		int randomY = (minZeroPos.second) + (rand() %(maxZeroPos.second - minZeroPos.second + 1));
		if (pWorkingGrid[randomX][randomY] == 0) {
			randomX -= minZeroPos.first;
			randomY -= minZeroPos.second;
			sectors[randomX / workingColumn/5][randomY % workingRow%5]->addZero();
			totalZeros++;
		}
	}
}

void Grid::calculateRanges()//Evitar los excluidos
{
	float startRange = 0;
	float lastDistribution = 0;
	int index = 0;
	for (int indexRow = 0; indexRow < 5; indexRow++)
		for (int indexColumn = 0; indexColumn < 5; indexColumn++) {
			{
				if (UNUSED_SCALE_SECTORS.find(index++) == UNUSED_SCALE_SECTORS.end()) {
					std::cout << index<<std::endl;
					lastDistribution = sectors[indexRow][indexColumn]->setDistribution(totalZeros);
					sectors[indexRow][indexColumn]->setRange(startRange, startRange + lastDistribution);
					startRange += lastDistribution;
				}
			}
		}
}

bool Grid::compareSectors()
{
	Sector* scaleSector = NULL;
	Sector* sector = NULL;
	int coincidences = 0;
	for (int index = 0; index < NUMBER_OF_TESTS; index++) {
		int randomTest = rand();//Saca un numero de 0 a 1
		for (int indexRow = 0; indexRow < 5; indexRow++) {
			for (int indexColumn = 0; indexColumn < 5; indexColumn++) {
				if (UNUSED_SCALE_SECTORS.find(index++) == UNUSED_SCALE_SECTORS.end())
				{
					if (scaleSector == NULL && scaleSectors[indexRow][indexColumn]->isInRange(randomTest))
						scaleSector = scaleSectors[indexRow][indexColumn];
					if (sector == NULL && sectors[indexRow][indexColumn]->isInRange(randomTest))
						sector = sectors[indexRow][indexColumn];
				}
			}
		}
		if (scaleSector->getPos() == sector->getPos())
			coincidences++;
	}
	if (coincidences > 7)
		return true;
	return false;
}

bool Grid::resolve()
{
	int coincidencesCounter = 0;
	for (int index = 0; index < 10; index++) {
		if (compareSectors())
			coincidencesCounter++;
	}
	if (coincidencesCounter > 7)
		return true;
	return false;
}




void Grid::showRanges()
{
	int index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (UNUSED_SCALE_SECTORS.find(index++) == UNUSED_SCALE_SECTORS.end())
				scaleSectors[i][j]->printRange();
		}
	}
}
