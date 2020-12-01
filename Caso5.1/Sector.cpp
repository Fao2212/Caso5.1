#include "Sector.h"
#include <iostream>

Sector::Sector(int pPos)
{
	rangeStart = 0;
	rangeEnd = 0;
	zeroQuantity = 0;
	zeroDistribution = 0;
	pos = pPos;
}

Sector::Sector(float pStartRange, float pEndRange,int pPos) {

	rangeStart = pStartRange;
	rangeEnd = pEndRange;
	zeroQuantity = 0;
	zeroDistribution = 0;
	pos = pPos;

}

void Sector::setRange(float pStart, float pEnd)
{
	rangeStart = pStart;
	rangeEnd = pEnd;
}

void Sector::printRange()
{
	std::cout << rangeStart << "-" << rangeEnd<<std::endl;
}

void Sector::addZero()
{
	zeroQuantity++;
}

double Sector::setDistribution(double pTotalZeros)
{
	zeroDistribution = zeroQuantity / pTotalZeros;
	return zeroDistribution;
}

bool Sector::isInRange(double pNumber)
{
	return pNumber > rangeStart && pNumber < rangeEnd;
}

int Sector::getPos()
{
	if(this != NULL)
		return pos;
}
