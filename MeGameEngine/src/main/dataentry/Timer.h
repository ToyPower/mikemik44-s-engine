#pragma once
#include "main/corefiles/specialincludes.h"
#include <time.h>
namespace ME {
	class TimerResult {
	public:
		const char* name;
		float timer;
		static std::vector<TimerResult> allResults;
		static void addTimerResult(TimerResult& tr) {
			allResults.push_back(tr);
		}
		static void clearTimerResult() {
			allResults.clear();
		}
	};
	
	class Timer {

	public:
		Timer(const char* name) : m_name(name), m_stopped(false) {
			m_startPoint = std::chrono::high_resolution_clock::now();
		}

		~Timer() {
			if (!m_stopped) {
				stop();
			}
		}

		TimerResult getTimePassed() {
			auto endPoint = std::chrono::high_resolution_clock::now();

			long last = std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch().count();
			long now = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

			float ans = (now - last) * 0.001f;
			TimerResult res = TimerResult();
			res.name = m_name;
			res.timer = ans;
			return res;
		}

		void restart() {
			m_startPoint = std::chrono::high_resolution_clock::now();
			m_stopped = false;
		}

		TimerResult stop(bool printToConsole = false) {
			if (m_stopped) {
				return TimerResult();
			}
			m_stopped = true;
			auto endPoint = std::chrono::high_resolution_clock::now();

			long last = std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch().count();
			long now = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

			float ans = (now - last) * 0.001f;

			if (printToConsole) {
				std::cout << m_name << "-Time Passed: " << ans << "ms" << std::endl;
			}
			TimerResult res = TimerResult();
			res.name = m_name;
			res.timer = ans;
			TimerResult::addTimerResult(res);
			return res;
		}

	private:
		const char* m_name;
		bool m_stopped;
		std::chrono::time_point<std::chrono::steady_clock> m_startPoint;
	};

}