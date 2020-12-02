#pragma once
#include <iostream>
#include <set>
#include "Appareance.h"
#include <vector>
#include <algorithm>

class Word {

	std::string word;
	std::vector<Appareance*> textOneAppareances;
	std::vector<Appareance*> textTwoAppareances;

public:

	std::vector<std::pair<int, int>> getCoincidences();
	bool compareWeights(int pWeightOne, int pWeightTwo);
	bool compareFingerPrints(std::vector<int> pFingerPrintOne, std::vector<int> pFingerPrintTwo);
	void addToTextPositions(std::string pText, Appareance* pPos);
	std::vector<Appareance*> getTextOneAppareances();

};