#pragma once

class Sector {

	int zeroQuantity;
	float rangeStart;
	float rangeEnd;
	float zeroDistribution;
	int pos;

public:
	Sector();
	Sector(float pStartRange, float pEndRange);
	void setRange(float pStart,float pEnd);
	void printRange();
	void addZero();
	float setDistribution(int pTotalZeros);
	bool isInRange(int pNumber);
	int getPos();
};