#ifndef CALC_HPP
#define CALC_HPP

const int WID = 1920, HEI = 800, W_MID = WID >> 1, H_MID = HEI >> 1, MAX = 10000;

void generate(bool* land, const int startingPoints, const int expProb);

void smooth(bool *, int, int, int, int);

void removePointlessWater(bool * land, int pointless = 3);

#endif