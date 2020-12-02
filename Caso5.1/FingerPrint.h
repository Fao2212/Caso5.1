#pragma once
#include <map>
#include <iostream>
#include <vector>


class FingerPrint							//Queria que fuera estatico pero la generacion del consecutivo me complico
{
public:
	int consecutive = 0;
	std::map<std::string, int> idWords;		//Guarda para una palabra un id unico que servira para crear el fingerprint
	std::vector<int> getFingerPrint(std::string);

};

