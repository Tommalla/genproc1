#include "pktnkju.hpp"

void pkt::randum()
{
	x = rand() % WID;
	y = rand() % HEI;
}

void pkt::make(int a, int b)
{
	x = a;
	y = b;
}

pkt::pkt(int a, int b)
{
	x = a;
	y = b;
}
inline int pkt::conv()
{
	return x + y * WID;
}

//BLABLLLLLGH

void pkt_kju::add(pkt a)
{
	kju[qhead++] = a;
}

pkt pkt_kju::pop()
{
	return kju[qtail++];
}

bool pkt_kju::empty()
{
	return qhead == qtail;
}

void pkt_kju::clear()
{
	qhead = qtail = 0;
}

pkt_kju::pkt_kju()
{
	qhead = qtail = 0;
}

void smooth(bool * field, int area, int powah, int wid, int hei)
{
	bool strawfield[wid * hei];
	for (int i = 0; i < wid * hei; i++)
		strawfield[i] = 0;
	int acumulator = 0, noenoland = area * area - powah;
	pkt pom;
	for (int i = 0; i < wid - area; i++)
		for (int j = 0; j < hei - area; j++)
		{
			for (int e = 0; e < area; e++)
				for (int f = 0; f < area; f++)
				{
					pom.make(i + e, j + f);
					acumulator += field[pom.conv()];
				}
			if (acumulator >= noenoland)
				for (int e = 0; e < area; e++)
					for (int f = 0; f < area; f++)
					{
						pom.make(i + e, j + f);
						strawfield[pom.conv()] = 1;
					}
			acumulator = 0;
		}
	for (int i = 0; i < wid * hei; i++)
	{
		if (strawfield[i])
			field[i] = 1;
	}
}

