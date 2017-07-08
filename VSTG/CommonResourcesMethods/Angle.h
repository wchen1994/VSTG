#pragma once

#include "Defines.h"

namespace CommResMeth {

	class __VSTG_API Angle
	{
	public:
		Angle();
		Angle(float ang);

		const Angle& operator=(const float & rhs);
		const Angle& operator=(const Angle & rhs);
		Angle operator+(const Angle & rhs);
		const Angle& operator+=(const Angle & rhs);
		Angle operator-(const Angle & rhs);
		const Angle& operator-=(const Angle & rhs);
		Angle operator-() const;

		inline bool operator< (const Angle& rhs) { return this->angle < rhs.angle; }
		inline bool operator> (const Angle& rhs) { return rhs.angle < this->angle; }
		inline bool operator<=(const Angle& rhs) { return !(*this > rhs); }
		inline bool operator>=(const Angle& rhs) { return !(*this < rhs); }

		inline bool operator==(const Angle& rhs) { return this->angle == rhs.angle; }
		inline bool operator!=(const Angle& rhs) { return !(*this == rhs); }

		inline operator float() const { return angle; }
		inline float rad() const { return angle * 3.141592654f / 180; }

	private:
		float angle;
	};

}