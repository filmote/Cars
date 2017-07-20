void scrollBuffer(byte scrollIncrement) { 

  memmove (arduboy.sBuffer + BUFFER_ROW_0_START, arduboy.sBuffer + BUFFER_ROW_0_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_1_START, arduboy.sBuffer + BUFFER_ROW_1_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_2_START, arduboy.sBuffer + BUFFER_ROW_2_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_3_START, arduboy.sBuffer + BUFFER_ROW_3_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_4_START, arduboy.sBuffer + BUFFER_ROW_4_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_5_START, arduboy.sBuffer + BUFFER_ROW_5_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_6_START, arduboy.sBuffer + BUFFER_ROW_6_START + scrollIncrement, WIDTH - scrollIncrement);
  memmove (arduboy.sBuffer + BUFFER_ROW_7_START, arduboy.sBuffer + BUFFER_ROW_7_START + scrollIncrement, WIDTH - scrollIncrement);

  memset (arduboy.sBuffer + BUFFER_ROW_0_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_1_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_2_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_3_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_4_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_5_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_6_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (arduboy.sBuffer + BUFFER_ROW_7_START + WIDTH - scrollIncrement, 0, scrollIncrement);
  

  // Scroll the upper and lower limit arrays also ..
  
  memmove (upperLimit, upperLimit + scrollIncrement, WIDTH - scrollIncrement);
  memmove (lowerLimit, lowerLimit + scrollIncrement, WIDTH - scrollIncrement);
  
  memset (upperLimit + WIDTH - scrollIncrement, 0, scrollIncrement);
  memset (lowerLimit + WIDTH - scrollIncrement, 0, scrollIncrement);

}
