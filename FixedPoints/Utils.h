#pragma once

#include "UFixedPoint.h"
#include "FixedPoint.h"

//
// Declaration
//

//
// These functions have a 'Fixed' suffix because
// Arduino defined 'floor', 'ceil', 'round' etc as macros,
// causing an irritating naming conflict.
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> floorFixed(const UFixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> floorFixed(const FixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> ceilFixed(const UFixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> ceilFixed(const FixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> roundFixed(const UFixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> roundFixed(const FixedPoint<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr bool signbitFixed(const FixedPoint<Integer, Fraction> & value);
END_FIXED_POINTS

//
// Definition
//

BEGIN_FIXED_POINTS
template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> floorFixed(const UFixedPoint<Integer, Fraction> & value)
{
	using OutputType = UFixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::fromInternal(static_cast<InternalType>(value.getInternal() & ~Details::IdentityMask<Fraction>::Value));
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> floorFixed(const FixedPoint<Integer, Fraction> & value)
{
	using OutputType = FixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::fromInternal(static_cast<InternalType>(value.getInternal() & ~Details::IdentityMask<Fraction>::Value));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> ceilFixed(const UFixedPoint<Integer, Fraction> & value)
{
	using OutputType = UFixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::fromInternal(static_cast<InternalType>((value.getInternal() & ~Details::IdentityMask<Fraction>::Value) + (1 << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> ceilFixed(const FixedPoint<Integer, Fraction> & value)
{
	using OutputType = FixedPoint<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::fromInternal(static_cast<InternalType>((value.getInternal() & ~Details::IdentityMask<Fraction>::Value) + (1 << Fraction)));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixedPoint<Integer, Fraction> roundFixed(const UFixedPoint<Integer, Fraction> & value)
{
	return (value.getInternal() & Details::MsbMask<Fraction>::Value) != 0 ? ceilFixed(value) : floorFixed(value);
}

template< unsigned Integer, unsigned Fraction >
constexpr FixedPoint<Integer, Fraction> roundFixed(const FixedPoint<Integer, Fraction> & value)
{
	return
		(
			(value.getInternal() & Details::MsbMask<Fraction>::Value) != 0 &&
			(signbitFixed(value) ? (value.getInternal() & Details::IdentityMask<Fraction - 1>::Value) != 0 : true)
		)
		? ceilFixed(value)
		: floorFixed(value);
}

template< unsigned Integer, unsigned Fraction >
constexpr bool signbitFixed(const FixedPoint<Integer, Fraction> & value)
{
	return (value.getInternal() & Details::MsbMask<FixedPoint<Integer, Fraction>::InternalSize>::Value) != 0;
}
END_FIXED_POINTS