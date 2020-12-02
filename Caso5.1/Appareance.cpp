#include "Appareance.h"

Appareance::Appareance(int pPos, std::vector<int>  pFingerPrint)
{
	pos = pPos;
	fingerPrint = pFingerPrint;
}

std::vector<int> Appareance::getFingerPrint()
{
	return fingerPrint;
}

int Appareance::getPos()
{
	return pos;
}