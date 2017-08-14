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

	constexpr InternalType getInternal(void) const;
	constexpr IntegerType getInteger(void) const;
	constexpr FractionType getFraction(void) const;

	constexpr explicit operator IntegerType(void) const;
	constexpr explicit operator float(void) const;
	constexpr explicit operator double(void) const;

	template< unsigned IntegerOut, unsigned FractionOut >
	constexpr explicit operator UFixedPoint<IntegerOut, FractionOut>(void) const;

	constexpr static UFixedPoint fromInternal(const InternalType & value);

	UFixedPoint & operator ++(void);
	UFixedPoint & operator --(void);
	UFixedPoint & operator +=(const UFixedPoint & other);
	UFixedPoint & operator -=(const UFixedPoint & other);
	UFixedPoint & operator *=(const UFixedPoint & other);
	UFixedPoint & operator /=(const UFixedPoint & other);
};

template< unsigned Integer, unsigned Fraction >
constexpr bool operator ==(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator !=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator +(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator -(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator *(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator /(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer * 2, Fraction * 2> Multiply(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right);
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
constexpr typename UFixedPoint<Integer, Fraction>::InternalType UFixedPoint<Integer, Fraction>::getInternal(void) const
{
	return this->value;
}

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixedPoint<Integer, Fraction>::IntegerType UFixedPoint<Integer, Fraction>::getInteger(void) const
{
	return static_cast<IntegerType>(this->value >> FractionSize);
}

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixedPoint<Integer, Fraction>::FractionType UFixedPoint<Integer, Fraction>::getFraction(void) const
{
	return static_cast<FractionType>(this->value & Details::IdentityMask<FractionSize>::Value);
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction>::operator IntegerType(void) const
{
	return this->getInteger();
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
constexpr UFixedPoint<Integer, Fraction>::operator UFixedPoint<IntegerOut, FractionOut>(void) const
{
	using OutputType = UFixedPoint<IntegerOut, FractionOut>;
	using InternalType = typename OutputType::InternalType;

	return
	(FractionOut > Fraction) ?
		OutputType::fromInternal(static_cast<InternalType>(this->value << ((FractionOut > Fraction) ? FractionOut - Fraction : 0))) :
	(FractionOut < Fraction) ?
		OutputType::fromInternal(static_cast<InternalType>(this->value >> ((FractionOut < Fraction) ? Fraction - FractionOut : 0))) :
		OutputType::fromInternal(this->value);
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> UFixedPoint<Integer, Fraction>::fromInternal(const typename UFixedPoint<Integer, Fraction>::InternalType & value)
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
constexpr bool operator ==(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.getInternal() == right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator !=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.getInternal() != right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.getInternal() < right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.getInternal() > right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.getInternal() <= right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >=(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return (left.getInternal() >= right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator +(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::fromInternal(static_cast<InternalType>(left.getInternal() + right.getInternal()));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator -(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::fromInternal(static_cast<InternalType>(left.getInternal() - right.getInternal()));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator *(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	return static_cast<UFixedPoint<Integer, Fraction>>(Multiply(left, right));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> operator /(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using InternalType = typename UFixedPoint<Integer, Fraction>::InternalType;
	return UFixedPoint<Integer, Fraction>::fromInternal(static_cast<InternalType>((left.getInternal() << Fraction) / right.getInternal()));
}

#define OPERATOR_LOGIC( type, op ) \
	template< unsigned Integer, unsigned Fraction > \
	constexpr bool operator op (const UFixedPoint<Integer, Fraction> & left, const type & right) \
	{ \
		return (left op UFixedPoint<Integer, Fraction>(right)); \
	} \
	\
	template< unsigned Integer, unsigned Fraction > \
	constexpr bool operator op (const type & left, const UFixedPoint<Integer, Fraction> & right) \
	{ \
		return (UFixedPoint<Integer, Fraction>(left) op right); \
	}

#define OPERATOR_ARITHMETIC( type, op ) \
	template< unsigned Integer, unsigned Fraction > \
	constexpr UFixedPoint<Integer, Fraction> operator op (const UFixedPoint<Integer, Fraction> & left, const type & right) \
	{ \
		return (left op UFixedPoint<Integer, Fraction>(right)); \
	} \
	\
	template< unsigned Integer, unsigned Fraction > \
	constexpr UFixedPoint<Integer, Fraction> operator op (const type & left, const UFixedPoint<Integer, Fraction> & right) \
	{ \
		return (UFixedPoint<Integer, Fraction>(left) op right); \
	}
	
#define OPERATORS( opType, op ) \
	OPERATOR_##opType( Details::IntegerLiteral, op ) \
	OPERATOR_##opType( Details::IntegerLiteralU, op ) \
	OPERATOR_##opType( Details::IntegerLiteralL, op ) \
	OPERATOR_##opType( Details::IntegerLiteralUL, op ) \
	OPERATOR_##opType( Details::IntegerLiteralLL, op ) \
	OPERATOR_##opType( Details::IntegerLiteralULL, op ) \
	OPERATOR_##opType( Details::DecimalLiteral, op ) \
	OPERATOR_##opType( Details::DecimalLiteralF, op ) \
	OPERATOR_##opType( Details::DecimalLiteralL, op )

OPERATORS( LOGIC, == )
OPERATORS( LOGIC, != )
OPERATORS( LOGIC, < )
OPERATORS( LOGIC, > )
OPERATORS( LOGIC, <= )
OPERATORS( LOGIC, >= )

OPERATORS( ARITHMETIC , + )
OPERATORS( ARITHMETIC, - )
OPERATORS( ARITHMETIC, * )
OPERATORS( ARITHMETIC, / )

#undef OPERATOR_LOGIC
#undef OPERATOR_ARITHMETIC
#undef OPERATORS

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer * 2, Fraction * 2> Multiply(const UFixedPoint<Integer, Fraction> & left, const UFixedPoint<Integer, Fraction> & right)
{
	using ResultType = UFixedPoint<Integer * 2, Fraction * 2>;
	using InternalType = typename ResultType::InternalType;
	return ResultType::fromInternal(static_cast<InternalType>(static_cast<InternalType>(left.getInternal()) * static_cast<InternalType>(right.getInternal())));
}
END_FIXED_POINTS