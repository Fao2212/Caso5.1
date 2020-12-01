#pragma once

class Sector {

	int zeroQuantity;
	float rangeStart;
	float rangeEnd;
	float zeroDistribution;
	int pos;

public:
	Sector(int pPos);
	Sector(float pStartRange, float pEndRange, int pPos);
	void setRange(float pStart,float pEnd);
	void printRange();
	void addZero();
	float setDistribution(int pTotalZeros);
	bool isInRange(int pNumber);
	int getPos();
};