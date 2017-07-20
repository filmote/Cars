void scrollBuffer(byte scrollIncrement) { 

    int f = arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement;
Serial.print("WIDTH: ");
Serial.println(WIDTH);
Serial.print("  arduboy.sBuffer: ");
Serial.println((int)arduboy.sBuffer);
//Serial.print("  arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement ");
//Serial.println(f);
//Serial.print("  WIDTH - scrollIncrement ");
//Serial.println(WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_0_START, arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_1_START, arduboy.sBuffer + BUFFER_ROW_1_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_2_START, arduboy.sBuffer + BUFFER_ROW_2_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_3_START, arduboy.sBuffer + BUFFER_ROW_3_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_4_START, arduboy.sBuffer + BUFFER_ROW_4_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_5_START, arduboy.sBuffer + BUFFER_ROW_5_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_6_START, arduboy.sBuffer + BUFFER_ROW_6_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_7_START, arduboy.sBuffer + BUFFER_ROW_7_START + scrollIncrement, WIDTH - scrollIncrement);

f= arduboy.sBuffer + WIDTH - scrollIncrement;
Serial.print("  arduboy.sBuffer + WIDTH - scrollIncrement ");
Serial.println(f);
Serial.print("  BUFFER_ROW_0_END - scrollIncrement ");
Serial.println(BUFFER_ROW_0_END - scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_0_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_1_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_2_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_3_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_4_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_5_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_6_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_7_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  
  f= arduboy.sBuffer + BUFFER_ROW_0_END - scrollIncrement;
  arduboy.sBuffer[f] = 1;
  arduboy.sBuffer[f + 1] = 128;
/*
  arduboy.sBuffer[BUFFER_ROW_0_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_1_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_2_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_3_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_4_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_5_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_6_END] = 0;
  arduboy.sBuffer[BUFFER_ROW_7_END] = 0;
*/


  // Scroll the upper and lower limit arrays also ..
  
  memmove (upperLimit, upperLimit + scrollIncrement, WIDTH - scrollIncrement);
  memmove (lowerLimit, lowerLimit + scrollIncrement, WIDTH - scrollIncrement);
  
  memset (upperLimit + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (lowerLimit + WIDTH - scrollIncrement, 0, scrollIncrement);

}
