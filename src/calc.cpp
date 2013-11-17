#include <QQueue>
#include <QVector>
#include <cassert>
#include "Point.hpp"
#include "calc.hpp"

void generators::cellular(Map& map, const qint32 startingPoints, const qint32 expProb) {
	QQueue<Point> kolej;
	Point a, b;

	for (qint32 i = 0; i < map.getWidth(); ++i)
		for (qint32 j = 0; j < map.getHeight(); ++j)
			map.heightAt(i, j) = -1;

	for (int i = 0; i < startingPoints; i++) {
		a.randum(map.getWidth(), map.getHeight());
		kolej.push_back(a);
		map.heightAt(a.x, a.y) = 0;
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
					kolej.push_back(b);
				}
			}
	}

}

void generators::perlinsNoise(Map& map) {
	//TODO create an array of random gradients
	//TODO foreach point calculate the result
}

void fillers::standard(Map& map) {
	for (qint32 i = 0; i < map.getWidth(); ++i)
		for (qint32 j = 0; j < map.getHeight(); ++j) {
			Height h = map.heightAt(i, j);
			Type t;
			if (h <= -1)
				t = Type::WATER;
			else if (h >= 0)
				t = Type::LAND;

			map.typeAt(i, j) = t;
		}
}

void filters::smooth(Map& map, qint32 field, qint32 force) {
	Map tmp(map.getWidth(), map.getHeight());
	/*for (qint32 i = 0; i < tmp.getWidth(); ++i)
		for (qint32 j = 0; j < tmp.getHeight(); ++j) {
			tmp.heightAt(i, j) = -1;
			tmp.typeAt(i, j) = Type::WATER;
		}*/

	/*int acumulator = 0, noenoland = area * area - powah;
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
	//TODO (to jakieś nieogarnięte jest)
}

void filters::removePointlessWater(Map& map, const qint32 pointless) {
	qint32 id[map.getWidth() * map.getHeight()];

	for (qint32 i = 0; i < map.getWidth() * map.getHeight(); ++i)
		id[i] = 0;

	QVector<QVector<Point>> lakes;
	QQueue<Point> q;
	Point p, next;
	qint32 curr = 1;
	qint32 idx, idn;

	qint32 dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (qint32 i = 0; i < map.getWidth(); ++i)
		for (qint32 j = 0; j < map.getHeight(); ++j) {
			p = Point(i, j);
			idx = points::convert(i, j, map.getWidth());
			if (map.typeAt(i, j) == Type::WATER && id[idx] == 0) {
				id[idx] = curr++;
				QVector<Point> tmp;
				tmp.push_back(p);
				lakes.push_back(tmp);
				q.push_back(p);

				while (!q.empty()) {
					p = q.front();
					q.pop_front();

					for (qint8 k = 0; k < 4; ++k) {
						next = Point(p.x + dir[k][0], p.y + dir[k][1]);
						if (map.isPointValid(next.x, next.y)) {
							idn = points::convert(next.x, next.y, map.getWidth());

							if (map.typeAt(next.x, next.y) == Type::WATER && id[idn] == 0) {
								id[idn] = id[idx];
								lakes.back().push_back(next);
								q.push_back(next);
							}
						}
					}
				}
			}
		}

	for (qint32 i = 0; i < lakes.size(); ++i)
		if (lakes[i].size() <= pointless) {
			for (Point p: lakes[i]) {
				map.typeAt(p.x, p.y) = Type::LAND;
				map.heightAt(p.x, p.y) = 0;
			}
		}
}