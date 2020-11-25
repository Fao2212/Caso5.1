#pragma once

class Sector {

	int zeroQuantity;
	float rangeStart;
	float rangeEnd;
	float zeroDistribution;

public:
	Sector();
	Sector(float pStartRange, float pEndRange);
	int setRange(float pStart,float pEnd);
	void printRange();
	void addZero();
	float setDistribution(int pTotalZeros);

};