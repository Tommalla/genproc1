#ifndef pktnkju_hpp
#define pktnkju_hpp

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <QImage>

const int WID = 1920, HEI = 800, W_MID = WID >> 1, H_MID = HEI >> 1, MAX = 10000;

struct pkt {
	int x, y;

	void randum();
	void make(int , int);
	int conv();

 	pkt(int = 0, int = 0);
};

void smooth(bool *, int, int, int, int);


#endif