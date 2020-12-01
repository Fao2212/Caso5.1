#include "TextSector.h"

TextSector::TextSector(std::pair<int, int> pRange, std::map<std::string, Word*>* pWordApparence, std::string pText,std::string pOriginText)
{
	range = pRange;
	wordApparence = pWordApparence;
	text = pText;
	originText = pOriginText;
}

void TextSector::sample()
{
	
	int sectorSize = range.second - range.first;
	int sampligSize = sectorSize * SAMPLING_PERCENTAGE;
	for (int index = 0; index < sampligSize; index++) {
		getRandomWord();
	}

}

void TextSector::getRandomWord()
{
	
	int randomPos = (range.first) + (rand() % (range.second-range.first+1));				//Random correcto para rangos
	int wordInit = randomPos;
	int wordEnd = randomPos;
	if (wordInit != 0)																		//Aca encuentro los "limites de la palabra"
	{
		do
		{
			wordInit--;
		} while (wordInit > 0  && text[wordInit] != ' ' && text[wordInit] != '\n');			//Esta condicion de parada es muy prblematica
	}
	if (wordEnd != text.size() - 1)
	{
		do
		{
			wordEnd++;
		} while (wordEnd < text.size() - 1 &&  text[wordEnd] != ' ' && text[wordEnd] != '\n');
	}
	std::string word = text.substr(wordInit, (wordEnd - wordInit));
	Word* currentWord;																		//Crea word como cajon de aparciciones de la palabra
	int wordWeigth = getWeight(wordInit,wordEnd);
	Appareance* appareance = new Appareance(wordInit,wordWeigth);							//Apariciones lleva el peso y posicion de aparicion

	if (wordApparence->find(word) == wordApparence->end()) {
		currentWord = new Word();
		currentWord->addToTextPositions(originText, appareance);
		wordApparence->insert(std::pair<std::string, Word*>(word, currentWord));
	}
	else {
		currentWord = wordApparence->at(word);
		currentWord->addToTextPositions(originText, appareance);
	}
}

int TextSector::getWeight(int pInitPos, int pEndPos)										//Este getWight no funciona para dar un verdadero peso
{
	int weigth = 0;																			//Puedo crear otro hash que le de a las palabras un id
	int leftWordCounter = 0;																//Y que las probabilidades dependan de el "fingerprint"
	int rightWordCounter = 0;
	int numberOfWords = 3;
	for (int index = 0; index < 15; index++) {
		pInitPos--;
		pEndPos++;
		if (pInitPos >= 0 && leftWordCounter <= numberOfWords)
		{
			if (text[pInitPos] == ' ')
				leftWordCounter++;
			else
				weigth += text[pInitPos];
		}
		if (pEndPos <= text.size() && rightWordCounter <= numberOfWords)
		{
			if (text[pEndPos] == ' ')
				rightWordCounter++;
			else
				weigth += text[pEndPos];
		}
	}
	return weigth;
}
