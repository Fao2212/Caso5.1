#include "Comparator.h"

void Comparator::readText()
{
	text1 = FileManager::readFile("Texto1.txt");//Cuidado con qu eno se abra o errores
	text2 = FileManager::readFile("Texto3.txt");
}

void Comparator::createSectors()
{

	int textOneSectorSize = (text1.size()-1) / NUMBER_OF_SECTORS;
	int textTwoSectorSize = (text2.size()-1) / NUMBER_OF_SECTORS;
	int currentRangeOne = 0;
	int currentRangeTwo = 0;
	for (int index = 0; index < NUMBER_OF_SECTORS; index++) 
	{
		textSectors1[index] = new TextSector(std::pair<int,int>(currentRangeOne,currentRangeOne+textOneSectorSize),&wordApparence,text1,"text1");
		textSectors2[index] = new TextSector(std::pair<int, int>(currentRangeTwo, currentRangeTwo + textTwoSectorSize), &wordApparence, text2,"text2");
		currentRangeOne += textOneSectorSize;
		currentRangeTwo += textTwoSectorSize;
	}

}

void Comparator::sampleSectors()
{
	for (int index = 0; index < NUMBER_OF_SECTORS; index++)
	{
		textSectors1[index]->sample();
		textSectors2[index]->sample();
	}
}

void Comparator::checkPlagiarism()//Despues del sampleo primero del par es texto uno
{
	std::vector<std::pair<int, int>> posibleCoincidences;
	for (const auto& word : wordApparence) 
	{
		posibleCoincidences = word.second->getCoincidences();
		for (const auto& testCoincidence :posibleCoincidences) 
		{
			isPlagiarism(testCoincidence.first, testCoincidence.second);
		}
	}
}

void Comparator::isPlagiarism(int pStartPosOne, int pStartPosTwo)
{
	Line * lineOne = getLine(0,pStartPosOne);
	Line* lineTwo = getLine(1, pStartPosTwo);
	int pWeightOne = lineOne->getWeight();
	int pWeightTwo = lineTwo->getWeight();
	int mayor;
	int menor;
	if (pWeightOne >= pWeightTwo) {
		mayor = pWeightOne;
		menor = pWeightTwo;
	}
	else {
		mayor = pWeightTwo;
		menor = pWeightOne;
	} 
	int percentage = ((menor / mayor) * 100);
	if (percentage >= 75)
		plagiarismList.push_back(new Plagiarism(lineOne, lineTwo,percentage));
}

Line* Comparator::getLine(int pText, int pInitialPos)
{
	int pEndPos = pInitialPos;
	std::string workingText;
	int weigth = 0;
	if (pText == 0)
		workingText = text1;
	else
		workingText = text2;

	if (pInitialPos != 0)
	{
		 while (pInitialPos > 0 && workingText[pInitialPos] != '.') 
		 {

			pInitialPos--;
			weigth = +workingText[pInitialPos];
		}
	}
	if (pEndPos != workingText.size() - 1)
	{
		 while (pEndPos < workingText.size() - 1 && workingText[pEndPos] != '.')
		{
			pEndPos++;
			weigth = +workingText[pEndPos];
		}
		
	}
	Line* line =  new Line(workingText.substr(pInitialPos, pEndPos-pInitialPos), weigth);
	return line;
}

void Comparator::showResults()
{
	std::cout << plagiarismList.size();
	for (auto const& plag : plagiarismList) {
		std::cout<<plag->toString();
	}
}
