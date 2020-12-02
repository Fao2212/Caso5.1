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
	plagString += "[LineOne]: \n"+textOneLine->getText()+"\n";
	plagString += "[LineTwo]: \n" + textTwoLine->getText() + "\n";
	plagString += +"Probability " +std::to_string(percentage)+"\n";
	plagString += "---------------------------------------\n\n";
	return plagString;
}
