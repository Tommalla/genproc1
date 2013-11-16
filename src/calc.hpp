#ifndef CALC_HPP
#define CALC_HPP
#include "Map.hpp"

const qint32 maxProb = 10000;

namespace generators {
	void cellular(Map& map, const qint32 startingPoints, const qint32 expProb);
	//Map perlinsNoise(const qint32 width, const qint32 height);
};

namespace filters {
	void smooth(Map& map, qint32 field, qint32 force);
	void removePointlessWater(Map& map, const qint32 pointless);
}

#endif