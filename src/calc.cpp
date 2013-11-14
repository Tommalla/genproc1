#include "pkt.hpp"
#include "calc.hpp"
#include <QQueue>
#include <QVector>

void generate(bool* land, const int startingPoints, const int expProb)
{
	QQueue<pkt> kolej;
	pkt a, b;
	for (int i = 0; i < startingPoints; i++)
	{
		a.randum();
		kolej.push_back(a);
		land[a.conv()] = true;
	}

	while (!kolej.empty())
	{
		a = kolej.front();
		kolej.pop_front();
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				b = pkt(a.x + i, a.y + j);
				if (!land[b.conv()] && b.x >= 0 && b.x < WID && b.y >= 0 && b.y < HEI && rand() % MAX < expProb)
				{
					land[b.conv()] = true;
					kolej.push_back(b);
				}
			}
	}
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
					pom = pkt(i + e, j + f);
					acumulator += field[pom.conv()];
				}
			if (acumulator >= noenoland)
				for (int e = 0; e < area; e++)
					for (int f = 0; f < area; f++)
					{
						pom = pkt(i + e, j + f);
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

void removePointlessWater(bool * land, int pointless) {
	int id[WID * HEI];
	QVector<QVector<pkt>> lakes;
	QQueue<pkt> q;
	pkt p, next;
	int curr = 1;
	int idx;

	int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i < WID; ++i)
		for (int j = 0; j < HEI; ++j) {
			p = pkt(i, j);
			idx = p.conv();
			if (land[idx] == false && id[idx] == 0) {
				id[idx] = curr++;
				QVector<pkt> tmp;
				tmp.push_back(p);
				lakes.push_back(tmp);
				q.push_back(p);

				while (!q.empty()) {
					p = q.front();
					q.pop_front();

					for (int k = 0; k < 4; ++k) {
						next = pkt(p.x + dir[k][0], p.y + dir[k][1]);
						if (next.isCorrect()) {
							idx = next.conv();

							if (land[idx] == false && id[idx] == 0) {
								id[idx] = id[p.conv()];
								lakes[id[idx] - 1].push_back(next);
								q.push_back(next);
							}
						}
					}
				}
			}
		}

	for (int i = 0; i < lakes.size(); ++i)
		if (lakes[i].size() <= pointless)
			for (pkt p: lakes[i])
				land[p.conv()] = true;
}