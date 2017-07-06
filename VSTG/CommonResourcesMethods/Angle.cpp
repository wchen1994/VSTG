#include "Angle.h"

namespace CommResMeth {

	Angle::Angle() : Angle(0.f)
	{
	}

	Angle::Angle(float ang)
	{
		*this = ang;
	}

	const Angle & Angle::operator=(const float & rhs)
	{
		angle = rhs - int(rhs) / 180 * 180;
		return *this;
	}

	const Angle & Angle::operator=(const Angle & rhs)
	{
		angle = rhs.angle;
		return *this;
	}

	Angle Angle::operator+(const Angle & rhs)
	{
		return Angle(angle + rhs.angle);
	}

	const Angle & Angle::operator+=(const Angle & rhs)
	{
		return *this = *this + rhs;
	}

	Angle Angle::operator-(const Angle & rhs)
	{
		return Angle(angle - rhs.angle);
	}

	const Angle & Angle::operator-=(const Angle & rhs)
	{
		return *this = *this - rhs;
	}

	Angle Angle::operator-() const
	{
		return Angle(-angle);
	}

}