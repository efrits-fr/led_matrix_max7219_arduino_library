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
  delay(50);
  initPins();
  
  delay(50);
  initMax7219Component();
}

void MAX7219MatrixLEDs8x32::initPins()
{
  pinMode(clockPin, OUTPUT);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(dataInPin, OUTPUT);
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

void MAX7219MatrixLEDs8x32::initMax7219Component()
{
  writeToRegister(decodeModeRegister,  usingLedMatrix);
  writeToRegister(intensityRegister,   intensityOfBrightness);
  writeToRegister(scanLimitRegister,   scan8LEDs);
  writeToRegister(shutdownRegister,    normalMode);
  writeToRegister(displayTestRegister, displayMode);
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
  for (byte indexDigit = 0; indexDigit < maxDigit; ++indexDigit)
  {
    beginWriteLine();
    for (byte indexSegment = 0; indexSegment < maxSegment; ++indexSegment)
    {
      writeToNextSegment(digits[indexDigit], matrix[indexDigit][indexSegment]);
    }
    endWriteLine();
  }
}

void MAX7219MatrixLEDs8x32::blankSegment(byte indexSegment)
{
  for (byte indexDigit = 0; indexDigit < maxDigit; ++indexDigit)
  {
    putPixel(indexDigit, indexSegment, 0x00);
  }
}

void MAX7219MatrixLEDs8x32::putPixel(byte indexDigit, byte indexSegment, byte pixel)
{
  matrix[indexDigit][indexSegment] = pixel;
}
