#ifndef IMAGES_H
#define IMAGES_H

const byte PROGMEM digit_0[] = {
  4, 4,
  0x1C, 0x22, 0x22, 0x1C, 
};

const byte PROGMEM digit_1[] = {
  4, 4,
  0x00, 0x24, 0x3E, 0x20, 
};

const byte PROGMEM digit_2[] = {
  4, 4,
  0x24, 0x32, 0x2A, 0x24, 
};

const byte PROGMEM digit_3[] = {
  4, 4,
  0x14, 0x22, 0x2A, 0x14, 
};

const byte PROGMEM digit_4[] = {
  4, 4,
  0x0C, 0x0A, 0x3E, 0x08, 
};

const byte PROGMEM digit_5[] = {
  4, 4,
  0x2E, 0x2A, 0x2A, 0x12, 
};

const byte PROGMEM digit_6[] = {
  4, 4,
  0x1C, 0x2A, 0x2A, 0x10, 
};

const byte PROGMEM digit_7[] = {
  4, 4,
  0x02, 0x32, 0x0A, 0x06, 
};

const byte PROGMEM digit_8[] = {
  4, 4,
  0x14, 0x2A, 0x2A, 0x14, 
};

const byte PROGMEM digit_9[] = {
  4, 4,
  0x24, 0x2A, 0x12, 0x0C, 
};

const byte PROGMEM digit_mask[] = {
  0x1F, 0x1F, 0x1F, 0x1F, 
};

const byte* digits[] = {digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9};  


const unsigned char PROGMEM littleCar[] = {
// width, height,
9, 7,
0x3F,  0x7B, 0x76, 0x2E, 0x2E, 0x2E, 0x7B, 0x72, 0x3C,
};
const unsigned char PROGMEM littleCar_Mask[] = {
0x7F,  0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
};

const unsigned char PROGMEM Hannibal[] = {
// width, height,
67, 64,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x1f, 0x9f, 0x9f, 0x8f, 0x1f, 0x9f, 0x0f, 0x1f, 0x0f, 0x1f, 0x0f, 0x8f, 0x9f, 0x9f, 0x9f, 0x9f, 0x1f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xcf, 0x67, 0x13, 0x80, 0x18, 0xa0, 0xb8, 0x93, 0xd9, 0x98, 0xc8, 0xcd, 0xd1, 0xe8, 0xf2, 0xf3, 0xfc, 0xfe, 0xfe, 0xfb, 0xfb, 0xfb, 0xf9, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xf8, 0xc0, 0x07, 0x6f, 0x9f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0xa0, 0xf3, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x9f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7c, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x87, 0x9f, 0x3f, 0x3f, 0x1f, 0xff, 0xff, 0xff, 0x0f, 0x80, 0x8f, 0xc7, 0xf3, 0xb3, 0x9b, 0x93, 0xdb, 0xd9, 0xd9, 0xff, 0xe7, 0x0f, 0xff, 0xff, 0xff, 0xef, 0xef, 0xeb, 0xe9, 0xe9, 0xe9, 0xc9, 0xf1, 0xf7, 0x0c, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xe0, 0x83, 0x0c, 0x50, 0xd1, 0x03, 0x3b, 0x0f, 0x40, 0xa1, 0x3f, 0xbf, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xdb, 0x97, 0x93, 0x9f, 0xff, 0xdf, 0xcb, 0xff, 0xef, 0xff, 0x7f, 0xff, 0xfb, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7c, 0x10, 0x03, 0xfc, 0xc0, 0x03, 0x3c, 0x80, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xe7, 0xcb, 0xeb, 0xab, 0xab, 0xab, 0xab, 0xa3, 0xe3, 0xc3, 0xe3, 0xe3, 0xc1, 0xc3, 0xf1, 0x00, 0xf0, 0xf1, 0xf9, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xdf, 0xcf, 0x27, 0xf3, 0x03, 0xf9, 0xfc, 0xfe, 0xff, 0xf8, 0xe0, 0x8f, 0x3f, 0x78, 0xf1, 0xe3, 0x82, 0x07, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0xcf, 0x73, 0xf8, 0xf3, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xff, 0xe7, 0xef, 0xef, 0xdf, 0xbf, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf7, 0xf3, 0xfb, 0xf9, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf9, 0xe7, 0xcf, 0x9e, 0x7e, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0xd0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xff, 0x80, 0x0c, 0xf6, 0xf8, 0xfb, 0xff, 0xff, 0xff, 0x89, 0x1f, 0x39, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xf7, 0xf7, 0xec, 0x7d, 0x3b, 0xff, 
};




// Cars ------------------------------------------------------------------------------------------------------------------------

const byte PROGMEM car_player[] = {
  16, 14, 
  0xFF, 0xA1, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x41, 0x5D, 0xFE, 0x54, 0xF8, 0xF0,
  0x1F, 0x1E, 0x3C, 0x2C, 0x3D, 0x1D, 0x1D, 0x1B, 0x1B, 0x1B, 0x1A, 0x3A, 0x2A, 0x3B, 0x1F, 0x0F,
};

