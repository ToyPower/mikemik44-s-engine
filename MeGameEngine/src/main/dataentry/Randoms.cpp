#include <hzpch.h>
#include "randoms.h"

namespace ME {

	Random::Random(long seed) {
		setSeed(seed);
	}

	void Random::setSeed(long seed) {

		x = (seed * 171) % 30269;
		y = (seed * 172) % 30307;
		z = (seed * 170) % 30323;

	}

	float Random::Float() {

		x = (171 * x) % 30269;
		y = (172 * y) % 30307;
		z = (170 * z) % 30323;

		float res = (x / 30269.0f, y / 30307.0f, z / 30323.0f);
		res = res - floor(res);
		return res;
	}

	float Random::Float(float max) {
		return Float() * max;
	}
	float Random::Float(float min, float max) {
		return Float() * (max - min) + min;
	}

	int Random::Int(int max) {
		return (int)Float(max);
	}
	int Random::Int(int min, int max) {
		return (int)Float(min, max);
	}

}