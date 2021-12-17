/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

#include "MAX7219MatrixLEDs8x32.h"

MAX7219MatrixLEDs8x32 matrix;

void setup() 
{
  Serial.begin(9600);
  matrix.init();
}

void loop() 
{
  matrix.putPixel(1, 1, B11111111);
}
