#ifndef ENUMS_H
#define ENUMS_H

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
  Last = ZigZag,
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

struct Player {
  uint8_t x;
  uint8_t y;
  const uint8_t height;
  const uint8_t width;
};
#endif