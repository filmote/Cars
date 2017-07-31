#pragma once 
 
#include "../FixedPoints.h" 
 
BEGIN_FIXED_POINTS
using Q4x4 = UFixedPoint<4, 4>;
using Q8x8 = UFixedPoint<8, 8>;
using Q16x16 = UFixedPoint<16, 16>;
using Q32x32 = UFixedPoint<32, 32>;

using Q1x7 = UFixedPoint<1, 7>;
using Q1x15 = UFixedPoint<1, 15>;
using Q1x31 = UFixedPoint<1, 31>;
using Q1x63 = UFixedPoint<1, 63>;
END_FIXED_POINTS