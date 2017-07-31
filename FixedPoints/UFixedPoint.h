#pragma once

#include <math.h>
#include <stdint.h>

#include "Details.h"

#include "UFixedPointBase.h"

//
// Declaration
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
class UFixedPoint : Details::UFixedPointBase< Integer, Fraction >
{
public:
	static_assert((Integer + Fraction) <= Details::BitSize<uintmax_t>::Value, "Platform does not have a type large enough.");

public:
	using IntegerType = Details::LeastUInt<Integer>;
	using FractionType = Details::LeastUInt<Fraction>;
	using InternalType = Details::LeastUInt<Integer + Fraction>;

	constexpr const static unsigned IntegerSize = Integer;
	constexpr const static unsigned FractionSize = Fraction;
	constexpr const static unsigned InternalSize = Details::BitSize<InternalType>::Value;

	constexpr const static unsigned long long Scale = 1ULL << FractionSize;

private:
	using Base = Details::UFixedPointBase<Integer, Fraction>;
	using RawType = typename Base::RawType;

public:
	using Base::Base;

	constexpr UFixedPoint(void);
	constexpr UFixedPoint(const IntegerType & integer);
	constexpr UFixedPoint(const IntegerType & integer, const FractionType & fraction);

	InternalType GetInternal(void) const;
	IntegerType GetInteger(void) const;
	FractionType GetFraction(void) const;

	constexpr explicit operator IntegerType(void) const;
	constexpr explicit operator float(void) const;
	constexpr explicit operator double(void) const;

	template< unsigned IntegerOut, unsigned FractionOut >
	explicit operator UFixedPoint<IntegerOut, FractionOut>(void) const;

	constexpr static UFixedPoint FromInternal(const InternalType & value);

	UFixedPoint & operator ++(void);
	UFixedPoint & operator --(void);
	UFixedPoint & operator +=(const UFixedPoint & other);
	UFixedPoint & operator -=(const UFixedPoint & other);
	UFixedPoint & operator *=(const UFixedPoint & other);
	UFixedPoint & operator /=(const UFixedPoint & other);
};

