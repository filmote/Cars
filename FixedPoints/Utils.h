#pragma once

#include "UFixedPoint.h"
#include "FixedPoint.h"

//
// Declaration
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> Floor(const UFixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> Floor(const FixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> Ceil(const UFixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> Ceil(const FixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> Round(const UFixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> Round(const FixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr bool Signbit(const FixedPoint<Integer, Fraction> & value);
END_FIXED_POINTS

//
// Definition
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> Floor(const UFixedPoint<Integer, Fraction> & value)
{
	using OutputType = UFixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::FromInternal(static_cast<InternalType>(value.GetInternal() & ~Details::IdentityMask<Fraction>::Value));
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> Floor(const FixedPoint<Integer, Fraction> & value)
{
	using OutputType = FixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::FromInternal(static_cast<InternalType>(value.GetInternal() & ~Details::IdentityMask<Fraction>::Value));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> Ceil(const UFixedPoint<Integer, Fraction> & value)
{
	using OutputType = UFixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::FromInternal(static_cast<InternalType>((value.GetInternal() & ~Details::IdentityMask<Fraction>::Value) + (1 << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> Ceil(const FixedPoint<Integer, Fraction> & value)
{
	using OutputType = FixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::FromInternal(static_cast<InternalType>((value.GetInternal() & ~Details::IdentityMask<Fraction>::Value) + (1 << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> Round(const UFixedPoint<Integer, Fraction> & value)
{
	return (value.GetInternal() & Details::MsbMask<Fraction>::Value) != 0 ? Ceil(value) : Floor(value);
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> Round(const FixedPoint<Integer, Fraction> & value)
{
	return
		(
			(value.GetInternal() & Details::MsbMask<Fraction>::Value) != 0 &&
			(Signbit(value) ? (value.GetInternal() & Details::IdentityMask<Fraction - 1>::Value) != 0 : true)
		)
		? Ceil(value)
		: Floor(value);
}

template< unsigned Integer, unsigned Fraction >
constexpr bool Signbit(const FixedPoint<Integer, Fraction> & value)
{
	return (value.GetInternal() & Details::MsbMask<FixedPoint<Integer, Fraction>::InternalSize>::Value) != 0;
}
END_FIXED_POINTS