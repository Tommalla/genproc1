#ifndef pktnkju_hpp
#define pktnkju_hpp
#include <qtypetraits.h>

struct Point {
	qint32 x, y;

	void randum(const qint32 width, const qint32 height);

 	Point(int = 0, int = 0);
};

namespace points {
	inline const qint32 convert(const qint32 x, const qint32 y, const qint32 width) {
		return x + y * width;
	}
};

#endif