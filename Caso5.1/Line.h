#pragma once
#include <iostream>
#include <vector>

class Line
{

	std::string text;
	double weight;
	std::vector<int> fingerPrint;

public:
	Line(std::string pText, std::vector<int> pfingerPrint);
	double getWeight();
	std::string getText();
	std::vector<int> getFingerPrint();

};