const byte PROGMEM car_01[] = {
  20, 12,
  0x7F, 0xD5, 0x3F, 0x02, 0x9E, 0xA2, 0xBF, 0x31, 0x91, 0x31, 0xB7, 0xB1, 0x2E, 0x9E, 0x82, 0x86, 0x02, 0x3E, 0x04, 0xFC,
  0x00, 0x03, 0x03, 0x02, 0x07, 0x06, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x06, 0x07, 0x02, 0x02, 0x02, 0x03,
};

const byte PROGMEM car_02[] = {
  17, 14,
  0xFE, 0x22, 0x02, 0x22, 0x82, 0x02, 0x02, 0xA2, 0x82, 0x22, 0xBF, 0xAD, 0x7E, 0xFC, 0x08, 0x18, 0xF0,
  0x1F, 0x10, 0x3C, 0x35, 0x3B, 0x11, 0x10, 0x11, 0x11, 0x10, 0x11, 0x3D, 0x35, 0x3C, 0x10, 0x1A, 0x0F,
};


const byte PROGMEM car_03[] = {
  16, 10,
  0xFC, 0x42, 0x9E, 0xAF, 0xB1, 0x01, 0x31, 0x31, 0x2F, 0x9E, 0x1A, 0x9A, 0x82, 0x9A, 0x02, 0xFC,
  0x01, 0x01, 0x03, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x02, 0x03, 0x01, 0x01,  
};

const byte PROGMEM car_04[] = {
  19, 12,
  0xF8, 0x44, 0x2A, 0x3A, 0x02, 0x2E, 0x31, 0xB7, 0x01, 0xB7, 0x31, 0x2E, 0x1E, 0x02, 0x1A, 0x1A, 0x02, 0x1A, 0xFC,
  0x01, 0x03, 0x02, 0x07, 0x05, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x05, 0x07, 0x02, 0x01,
};

const byte PROGMEM car_05[] = {
  18, 10,
  0xFC, 0x5A, 0x82, 0x82, 0x9E, 0x0F, 0x01, 0x71, 0x31, 0x31, 0x2F, 0x9E, 0x1A, 0x9A, 0x82, 0x9A, 0x02, 0xFC,
  0x01, 0x01, 0x03, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x02, 0x03, 0x01, 0x01,
};

const byte PROGMEM car_06[] = {
  19, 12,
  0xFC, 0x06, 0x3A, 0x02, 0x2E, 0x31, 0x11, 0xB1, 0xB1, 0xAE, 0x02, 0xBA, 0x2A, 0x3A, 0x2A, 0x2A, 0x2A, 0x06, 0xFC,
  0x01, 0x03, 0x02, 0x07, 0x05, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x05, 0x07, 0x02, 0x03, 0x03,
};

const byte PROGMEM car_07[] = {
  19, 15,
  0xF0, 0x50, 0xFC, 0x04, 0x34, 0x14, 0x34, 0x04, 0x04, 0x84, 0xC2, 0xE2, 0xE1, 0xA1, 0xA1, 0xE1, 0x5E, 0xB0, 0xE0,
  0x07, 0x05, 0x3F, 0x30, 0x7B, 0x68, 0x7B, 0x33, 0x30, 0x3E, 0x3E, 0x30, 0x33, 0x7B, 0x6A, 0x78, 0x31, 0x32, 0x1F,
};

const byte PROGMEM car_08[] = {
  18, 12,
  0xF8, 0x04, 0x74, 0x74, 0x74, 0x74, 0x74, 0x7F, 0x01, 0xC1, 0xC1, 0xBF, 0x7E, 0x04, 0x04, 0x04, 0x4C, 0xF8,
  0x07, 0x04, 0x0E, 0x0A, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x0A, 0x0E, 0x04, 0x06, 0x03,
};

const byte PROGMEM mask_player[] = {
  0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0,
  0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F,
};

const byte PROGMEM mask_01[] = {
  0x7F, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC,
  0x00, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03,
};

const byte PROGMEM mask_02[] = {
  0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF8, 0xF0,
  0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x0F,
};

const byte PROGMEM mask_03[] = {
  0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC,
  0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 0x01,
};

const byte PROGMEM mask_04[] = {
  0xF8, 0xFD, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFC,
  0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x01,
};

const byte PROGMEM mask_05[] = {
  0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC,
  0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 0x01,
};

const byte PROGMEM mask_06[] = {
  0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC,
  0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03,
};

const byte PROGMEM mask_07[] = {
  0xF0, 0xF0, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF0, 0xE0,
  0x07, 0x07, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F,
};

const byte PROGMEM mask_08[] = {
  0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8,
  0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x03,
};


// Road ------------------------------------------------------------------------------------------------------------------------

const byte PROGMEM upper_road[] = {
  8, 24,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x35, 0x32, 0x35, 0x32, 0x35, 0x32, 0x35, 0x32,
};

const byte PROGMEM upper_road_up[] = {
  8, 24,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x35, 0x32, 0x35, 0x32, 0x39, 0x1A, 0x19, 0x1A,
};

