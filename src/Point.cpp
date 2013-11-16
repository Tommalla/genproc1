#include <cstdlib>
#include "Point.hpp"
#include "calc.hpp"

void Point::randum(const qint32 width, const qint32 height) {
	x = rand() % width;
	y = rand() % height;
}

Point::Point(int a, int b) {
	x = a;
	y = b;
}