template< unsigned Integer, unsigned Fraction >
bool operator ==(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator ==(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator ==(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator !=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator !=(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator !=(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator <(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator >(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <=(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator <=(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >=(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator >=(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator +(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator +(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator +(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator -(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator -(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator -(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator *(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator *(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator *(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator /(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator /(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer * 2, Fraction * 2> Multiply(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);
END_FIXED_POINTS

//
// Definition
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction>::UFixedPoint(void)
	: Base()
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction>::UFixedPoint(const IntegerType & integer)
	: Base(RawType(static_cast<InternalType>(integer << FractionSize)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction>::UFixedPoint(const IntegerType & integer, const FractionType & fraction)
	: Base(RawType(static_cast<InternalType>((integer << FractionSize) | fraction)))
{
}

template< unsigned Integer, unsigned Fraction >
typename UFixedPoint<Integer, Fraction>::InternalType UFixedPoint<Integer, Fraction>::GetInternal(void) const
{
	return this->value;
}

template< unsigned Integer, unsigned Fraction >
typename UFixedPoint<Integer, Fraction>::IntegerType UFixedPoint<Integer, Fraction>::GetInteger(void) const
{
	return static_cast<IntegerType>(this->value >> FractionSize);
}

template< unsigned Integer, unsigned Fraction >
typename UFixedPoint<Integer, Fraction>::FractionType UFixedPoint<Integer, Fraction>::GetFraction(void) const
{
	return static_cast<FractionType>(this->value & Details::IdentityMask<FractionSize>::Value);
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction>::operator IntegerType(void) const
{
	return this->GetInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction>::operator float(void) const
{
	return (this->value * (1.0f / Scale));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction>::operator double(void) const
{
	return (this->value * (1.0 / Scale));
}

template< unsigned Integer, unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
UFixedPoint<Integer, Fraction>::operator UFixedPoint<IntegerOut, FractionOut>(void) const
{
	using Output = UFixedPoint<IntegerOut, FractionOut>;
	using InternalType = typename Output::InternalType;

	if (FractionOut > Fraction)
	{
		constexpr const auto Difference = (FractionOut > Fraction) ? FractionOut - Fraction : 0;
		return Output::FromInternal(static_cast<InternalType>(this->value << Difference));
	}
	else if (FractionOut < Fraction)
	{
		constexpr const auto Difference = (FractionOut < Fraction) ? Fraction - FractionOut : 0;
		return Output::FromInternal(static_cast<InternalType>(this->value >> Difference));
	}
	else
	{
		return Output::FromInternal(this->value);
	}
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> UFixedPoint<Integer, Fraction>::FromInternal(const typename UFixedPoint<Integer, Fraction>::InternalType & value)
{
	return UFixedPoint<Integer, Fraction>(RawType(value));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> & UFixedPoint<Integer, Fraction>::operator ++(void)
{
	this->value += (1 << FractionSize);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> & UFixedPoint<Integer, Fraction>::operator --(void)
{
	this->value -= (1 << FractionSize);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> & UFixedPoint<Integer, Fraction>::operator +=(const UFixedPoint<Integer, Fraction> & other)
{
	this->value += other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> & UFixedPoint<Integer, Fraction>::operator -=(const UFixedPoint<Integer, Fraction> & other)
{
	this->value -= other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> & UFixedPoint<Integer, Fraction>::operator *=(const UFixedPoint<Integer, Fraction> & other)
{
	this->value *= other.value;
	this->value >>= Fraction;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> & UFixedPoint<Integer, Fraction>::operator /=(const UFixedPoint<Integer, Fraction> & other)
{
	this->value <<= Fraction;
	this->value /= other.value;
	return *this;
}



template< unsigned Integer, unsigned Fraction >
bool operator ==(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() == right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator ==(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left == UFixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator ==(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (UFixedPoint<Integer, Fraction>(left) == right);
}

template< unsigned Integer, unsigned Fraction >
bool operator !=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() != right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator !=(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left != UFixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator !=(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (UFixedPoint<Integer, Fraction>(left) != right);
}

template< unsigned Integer, unsigned Fraction >
bool operator <(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() < right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator <(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left < UFixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator <(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (UFixedPoint<Integer, Fraction>(left) < right);
}

template< unsigned Integer, unsigned Fraction >
bool operator >(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() > right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator >(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left > UFixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator >(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (UFixedPoint<Integer, Fraction>(left) > right);
}

template< unsigned Integer, unsigned Fraction >
bool operator <=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() <= right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator <=(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left <= UFixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator <=(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (UFixedPoint<Integer, Fraction>(left) <= right);
}

template< unsigned Integer, unsigned Fraction >
bool operator >=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() >= right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator >=(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left >= UFixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator >=(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (UFixedPoint<Integer, Fraction>(left) >= right);
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator +(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() + right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator +(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() + (right << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator +(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>((left << Fraction) + right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator -(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() - right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator -(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() - (right << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator -(const typename UFixedPoint<Integer, Fraction>::IntegerType & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>((left << Fraction) - right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator *(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return static_cast<UFixedPoint<Integer, Fraction>>(Multiply(left, right));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator *(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return left * UFixedPoint<Integer, Fraction>(right);
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator *(const typename UFixedPoint<Integer, Fraction>::IntegerType& left, const  UFixedPoint<Integer, Fraction> & right)
{
	return UFixedPoint<Integer, Fraction>(left) * right;
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator /(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>((left.GetInternal() << Fraction) / right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer, Fraction> operator /(const UFixedPoint<Integer, Fraction> & left, const typename UFixedPoint<Integer, Fraction>::IntegerType & right)
{
	return left / (UFixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
UFixedPoint<Integer * 2, Fraction * 2> Multiply(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using ResultType = UFixedPoint<Integer * 2, Fraction * 2>;
	using InternalType = typename ResultType::InternalType;
	return ResultType::FromInternal(static_cast<InternalType>(static_cast<InternalType>(left.GetInternal()) * static_cast<InternalType>(right.GetInternal())));
}
END_FIXED_POINTS