const byte PROGMEM upper_road_down[] = {
  8, 24,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x19, 0x1A, 0x19, 0x1A, 0x31, 0x32, 0x35, 0x32,
};

const byte PROGMEM lower_road[] = {
  8, 24,
  0x4C, 0xAC, 0x4C, 0xAC, 0x4C, 0xAC, 0x4C, 0xAC,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,  
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
};  

const byte PROGMEM lower_road_up[] = {
  8, 24,
  0x58, 0x98, 0x58, 0x98, 0x4C, 0xAC, 0x4C, 0xAC,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
};

const byte PROGMEM lower_road_down[] = {
  8, 24,
  0x4C, 0xAC, 0x4C, 0x8C, 0x58, 0x98, 0x58, 0x98,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
};


// Obstacles ------------------------------------------------------------------------------------------------------------------------

const byte PROGMEM roughPatch[] = {
  8, 8,
  0x0C, 0x42, 0x80, 0x18, 0xC3, 0x00, 0x14, 0x42,
};

const byte PROGMEM crossing[] = {
  6, 40,
  0x33,  0x33, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x33,  0x33, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x33,  0x33, 0x33, 0x33, 0x33, 0x33,
};


/*
const byte PROGMEM tree[] = {
  12, 14,
0x00,  0xB8, 0x44, 0x82, 0x02, 0x14, 0x08, 0x04, 0x44, 0x88, 0x70, 0x00,
0x00, 0x03, 0x04, 0x08, 0x08, 0x04, 0x0A, 0x10, 0x10, 0x08, 0x07, 0x00,
};

const byte PROGMEM mask_tree[] = {
0xB8,  0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFC, 0xFE, 0xFE, 0xFC, 0xFC, 0x70,
0x03, 0x0F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 0x1F, 0x1F, 0x07,
};
*/

const byte PROGMEM tree[] = {
  14, 16,
  0x00, 0x00, 0x70, 0x88, 0x04, 0x04, 0x28, 0x10, 0x08, 0x88, 0x10, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x08, 0x11, 0x10, 0x08, 0x14, 0x20, 0x20, 0x11, 0x0E, 0x00, 0x00,
};

const byte PROGMEM tree_mask[] = {
  0x70, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0,  
  0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0x7F, 0x3F, 0x7F, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x0E,
};

const byte PROGMEM fuel[] = {
  7, 10,
  0xFA, 0x07, 0x52, 0x21, 0x51, 0x01, 0xFE,
  0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01,
};

const byte PROGMEM fuel_mask[] = {
  0xFA, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE,
  0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
};

const byte PROGMEM jewel[] = {
  5, 7, 
  0x1C,  0x22, 0x5D, 0x22, 0x1C,
};

const byte PROGMEM jewel_mask[] = {
  0x1C, 0x3E, 0x7F, 0x3E, 0x1C,
};

const byte PROGMEM bush[] = {
  11, 12,

0x00,  0x00, 0x80, 0x58, 0x24, 0x04, 0x08, 0x44, 0xB8, 0x00, 0x00,
0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x01, 0x00, 0x00,
};

const byte PROGMEM bush_mask[] = {
0x80,  0xD8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0xFC, 0xB8,
0x01, 0x03, 0x07, 0x0F, 0x0F, 0x07, 0x0F, 0x0F, 0x07, 0x03, 0x01,
};

const byte PROGMEM crevice[] = {
  16, 56,
  0x55,  0xAA, 0x55, 0xFF, 0x00, 0xFF, 0xFF, 0xDB, 0x55, 0x92, 0x45, 0x00, 0xFF, 0xAA, 0x55, 0xAA,
  0x0D, 0x0C, 0x0D, 0xFF, 0x00, 0xFF, 0xFF, 0x36, 0x49, 0x24, 0x51, 0x00, 0xFF, 0x0C, 0x0D, 0x0C,
  0x00, 0x00, 0xFC, 0x03, 0xF8, 0xFF, 0xB7, 0xAB, 0x41, 0x09, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xF0, 0x0F, 0xE0, 0xFF, 0xFF, 0x6D, 0x2A, 0x02, 0xF8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x9F, 0x70, 0x07, 0xFF, 0x5F, 0x03, 0xF0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0xF8, 0x03, 0x85, 0x70, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x2E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM ramp[] = {
  20, 19,
  0x10,  0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x81, 0x81, 0x01, 0xFF,
  0x08, 0x08, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x81, 0x81, 0x80, 0x80, 0x40, 0x40, 0x40, 0x7F,
  0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x01, 0x05, 0x01, 0x05, 0x00, 0x06, 0x00, 0x06, 0x00, 0x07, 0x00, 0x07,
};

const byte PROGMEM fuel_gauge[] = {
  5, 8,
  0x7F,  0x41, 0x75, 0x7D, 0x7F,
  /*
  0x7D,  0x42, 0x59, 0x41, 0x7F,*/
/*  0x7D, 0x56, 0x6F, 0x57, 0x7F,*/
};
#endif
