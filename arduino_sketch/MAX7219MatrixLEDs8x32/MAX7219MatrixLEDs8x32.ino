/*
 * Lisa Monpierre
 * EFRITS SAS
 *
 * MAX7219 Library
 * Dec. 2021
 */

#include "MAX7219MatrixLEDs8x32.h"
#include "max7219_demo.h"

MAX7219MatrixLEDs8x32 matrix;

void setup()
{
  matrix.init();
}

void loop()
{
  demo();
}
