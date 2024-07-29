#pragma once

namespace ME {

	class TimeStep {

	public:

		TimeStep(float time = 0.0f) : m_time(time) {}
		operator float() const { return m_time; }
		float getTime() const { return m_time; }
		float getMilla()  const { return m_time * 1000; }
		float getNano()  const { return m_time * 100000000; }
	private:
		float m_time;

	};
}
