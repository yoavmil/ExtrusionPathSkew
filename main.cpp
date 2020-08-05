
// usage example

#include "Polygons.h"

int main(void) {

	// create some star polygon

	Polygon star = {
		{0, -1000},
		{+500, -500},
		{+1000, -500},
		{+750, 0},
		{+1000, 500},
		{+500, 500},
		{0, 1000},
		{-500, 500},
		{-1000, 500},
		{-750, 0},
		{-1000, -500},
		{-500, -500},
	};
	
	Polygons::AddSamplePoints(star, 50);
	Polygons::Skew(star, 100, 500);

	return 0;
}