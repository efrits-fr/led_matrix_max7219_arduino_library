/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

#ifndef MAX7219_MATRIX_LEDS_8X32_H
#define MAX7219_MATRIX_LEDS_8X32_H

#include <Arduino.h>

class MAX7219MatrixLEDs8x32
{
public:
  ~MAX7219MatrixLEDs8x32() = default;

  void init();

  void putPixel(byte indexDigit, byte indexSegment, byte pixel);
  void displayScreen();

private:
  void initMax7219Component();
  void initPins();

  void sendBytesToMax7219(byte data);
  void writeToRegister(byte registerNumber, byte data);
  void writeToNextSegment(byte digitRegister, byte data);
  
  void beginWriteLine();
  void endWriteLine();
  
  void blankSegment(byte indexSegment);

  static byte const clockPin      = 13;
  static byte const dataInPin     = 11;
  static byte const chipSelectPin = 10;
    
  static byte const noOpRegister        = 0x00;
  static byte const digit0Register      = 0x01;
  static byte const digit1Register      = 0x02;
  static byte const digit2Register      = 0x03;
  static byte const digit3Register      = 0x04;
  static byte const digit4Register      = 0x05;
  static byte const digit5Register      = 0x06;
  static byte const digit6Register      = 0x07;
  static byte const digit7Register      = 0x08;
  static byte const decodeModeRegister  = 0x09;
  static byte const intensityRegister   = 0x0A;
  static byte const scanLimitRegister   = 0x0B;
  static byte const shutdownRegister    = 0x0C;
  static byte const displayTestRegister = 0x0F; 
  
  static byte const usingLedMatrix        = 0x00; // Not digits model
  static byte const intensityOfBrightness = 0x01; // Range 0x00 - 0x01
  static byte const scan8LEDs             = 0x07;
  static byte const normalMode            = 0x01; // For shutdown/power-down mode set 0
  static byte const displayMode           = 0x00; // For test display mode set 1
  
  static byte const maxDigit   = 8;
  static byte const maxSegment = 4;
  
  byte const digits[8] =
  { 
    digit0Register,
    digit1Register,
    digit2Register,
    digit3Register,
    digit4Register,
    digit5Register,
    digit6Register,
    digit7Register
  };

  byte matrix[8][4] =
  {
    {0X00, 0X00, 0X00, 0X00 },
    {0X00, 0X00, 0X00, 0X00 },
    {0X00, 0X00, 0X00, 0X00 },
    {0X00, 0X00, 0X00, 0X00 },
    {0X00, 0X00, 0X00, 0X00 },
    {0X00, 0X00, 0X00, 0X00 },
    {0X00, 0X00, 0X00, 0X00 },
    {0X00, 0X00, 0X00, 0X00 }
  };
};

#endif // MAX7219_MATRIX_LEDS_8X32_H
