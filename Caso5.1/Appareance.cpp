#include "Appareance.h"

Appareance::Appareance(int pPos, int pWeight)
{
	pos = pPos;
	weightByNearest = pWeight;
}

int Appareance::getWeight()
{
	return weightByNearest;
}

int Appareance::getPos()
{
	return pos;
}