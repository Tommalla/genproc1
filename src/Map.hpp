/*
 * Tomasz [Tommalla] Zakrzewski, 2013
 * All rights reserved
 */

#ifndef MAP_H
#define MAP_H
#include <qtypetraits.h>

typedef qint8 Height;

enum class Type {
	WATER,
	LAND
};

class Map {
	public:
		Map(const qint32 width, const qint32 height);
		Map(const Map& other);
		Map(Map&& other);
		~Map();
		Map& operator=(const Map& other);
		Map& operator=(Map&& other);

		Height& heightAt(const qint32 x, const qint32 y) const;
		Type& typeAt(const qint32 x, const qint32 y) const;
		qint32 getWidth() const;
		qint32 getHeight() const;
		bool isPointValid(const qint32 x, const qint32 y) const;
	private:
		qint32 width, height;
		Height* heightMap;
		Type* typeMap;

		void copy(const Map& other);
		void move(Map&& other);
};

#endif // MAP_H
