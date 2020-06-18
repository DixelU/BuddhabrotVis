#pragma once
#include <vector>
#include <utility>
#include <random>
#include "multidimentional_point.h"

namespace fv_utils {
	std::default_random_engine gen;
	std::uniform_real_distribution<double> distr(0., 1.);
	inline double rdrand() {
		return distr(gen);
	}
}

typedef std::vector<double> line;
typedef std::vector<Point<2>> dline;

typedef std::vector<line> field;
typedef std::vector<dline> dfield;

using fv_utils::rdrand;

std::pair<field*, dfield*> GetStillRandomSignedField(size_t RasterCount) {
	constexpr size_t round_range = 2;
	field* f = new field;
	field localbuffer;
	line q;
	q.assign(RasterCount, 0);
	f->assign(RasterCount, q);
	localbuffer = *f;
	dfield* df = new dfield;
	dline dq;
	dq.assign(RasterCount, { 0,0 });
	df->assign(RasterCount, dq);
	for (size_t y = 0; y < RasterCount; y++) {
		for (size_t x = 0; x < RasterCount; x++) {
			(*f)[y][x] = (rdrand() - 0.5);
		}
	}

	for (size_t y = 0; y < RasterCount; y++) {
		for (size_t x = 0; x < RasterCount; x++) {
			double avg = 0;
			size_t counter = 0;
			for (int64_t ox = -round_range; ox <= round_range; ox++) {
				for (int64_t oy = -round_range; oy <= round_range; oy++) {
					if (y + oy<0 || y + oy>f->size() || x + ox<0 || x + ox>f->front().size())
						continue;
					avg += (*f)[y + oy][x + ox];
					counter++;
				}
			}
			localbuffer[y][x] = avg/counter;
		}
	}
	f->swap(localbuffer);
	return { f,df };
}

struct F_Vis {
	field FieldVal;
	field FieldValBuffer;
	dfield FieldSpeed;
	dfield FieldSpeedBuffer;
	F_Vis(size_t Raster_Count, std::pair<field*, dfield*>(*StartConditionsConstructor)(size_t) = GetStillRandomSignedField) {
		auto pr = StartConditionsConstructor(Raster_Count);
		FieldVal = *(pr.first);
		FieldSpeed = *(pr.second);
	}
	void Draw() const {

	}

};