#pragma once
#include <iostream>

class Line
{

	std::string text;
	int weight;
public:
	Line(std::string pText,int pWeigth);
	int getWeight();
	std::string getText();

};

