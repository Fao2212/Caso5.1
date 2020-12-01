#include "Plagiarism.h"
#include <sstream>

Plagiarism::Plagiarism(Line* pLineOne, Line* pLineTwo, int pPercentage)
{
	textOneLine = pLineOne;
	textTwoLine = pLineTwo;
	percentage = pPercentage;
}

std::string Plagiarism::toString()
{
	std::string plagString = "---------------------------------------\n";
	plagString += textOneLine->getText()+"\n";
	plagString += textTwoLine->getText() + "\n";
	plagString += +"Probability " +std::to_string(percentage);
	plagString += "---------------------------------------\n";
	return plagString;
}
