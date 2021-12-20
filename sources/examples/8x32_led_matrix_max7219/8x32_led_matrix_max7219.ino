/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

#include <ledMatrixMax7219.h>

LedMatrixMax7219 matrix;

void setup() 
{
  matrix.init();
}

void loop() 
{
  matrix.setPixelRange(1, 1, B11111111);
  matrix.displayScreen();
}
