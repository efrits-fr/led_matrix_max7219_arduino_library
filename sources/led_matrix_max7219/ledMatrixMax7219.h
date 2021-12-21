/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

#ifndef LED_MATRIX_MAX7219_H_
#define LED_MATRIX_MAX7219_H_

#include <Arduino.h>

class LedMatrixMax7219
{
public:
  void init();

  void setPixel(byte x, byte y, byte color);
  byte getPixel(byte x, byte y) const;
  void setIntensity(byte a, byte b, byte c, byte d) const;
  void setPixelRange(byte x, byte y, byte colorBitfield);

  void displayScreen() const;
  byte getWidth() const;
  byte getHeight() const;

private:
  void initMax7219Component();
  void initPins() const;

  void sendBytesToMax7219(byte data) const;
  void writeToRegister(byte registerNumber, byte data) const;
  void writeToNextSegment(byte digitRegister, byte data) const;

  void beginWriteLine() const;
  void endWriteLine() const;

  void blankSegment(byte indexSegment);

  static byte const clockPin      = 10;
  static byte const chipSelectPin = 11;
  static byte const dataInPin     = 12;

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

#endif // LED_MATRIX_MAX7219_H_
