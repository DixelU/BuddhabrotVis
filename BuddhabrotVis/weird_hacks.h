#pragma once
#include <stdint.h>

#define RANDFLOAT(range)  ((0 - range) + ((float)rand()/((float)RAND_MAX/(2*range))))

inline float Q_rsqrt(float number) {
	const float x2 = number * 0.5F;
	const float threehalfs = 1.5F;
	union {
		float f;
		uint32_t i;
	} conv = { number }; // member 'f' set to value of 'number'.
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= (threehalfs - (x2 * conv.f * conv.f));
	//conv.f *= (threehalfs - (x2 * conv.f * conv.f));
	return conv.f;
}

inline double Q_rsqrt(double number) {
	const double x2 = number * 0.5F;
	const double threehalfs = 1.5F;
	union {
		double f;
		uint64_t i;
	} conv = { number }; // member 'f' set to value of 'number'.
	conv.i = 0x5FE6EB50C7B537A9 - (conv.i >> 1);
	conv.f *= (threehalfs - (x2 * conv.f * conv.f));
	//conv.f *= (threehalfs - (x2 * conv.f * conv.f));
	return conv.f;
}
