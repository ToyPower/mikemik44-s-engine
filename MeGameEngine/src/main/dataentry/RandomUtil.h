#pragma once
#include "Randoms.h"
namespace ME {

	class Rand {

	public:
		static float Float() {
			return rand.Float();
		}
		static float Float(float max) {
			return rand.Float(max);
		}
		static float Float(float min, float max) {
			return rand.Float(min, max);
		}
		static int Int(float max) {
			return rand.Int(max);
		}
		static int Int(float min, float max) {
			return rand.Int(min, max);
		}
	private:
		static Random rand;
	};

}
