#ifndef pktnkju_hpp
#define pktnkju_hpp

struct pkt {
	int x, y;

	void randum();
	int conv();
	bool isCorrect();

 	pkt(int = 0, int = 0);
};

#endif