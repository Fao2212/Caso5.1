#pragma once
#include <iostream>

class Line
{

	std::string text;
	double weight;
public:
	Line(std::string pText,double pWeigth);
	double getWeight();
	std::string getText();

};

