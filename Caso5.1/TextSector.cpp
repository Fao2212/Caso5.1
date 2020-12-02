#include "TextSector.h"

TextSector::TextSector(std::pair<int, int> pRange, std::map<std::string, Word*>* pWordApparence, std::string pText,std::string pOriginText,FingerPrint * pFingerPrintManager)
{
	range = pRange;
	wordApparence = pWordApparence;
	text = pText;
	originText = pOriginText;
	fingerPrintManager = pFingerPrintManager;
}

void TextSector::sample()
{
	
	int sectorSize = range.second - range.first;
	int sampligSize = sectorSize * SAMPLING_PERCENTAGE;
	for (int index = 0; index < sampligSize; index) {
		if (getRandomWord())
			index++;
	}

}

bool TextSector::getRandomWord()//TODO:Si es espacio o enter moverse a la izquierda
{
	
	int randomPos = (range.first) + (rand() % (range.second-range.first+1));				//Random correcto para rangos
	if (text[randomPos] == ' ' || text[randomPos] == '\n' || text[randomPos] == '\r\n')
		randomPos--;
	int wordInit = randomPos;
	int wordEnd = randomPos;
	while (wordInit > 0)
	{
		if (text[wordInit] == ' ' || text[wordInit] == '\n' || text[wordInit] == '\r\n')
		{
			wordInit++;
			break;
		}
		wordInit--;
	}
	while (wordEnd < text.size() - 1)
	{
		if (text[wordEnd] == ' ' || text[wordEnd] == '\n' || text[wordEnd] == '\r\n')
		{
			break;
		}
		wordEnd++;
	}
	std::string word = text.substr(wordInit, (wordEnd - wordInit));
	if (word.size() > 5)
	{
		Word* currentWord;																		//Crea word como cajon de aparciciones de la palabra
		int wordWeigth = getWeight(wordInit, wordEnd);
		std::vector<int> fingerPrint = prepareFingerPrint(wordInit);
		Appareance* appareance = new Appareance(wordInit, fingerPrint);							//Apariciones lleva el peso y posicion de aparicion

		if (wordApparence->find(word) == wordApparence->end())
		{
			currentWord = new Word();
			currentWord->addToTextPositions(originText, appareance);
			wordApparence->insert(std::pair<std::string, Word*>(word, currentWord));
		}
		else
		{
			currentWord = wordApparence->at(word);
			currentWord->addToTextPositions(originText, appareance);
		}
		return true;
	}
	return false;
}

int TextSector::getWeight(int pInitPos, int pEndPos)										//Este getWight no funciona para dar un verdadero peso (YA NO ES UTILIZADO)
{																							//Se deja de comparacion
	int weigth = 0;																			//Puedo crear otro hash que le de a las palabras un id
	int leftWordCounter = 0;																//Y que las probabilidades dependan de el "fingerprint"
	int rightWordCounter = 0;
	int numberOfWords = 3;
	for (int index = 0; index < 15; index++) {												//Pense en solo mover las pos de memoria pero complicaria el 
		pInitPos--;																			//Caso de los nulos
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

std::vector<int> TextSector::prepareFingerPrint(int pInitPos)
{
	int sidesMovement = 50;
	int maxRange = text.size() - 1;
	int minRange = 0;						//Esto puede ir definido por defecto en la clase
	int fingerPrintInit = pInitPos - sidesMovement; 
	int fingerPrintEnd = pInitPos + sidesMovement;
	if (fingerPrintInit < minRange)
		fingerPrintInit = minRange;
	if (fingerPrintEnd > maxRange)
		fingerPrintEnd = maxRange;
	std::string preFingerPrint =  text.substr(fingerPrintInit, fingerPrintEnd - fingerPrintInit);
	return fingerPrintManager->getFingerPrint(preFingerPrint);
}
