#include "Sector.h"
#include <iostream>

Sector::Sector()
{
	rangeStart = 0;
	rangeEnd = 0;
	zeroQuantity = 0;
	zeroDistribution = 0;
}

Sector::Sector(float pStartRange, float pEndRange) {

	rangeStart = pStartRange;
	rangeEnd = pEndRange;
	zeroQuantity = 0;
	zeroDistribution = 0;

}

void Sector::printRange()
{
	std::cout << rangeStart << "-" << rangeEnd<<std::endl;
}

void Sector::addZero()
{
	zeroQuantity++;
}

float Sector::setDistribution(int pTotalZeros)
{
	return zeroDistribution = zeroQuantity / pTotalZeros;
}
