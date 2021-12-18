/*
 * Lisa Monpierre
 * EFRITS SAS
 *
 * MAX7219 Library
 * Dec. 2021
 */

#include "MAX7219MatrixLEDs8x32.h"

void MAX7219MatrixLEDs8x32::init()
{
  initPins();
  initMax7219Component();
  displayScreen();
}

void MAX7219MatrixLEDs8x32::initPins()
{
  pinMode(clockPin, OUTPUT);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(dataInPin, OUTPUT);
  delay(500);
}

void MAX7219MatrixLEDs8x32::initMax7219Component()
{
  writeToRegister(decodeModeRegister,  usingLedMatrix);
  writeToRegister(intensityRegister,   intensityOfBrightness);
  writeToRegister(scanLimitRegister,   scan8LEDs);
  writeToRegister(shutdownRegister,    normalMode);
  writeToRegister(displayTestRegister, displayMode);
  delay(500);
}

void MAX7219MatrixLEDs8x32::intensity(byte a, byte b, byte c, byte d)
{
  digitalWrite(chipSelectPin, LOW);
  writeToRegister(intensityRegister, a);
  writeToRegister(intensityRegister, b);
  writeToRegister(intensityRegister, c);
  writeToRegister(intensityRegister, d);
  digitalWrite(chipSelectPin, HIGH);
}

void MAX7219MatrixLEDs8x32::sendBytesToMax7219(byte data)
{
  for (byte i = 0; i < 8; ++i)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataInPin, data & 0x80);
    data = data << 1;
    digitalWrite(clockPin, HIGH);
   }
}

void MAX7219MatrixLEDs8x32::writeToRegister(byte registerNumber, byte data)
{
  digitalWrite(chipSelectPin, LOW);
  sendBytesToMax7219(registerNumber);
  sendBytesToMax7219(data);
  digitalWrite(chipSelectPin, HIGH);
}


void MAX7219MatrixLEDs8x32::writeToNextSegment(byte digitRegister, byte data)
{
  sendBytesToMax7219(digitRegister);
  sendBytesToMax7219(data);
}

void MAX7219MatrixLEDs8x32::beginWriteLine()
{
  digitalWrite(chipSelectPin, LOW);
}

void MAX7219MatrixLEDs8x32::endWriteLine()
{
  digitalWrite(chipSelectPin, HIGH);
}

void MAX7219MatrixLEDs8x32::displayScreen()
{
  for (byte y = 0; y < maxDigit; ++y)
  {
    beginWriteLine();
    for (byte x = 0; x < maxSegment; ++x)
      writeToNextSegment(digits[y], matrix[y][x]);
    endWriteLine();
  }
}

void MAX7219MatrixLEDs8x32::blankSegment(byte indexSegment)
{
  for (byte y = 0; y < getHeight(); ++y)
    for (byte x = 0; x < maxSegment; ++x)
  {
    setPixelRange(x, y, 0x00);
  }
}

void MAX7219MatrixLEDs8x32::setPixelRange(byte x, byte y, byte colorBitfield)
{
  matrix[y][x] = colorBitfield;
}

void MAX7219MatrixLEDs8x32::setPixel(byte x, byte y, byte color)
{
  byte bloc = x >> 3;
  byte pixel = x - (bloc << 3);
  byte *target = &matrix[y][bloc];

  if (color)
    *target |= 128 >> pixel;
  else
    *target &= ~(128 >> pixel);
}

byte MAX7219MatrixLEDs8x32::getPixel(byte x, byte y) const
{
  byte bloc = x >> 3;
  byte pixel = x - (bloc << 3);
  const byte *target = &matrix[y][bloc];

  return ((*target >> pixel) & 1);
}

byte MAX7219MatrixLEDs8x32::getWidth(void) const
{
  return (maxSegment * 8);
}

byte MAX7219MatrixLEDs8x32::getHeight(void) const
{
  return (maxDigit);
}
