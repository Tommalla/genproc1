#ifndef CALC_HPP
#define CALC_HPP
#include "Map.hpp"

const qint32 maxProb = 10000;

namespace generators {
	void cellular(Map& map, const qint32 startingPoints, const qint32 expProb);
	void perlinsNoise(Map& map, const qint16 accuracy, const qint8 minHeight, const qint8 maxHeight);
};

namespace fillers {
	void standard(Map& map);
};

namespace filters {
	void smooth(Map& map, qint32 field, qint32 force);
	void removePointlessWater(Map& map, const qint32 pointless);
	void rationalize(Map& map, const qint32 frame);
};

#endif