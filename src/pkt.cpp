#include <cstdlib>
#include "pkt.hpp"
#include "calc.hpp"

void pkt::randum()
{
	x = rand() % WID;
	y = rand() % HEI;
}

pkt::pkt(int a, int b)
{
	x = a;
	y = b;
}

int pkt::conv()
{
	return x + y * WID;
}

bool pkt::isCorrect()
{
	return x >= 0 && x < WID && y >= 0 && y < HEI;
}

