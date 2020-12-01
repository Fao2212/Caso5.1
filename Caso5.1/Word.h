#pragma once
#include <iostream>
#include <set>
#include "Appareance.h"
#include <vector>

class Word {

	std::string word;
	std::set<Appareance*> textOneAppareances;
	std::set<Appareance*> textTwoAppareances;

public:

	std::vector<std::pair<int, int>> getCoincidences();
	bool compareWeights(int pWeightOne, int pWeightTwo);
	void addToTextPositions(std::string pText, Appareance* pPos);

};