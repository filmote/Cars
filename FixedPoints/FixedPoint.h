#pragma once

#include <math.h>
#include <stdint.h>

#include "Details.h"

#include "FixedPointBase.h"

//
// Declaration
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
class FixedPoint : Details::FixedPointBase< Integer, Fraction >
{
public:
	static_assert(((Integer + 1) + Fraction) <= Details::BitSize<uint_least64_t>::Value, "Platform does not have type capable of containing.");

public:
	using IntegerType = Details::LeastInt<Integer + 1>;
	using FractionType = Details::LeastUInt<Fraction>;
	using InternalType = Details::LeastInt<(Integer + 1) + Fraction>;

	constexpr const static unsigned IntegerSize = Integer + 1;
	constexpr const static unsigned FractionSize = Fraction;
	constexpr const static unsigned InternalSize = Details::BitSize<InternalType>::Value;

	constexpr const static unsigned long long Scale = 1ULL << FractionSize;
	
private:
	using Base = Details::FixedPointBase<Integer, Fraction>;
	using RawType = typename Base::RawType;

public:
	using Base::Base;

	constexpr FixedPoint(void);
	constexpr FixedPoint(const IntegerType & integer);
	constexpr FixedPoint(const IntegerType & integer, const FractionType & fraction);

	InternalType GetInternal(void) const;
	IntegerType GetInteger(void) const;
	FractionType GetFraction(void) const;

	constexpr explicit operator IntegerType(void) const;
	constexpr explicit operator float(void) const;
	constexpr explicit operator double(void) const;

	template< unsigned IntegerOut, unsigned FractionOut >
	explicit operator FixedPoint<IntegerOut, FractionOut>(void) const;

	constexpr static FixedPoint FromInternal(const InternalType & value);

	constexpr FixedPoint operator -(void) const;
	FixedPoint & operator ++(void);
	FixedPoint & operator --(void);
	FixedPoint & operator +=(const FixedPoint & other);
	FixedPoint & operator -=(const FixedPoint & other);
	FixedPoint & operator *=(const FixedPoint & other);
	FixedPoint & operator /=(const FixedPoint & other);
};

