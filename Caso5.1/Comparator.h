#pragma once
#include <iostream>
#include<map>
#include"Word.h"
#include "TextSector.h"
#include <vector>
#include "Line.h"
#include "Plagiarism.h"
#include "FileManager.h"

class Comparator {

	std::string text1;
	std::string text2;
	std::map<std::string, Word*> wordApparence;
	static const int NUMBER_OF_NEAR_CHARACTERS = 15;
	static const int NUMBER_OF_SECTORS = 20;
	TextSector* textSectors1[NUMBER_OF_SECTORS];
	TextSector* textSectors2[NUMBER_OF_SECTORS];
	std::vector<Plagiarism*> plagiarismList;
public:
	void readText();
	void createSectors();
	void sampleSectors();
	void checkPlagiarism();
	void isPlagiarism(int pStartPosOne,int pStartPosTwo);
	Line * getLine(int pText,int pInitialPos);
	void showResults();
};