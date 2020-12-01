#pragma once

class Sector {

	int zeroQuantity;
	float rangeStart;
	float rangeEnd;
	double zeroDistribution;
	int pos;

public:
	Sector(int pPos);
	Sector(float pStartRange, float pEndRange, int pPos);
	void setRange(float pStart,float pEnd);
	void printRange();
	void addZero();
	double setDistribution(double pTotalZeros);
	bool isInRange(double pNumber);
	int getPos();
};