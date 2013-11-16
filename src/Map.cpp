/*
 * Tomasz [Tommalla] Zakrzewski, 2013
 * All rights reserved
 */

#include "Map.hpp"
#include "Point.hpp"

Map::Map(const qint32 width, const qint32 height) : width(width), height(height) {
	heightMap = new Height[width * height];
	typeMap = new Type[width * height];

	for (qint32 i = 0; i < width; ++i)
		for (qint32 j = 0; j < height; ++j) {
			heightAt(i, j) = -1;
			typeAt(i, j) = Type::WATER;
		}
}

Map::Map(const Map& other) {
	copy(other);
}

Map::Map(Map&& other) {
	move(std::move(other));
}

Map::~Map() {
	delete[] heightMap;
	delete[] typeMap;
}

Map& Map::operator=(const Map& other) {
	copy(other);
	return *this;
}

Map& Map::operator=(Map&& other) {
	move(std::move(other));
	return *this;
}

void Map::copy(const Map& other) {
	if (&other != this) {
		delete[] heightMap;
		delete[] typeMap;

		height = other.height;
		width = other.width;
		heightMap = new Height[width * height];
		typeMap = new Type[width * height];

		for (int i = 0; i < width * height; ++i) {
			heightMap[i] = other.heightMap[i];
			typeMap[i] = other.typeMap[i];
		}
	}
}

void Map::move(Map&& other) {
	width = other.width;
	height = other.height;
	heightMap = other.heightMap;
	typeMap = other.typeMap;
	other.heightMap = nullptr;
	other.typeMap = nullptr;
}

Height& Map::heightAt(const qint32 x, const qint32 y) const {
	return heightMap[points::convert(x, y, width)];
}

Type& Map::typeAt(const qint32 x, const qint32 y) const {
	return typeMap[points::convert(x, y, width)];
}

qint32 Map::getWidth() const {
	return width;
}

qint32 Map::getHeight() const {
	return height;
}

bool Map::isPointValid(const qint32 x, const qint32 y) const {
	return x >= 0 && x < width && y >= 0 && y < height;
}
