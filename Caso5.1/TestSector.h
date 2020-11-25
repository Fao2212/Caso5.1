#pragma once
#include <iostream>

class TestSector {

	int selectionProbability;
	std::pair<int, int> sectorStart;
	std::pair<int, int> sectorEnd;
public:
	TestSector(std::pair<int, int> pSectorStart, std::pair<int, int> pSectorEnd);


	std::pair<int, int> selectPos();
	bool canTest(int pNumber);
	void decreaseProbability();

};