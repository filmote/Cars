#ifndef ENUMS_H
#define ENUMS_H

#include "FixedPoints.h"
#include "FixedPointsCommon.h"

enum class RoadType : uint8_t {
  Straight,
  Up,  
  Down,
  Count,
  First = Straight,
  Last = Down,
};

enum class SteeringType : uint8_t {
  FollowRoad,
  ZigZag,  
  Random,
  Count,
  First = FollowRoad,
  Last = Random,
};


enum class ObstacleType : uint8_t {
  RoughRoad,
  Crossing,  
  Fuel,
  Jewel,
  Count,
  Ramp,
  Crevice,
  First = RoughRoad,
  Last = Crossing,
};

struct PointSQ7x8 {
  SQ7x8 x;
  SQ7x8 y;
};

struct RoadElement {
  int16_t upperLimit;
  int16_t lowerLimit;
  RoadType roadType;
};

struct Road {
  int16_t x;
  int16_t y;
  int16_t height;
  RoadType type;
  uint8_t randomNumber;
  uint8_t randomCount;
};


enum class Direction : uint8_t {
  None = 0,
  Up = 1,  
  Down = 2,
  Left = 4,
  Right = 8,
};

constexpr Direction operator |(const Direction &left, const Direction &right) {
  return static_cast<Direction>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
}

constexpr Direction operator &(const Direction &left, const Direction &right) {
  return static_cast<Direction>(static_cast<uint8_t>(left) & static_cast<uint8_t>(right));
}

#endif
