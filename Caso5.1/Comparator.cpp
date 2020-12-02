#include "Comparator.h"

Comparator::Comparator()
{
	fingerPrintManager = new FingerPrint();
}


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
		textSectors1[index] = new TextSector(std::pair<int,int>(currentRangeOne,currentRangeOne+textOneSectorSize),&wordApparence,text1,"text1",fingerPrintManager);
		textSectors2[index] = new TextSector(std::pair<int, int>(currentRangeTwo, currentRangeTwo + textTwoSectorSize), &wordApparence, text2,"text2", fingerPrintManager);
		currentRangeOne += textOneSectorSize;
		currentRangeTwo += textTwoSectorSize;
	}

}

void Comparator::sampleSectors()
{
	std::cout << "Start Sampling";
	for (int index = 0; index < NUMBER_OF_SECTORS; index++)
	{
		textSectors1[index]->sample();
		textSectors2[index]->sample();
	}
	std::cout << "End Sampling";
}

void Comparator::checkPlagiarism()//Despues del sampleo primero del par es texto uno
{
	std::cout << "Start Check" << std::endl;
	std::vector<std::pair<int, int>> posibleCoincidences;
	for (const auto& word : wordApparence) 
	{
		posibleCoincidences = word.second->getCoincidences();
		for (const auto& testCoincidence :posibleCoincidences) 
		{
			isPlagiarism(testCoincidence.first, testCoincidence.second);
		}
	}
	std::cout << "End Check" << std::endl;
}

void Comparator::isPlagiarism(int pStartPosOne, int pStartPosTwo) //Rehacer con Word
{
	Line * lineOne = getLine(0,pStartPosOne);
	Line* lineTwo = getLine(1, pStartPosTwo);
	std::vector<int> biggestVector;
	std::vector<int> workVector;
	int coincidences = 0;
	if (lineOne->getFingerPrint().size() >= lineTwo->getFingerPrint().size()) {
		biggestVector = lineOne->getFingerPrint();
		workVector = lineTwo->getFingerPrint();
	}
	else {
		biggestVector = lineTwo->getFingerPrint();
		workVector = lineOne->getFingerPrint();
	} 
	for (auto const& value : workVector) {
		if (std::find(biggestVector.begin(), biggestVector.end(), value) != biggestVector.end())
			coincidences++;
	}
	double percentage = ((coincidences / (double)(workVector.size()/2.0)) * 100.0);
	//relacion de tamano
	//cantidad de coincidencias
	std::cout << coincidences<<"-"<<workVector.size()<<std::endl;
	std::cout << "Perc: " << percentage<<std::endl;
	if (percentage >= 40)
		plagiarismList.push_back(new Plagiarism(lineOne, lineTwo,percentage));
}

Line* Comparator::getLine(int pText, int pInitialPos)
{
	std::string workingText;
	int sidesMovement = 30;		
	int maxRange = workingText.size() - 1;
	int minRange = 0;						//Esto puede ir definido por defecto en la clase
	int fingerPrintInit = pInitialPos - 40;
	int fingerPrintEnd = pInitialPos + 40;
	if (pText == 0)
		workingText = text1;
	else
		workingText = text2;
	if (fingerPrintInit < minRange)
		fingerPrintInit = minRange;
	if (fingerPrintEnd > maxRange)
		fingerPrintEnd = maxRange;
	std::string preFingerPrint = workingText.substr(fingerPrintInit, fingerPrintEnd - fingerPrintInit);
	std::vector<int> fingerPrint = fingerPrintManager->getFingerPrint(preFingerPrint);
	Line* line =  new Line(preFingerPrint, fingerPrint);
	return line;
}

void Comparator::showResults()
{
	std::cout << "Showing";
	for (auto const& plag : plagiarismList) {
		std::cout<<plag->toString();
	}
}

void Comparator::showHash() {
	for (auto const& word : wordApparence) {
		std::cout<<"[" << word.first << std::endl;
		for (auto const& c: word.second->getTextOneAppareances()) {
			std::cout << c ->getPos()<< "-" << std::endl;
		}
		std::cout << "]" << std::endl;
	}
}