template< unsigned Integer, unsigned Fraction >
bool operator ==(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator ==(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator ==(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator !=(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator !=(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator !=(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator <(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator >(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <=(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator <=(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator <=(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >=(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
bool operator >=(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
bool operator >=(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator +(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator +(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator +(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator -(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator -(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator -(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator *(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator *(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator *(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator /(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator /(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right);

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer * 2, Fraction * 2> Multiply(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right);
END_FIXED_POINTS

//
// Definition
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction>::FixedPoint(void)
	: Base()
{
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction>::FixedPoint(const IntegerType & integer)
	: Base(RawType(static_cast<InternalType>(integer << FractionSize)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction>::FixedPoint(const IntegerType & integer, const FractionType & fraction)
	: Base(RawType(static_cast<InternalType>((integer << FractionSize) | fraction)))
{
}

template< unsigned Integer, unsigned Fraction >
typename FixedPoint<Integer, Fraction>::InternalType FixedPoint<Integer, Fraction>::GetInternal(void) const
{
	return this->value;
}

template< unsigned Integer, unsigned Fraction >
typename FixedPoint<Integer, Fraction>::IntegerType FixedPoint<Integer, Fraction>::GetInteger(void) const
{
	return static_cast<IntegerType>(this->value >> FractionSize);
}

template< unsigned Integer, unsigned Fraction >
typename FixedPoint<Integer, Fraction>::FractionType FixedPoint<Integer, Fraction>::GetFraction(void) const
{
	return static_cast<FractionType>(this->value & Details::IdentityMask<FractionSize>::Value);
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction>::operator IntegerType(void) const
{
	return this->GetInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction>::operator float(void) const
{
	return (this->value * (1.0f / Scale));
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction>::operator double(void) const
{
	return (this->value * (1.0 / Scale));
}

template< unsigned Integer, unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
FixedPoint<Integer, Fraction>::operator FixedPoint<IntegerOut, FractionOut>(void) const
{
	using Output = FixedPoint<IntegerOut, FractionOut>;
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
constexpr FixedPoint<Integer, Fraction> FixedPoint<Integer, Fraction>::FromInternal(const typename FixedPoint<Integer, Fraction>::InternalType & value)
{
	return FixedPoint<Integer, Fraction>(RawType(value));
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> FixedPoint<Integer, Fraction>::operator -(void) const
{
	return FixedPoint<Integer, Fraction>::FromInternal(-this->value);
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> & FixedPoint<Integer, Fraction>::operator ++(void)
{
	this->value += (1 << FractionSize);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> & FixedPoint<Integer, Fraction>::operator --(void)
{
	this->value -= (1 << FractionSize);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> & FixedPoint<Integer, Fraction>::operator +=(const FixedPoint<Integer, Fraction> & other)
{
	this->value += other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> & FixedPoint<Integer, Fraction>::operator -=(const FixedPoint<Integer, Fraction> & other)
{
	this->value -= other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> & FixedPoint<Integer, Fraction>::operator *=(const FixedPoint<Integer, Fraction> & other)
{
	this->value *= other.value;
	this->value >>= Fraction;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> & FixedPoint<Integer, Fraction>::operator /=(const FixedPoint<Integer, Fraction> & other)
{
	this->value <<= Fraction;
	this->value /= other.value;
	return *this;
}



template< unsigned Integer, unsigned Fraction >
bool operator ==(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() == right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator ==(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left == FixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator ==(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	return (FixedPoint<Integer, Fraction>(left) == right);
}

template< unsigned Integer, unsigned Fraction >
bool operator !=(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() != right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator !=(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left != FixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator !=(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	return (FixedPoint<Integer, Fraction>(left) != right);
}

template< unsigned Integer, unsigned Fraction >
bool operator <(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() < right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator <(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left < FixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator <(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	return (FixedPoint<Integer, Fraction>(left) < right);
}

template< unsigned Integer, unsigned Fraction >
bool operator >(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() > right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator >(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left > FixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator >(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	return (FixedPoint<Integer, Fraction>(left) > right);
}

template< unsigned Integer, unsigned Fraction >
bool operator <=(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() <= right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator <=(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left <= FixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator <=(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	return (FixedPoint<Integer, Fraction>(left) <= right);
}

template< unsigned Integer, unsigned Fraction >
bool operator >=(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	return (left.GetInternal() >= right.GetInternal());
}

template< unsigned Integer, unsigned Fraction >
bool operator >=(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return (left >= FixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
bool operator >=(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	return (FixedPoint<Integer, Fraction>(left) >= right);
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator +(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename FixedPoint<Integer, Fraction>::InternalType;
	return FixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() + right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator +(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	using InternalType = typename FixedPoint<Integer, Fraction>::InternalType;
	return FixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() + (right << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator +(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename FixedPoint<Integer, Fraction>::InternalType;
	return FixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>((left << Fraction) + right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator -(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename FixedPoint<Integer, Fraction>::InternalType;
	return FixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() - right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator -(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	using InternalType = typename FixedPoint<Integer, Fraction>::InternalType;
	return FixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>(left.GetInternal() - (right << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator -(const typename FixedPoint<Integer, Fraction>::IntegerType & left, const FixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename FixedPoint<Integer, Fraction>::InternalType;
	return FixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>((left << Fraction) - right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator *(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	return static_cast<FixedPoint<Integer, Fraction>>(Multiply(left, right));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator *(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return left * FixedPoint<Integer, Fraction>(right);
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator *(const typename FixedPoint<Integer, Fraction>::IntegerType& left, const  FixedPoint<Integer, Fraction> & right)
{
	return FixedPoint<Integer, Fraction>(left) * right;
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator /(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename FixedPoint<Integer, Fraction>::InternalType;
	return FixedPoint<Integer, Fraction>::FromInternal(static_cast<InternalType>((left.GetInternal() << Fraction) / right.GetInternal()));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer, Fraction> operator /(const FixedPoint<Integer, Fraction> & left, const typename FixedPoint<Integer, Fraction>::IntegerType & right)
{
	return left / (FixedPoint<Integer, Fraction>(right));
}

template< unsigned Integer, unsigned Fraction >
FixedPoint<Integer * 2, Fraction * 2> Multiply(const FixedPoint<Integer, Fraction> & left, const FixedPoint<Integer, Fraction> & right)
{	
	using ResultType = FixedPoint<Integer * 2, Fraction * 2>;
	using InternalType = typename ResultType::InternalType;
	return ResultType::FromInternal(static_cast<InternalType>(static_cast<InternalType>(left.GetInternal()) * static_cast<InternalType>(right.GetInternal())));
}
END_FIXED_POINTS