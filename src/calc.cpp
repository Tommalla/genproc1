#include <QQueue>
#include <QVector>
#include "Point.hpp"
#include "calc.hpp"

void generators::cellular(Map& map, const qint32 startingPoints, const qint32 expProb) {
	QQueue<Point> kolej;
	Point a, b;

	for (qint32 i = 0; i < map.getWidth(); ++i)
		for (qint32 j = 0; j < map.getHeight(); ++j) {
			map.heightAt(i, j) = -1;
			map.typeAt(i, j) = Type::WATER;
		}

	for (int i = 0; i < startingPoints; i++) {
		a.randum(map.getWidth(), map.getHeight());
		kolej.push_back(a);
		map.heightAt(a.x, a.y) = 0;
		map.typeAt(a.x, a.y) = Type::LAND;
	}

	while (!kolej.empty()) {
		a = kolej.front();
		kolej.pop_front();
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				b = Point(a.x + i, a.y + j);
				if (map.isPointValid(b.x, b.y) && map.heightAt(b.x, b.y) == -1 && rand() % maxProb < expProb)
				{
					map.heightAt(b.x, b.y) = 0;
					map.typeAt(b.x, b.y) = Type::LAND;
					kolej.push_back(b);
				}
			}
	}

}

void filters::smooth(bool * field, int area, int powah, int wid, int hei) {
	/*
	bool strawfield[wid * hei];
	for (int i = 0; i < wid * hei; i++)
		strawfield[i] = 0;
	int acumulator = 0, noenoland = area * area - powah;
	Point pom;
	for (int i = 0; i < wid - area; i++)
		for (int j = 0; j < hei - area; j++)
		{
			for (int e = 0; e < area; e++)
				for (int f = 0; f < area; f++)
				{
					pom = Point(i + e, j + f);
					acumulator += field[pom.conv()];
				}
			if (acumulator >= noenoland)
				for (int e = 0; e < area; e++)
					for (int f = 0; f < area; f++)
					{
						pom = Point(i + e, j + f);
						strawfield[pom.conv()] = 1;
					}
			acumulator = 0;
		}

	for (int i = 0; i < wid * hei; i++)
	{
		if (strawfield[i])
		field[i] = 1;
	}*/
}

void filters::removePointlessWater(bool * land, int pointless) {
/*	int id[WID * HEI];
	QVector<QVector<Point>> lakes;
	QQueue<Point> q;
	Point p, next;
	int curr = 1;
	int idx;

	int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i < WID; ++i)
		for (int j = 0; j < HEI; ++j) {
			p = Point(i, j);
			idx = p.conv();
			if (land[idx] == false && id[idx] == 0) {
				id[idx] = curr++;
				QVector<Point> tmp;
				tmp.push_back(p);
				lakes.push_back(tmp);
				q.push_back(p);

				while (!q.empty()) {
					p = q.front();
					q.pop_front();

					for (int k = 0; k < 4; ++k) {
						next = Point(p.x + dir[k][0], p.y + dir[k][1]);
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
			for (Point p: lakes[i])
				land[p.conv()] = true;
			*/
}