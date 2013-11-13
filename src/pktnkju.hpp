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
// 	pkt();
};

// const pkt mod[8] = {pkt(-1, 1), pkt(0, 1), pkt(1, 1), pkt(1, 0), pkt(1, -1), pkt(0, -1), pkt(-1, -1), pkt(0, -1)};

struct pkt_kju {
 private:
	int qhead, qtail;
	pkt kju[WID * HEI];
 public:
	void add(pkt);	//
	pkt pop();	//
	bool empty();
	void clear();
	//int elems();
	
 	pkt_kju();
	
};

void smooth(bool *, int, int, int, int);


#endif