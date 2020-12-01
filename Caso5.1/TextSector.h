#pragma once
#include <iostream>
#include<map>
#include "Word.h"
#include "Appareance.h"


class TextSector {//Necesita saber cual es su texto
	
	std::string text;
	std::string originText;
	std::pair<int, int> range;
	std::map<std::string, Word*> * wordApparence;
	const double SAMPLING_PERCENTAGE = 0.15;

public:
	TextSector(std::pair<int, int>pRange, std::map<std::string, Word*>* pWordApparence, std::string pText,std::string pOriginText);

	void sample();//Un ciclo del tamano de sampling que sacara pos de palabras al azar y llamara a getRaW para obtener la palabra y guardarla en el hash
	void getRandomWord(); //Metodo para encontrar donde esta la palabra segun la posicion obtenida
	int getWeight(int pInitPos, int pEndPos);//Calcula un peso dependiendo de los caracteres establecidos para la palabra obtenida

};