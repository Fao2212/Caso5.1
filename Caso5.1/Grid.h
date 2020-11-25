#pragma once
#include <set>
#include "Sector.h"

class Grid {

	const float SCALE_RANGES[23] = { 0 ,0.02523659306 ,0.05678233438 ,0.08201892744 ,0.1545741325 ,0.1741324921,
									0.2782334385 ,0.2977917981 ,0.3703470032 ,0.41829653 ,0.4927444795,
									0.5583596215 ,0.632807571, 0.6807570978 ,0.7022082019 ,0.8063091483,
									0.8151419558,0.9192429022 ,0.9406940063 ,0.9425867508 ,0.9703470032 ,0.9981072555 ,1 };
	const int SAMPLING_ROWS = 20;
	const int SAMPLING_COLUMNS = 20;//Considerar las matrices mas pequenas que esto
	const int NUMBER_OF_TESTS = 10;
	const float SAMPLE_SIZE_PERCENTAGE = 0.15;//Esto es para el total de ceros encontrados en la primera fase
	const std::set<int> UNUSED_SCALE_SECTORS = { 1,3,22,25 };

	Sector * scaleSectors[5][5];
	Sector * sectors[5][5];
	std::pair<int, int> maxZeroPos;
	std::pair<int,int>  minZeroPos;

	int workingRow;
	int workingColumn;
	int totalZeros;

public:

	Grid();

	void setScaleSectors(); 
	void samplingGrid(int * pWorkingGrid[], int pRows, int pColumns);
	void setDimensions(std::pair<int, int> pZeroPos);
	void samplingSectors(int* pWorkingGrid[]);
	void calculateRanges();
	void compareSectors();
	void showRanges();

};