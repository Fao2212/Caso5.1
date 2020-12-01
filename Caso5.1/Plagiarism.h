#pragma once
#include "Line.h"

class Plagiarism
{

	Line* textOneLine;
	Line* textTwoLine;
	int	percentage;

public:

	Plagiarism(Line * pLineOne,Line * pLineTwo,int pPercentage);
	std::string toString();

};

