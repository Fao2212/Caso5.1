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
	int numberOfSectors = SAMPLING_ROWS-1;//Aca hay problemas
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
	int scaleColumn = workingColumn / 5;
	int scaleRow = workingRow / 5;
	for (int zeroIndex = 0; zeroIndex < samplingSize; zeroIndex++)
	{
		int randomCol = (minZeroPos.first) + (rand()% (maxZeroPos.first - minZeroPos.first + 1));
		int randomRow = (minZeroPos.second) + (rand() %(maxZeroPos.second - minZeroPos.second + 1));
		if (pWorkingGrid[randomCol][randomRow] == 0) {
			Sector* currentSector = sectors[((randomCol % scaleColumn)) / 5][(randomRow / scaleRow) % 5];
			if (currentSector != NULL) {
				currentSector->addZero();
				totalZeros++;
			}
		}
	}
}

void Grid::calculateRanges()//Evitar los excluidos tomar en cuenta el lastD en 0
{
	double startRange = 0;
	double lastDistribution = 0;
	int index = 0;
	for (int indexRow = 0; indexRow < 5; indexRow++)
		for (int indexColumn = 0; indexColumn < 5; indexColumn++) {
			{
				if (UNUSED_SCALE_SECTORS.find(index++) == UNUSED_SCALE_SECTORS.end()) {
					lastDistribution = sectors[indexColumn][indexRow]->setDistribution(totalZeros);
					sectors[indexColumn][indexRow]->setRange(startRange, startRange + lastDistribution);
					sectors[indexColumn][indexRow]->printRange();
					startRange += lastDistribution;
				}
			}
		}
	std::cout << "---------------------------------------------" << std::endl;
}

bool Grid::compareSectors()
{
	int coincidences = 0;
	for (int index = 0; index < NUMBER_OF_TESTS; index++) {
		double randomTest = rand() / double(RAND_MAX+1.0);//Saca un numero de 0 a 1
		int posIndex = 0;
		Sector* scaleSector = NULL;
		Sector* sector = NULL;
		std::cout<<"i"<<index<<std::endl;
		std::cout << randomTest << std::endl;
		for (int indexRow = 0; indexRow < 5; indexRow++) {
			for (int indexColumn = 0; indexColumn < 5; indexColumn++) {
				if (UNUSED_SCALE_SECTORS.find(posIndex++) == UNUSED_SCALE_SECTORS.end())
				{
					if (scaleSector == NULL && scaleSectors[indexColumn][indexRow]->isInRange(randomTest))
						scaleSector = scaleSectors[indexColumn][indexRow];
					if (sector == NULL && sectors[indexColumn][indexRow]->isInRange(randomTest))
						sector = sectors[indexColumn][indexRow];
				}
			}
		}
		std::cout << "Sectors" << scaleSector->getPos() << "-" << sector->getPos()<<std::endl;
		if (scaleSector->getPos() == sector->getPos())
			coincidences++;
	}
	std::cout << "Coincidences" << coincidences<<std::endl;
	if (coincidences > 6)
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
	if (coincidencesCounter > 5)
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
