#pragma once
#include <hzpch.h>
#include <time.h>
namespace ME {

	class Random {

	public:
		Random(long seed = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count());
		void setSeed(long seed = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count());

		float Float();
		float Float(float max);
		float Float(float min, float max);

		int Int(int max);
		int Int(int min, int max);

	private:
		long x, y, z;

	};

}
