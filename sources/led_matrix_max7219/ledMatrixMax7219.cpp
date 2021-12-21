/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

#include "ledMatrixMax7219.h"

void LedMatrixMax7219::init()
{
  initPins();
  initMax7219Component();
  displayScreen();
}

void LedMatrixMax7219::initPins()
{
  pinMode(clockPin, OUTPUT);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(dataInPin, OUTPUT);
  delay(500);
}

void LedMatrixMax7219::sendBytesToMax7219(byte data)
{
  for (byte i = 0; i < 8; ++i)
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataInPin, data & 0x80);
    data = data << 1;
    digitalWrite(clockPin, HIGH);
   }
}

void LedMatrixMax7219::setIntensity(byte intensity_for_matrix_a, byte intensity_for_matrix_b, byte intensity_for_matrix_c, byte intensity_for_matrix_d)
{
  digitalWrite(chipSelectPin, LOW);
  writeToRegister(intensityRegister, intensity_for_matrix_a);
  writeToRegister(intensityRegister, intensity_for_matrix_b);
  writeToRegister(intensityRegister, intensity_for_matrix_c);
  writeToRegister(intensityRegister, intensity_for_matrix_d);
  digitalWrite(chipSelectPin, HIGH);
}

void LedMatrixMax7219::writeToRegister(byte registerNumber, byte data)
{
  digitalWrite(chipSelectPin, LOW);
  sendBytesToMax7219(registerNumber);
  sendBytesToMax7219(data);
  digitalWrite(chipSelectPin, HIGH);
}

void LedMatrixMax7219::initMax7219Component()
{
  writeToRegister(decodeModeRegister,  usingLedMatrix);
  writeToRegister(intensityRegister,   intensityOfBrightness);
  writeToRegister(scanLimitRegister,   scan8LEDs);
  writeToRegister(shutdownRegister,    normalMode);
  writeToRegister(displayTestRegister, displayMode);
  delay(500);
}

void LedMatrixMax7219::writeToNextSegment(byte digitRegister, byte data)
{
  sendBytesToMax7219(digitRegister);
  sendBytesToMax7219(data);
}

void LedMatrixMax7219::beginWriteLine()
{
  digitalWrite(chipSelectPin, LOW);
}

void LedMatrixMax7219::endWriteLine()
{
  digitalWrite(chipSelectPin, HIGH);
}

void LedMatrixMax7219::displayScreen() const
{
  for (byte y = 0; y < maxDigit; ++y)
  {
    beginWriteLine();
    for (byte x = 0; x < maxSegment; ++x)
      writeToNextSegment(digits[y], matrix[y][x]);
    endWriteLine();
  }
}

void LedMatrixMax7219::blankSegment(byte indexSegment)
{
  for (byte y = 0; y < getHeight(); ++y)
    for (byte x = 0; x < maxSegment; ++x)
      {
	setPixelRange(x, y, 0x00);
      }
}

void Ledmatrixmax7219::setPixelRange(byte x, byte y, byte colorBitfield)
{
  matrix[y][x] = colorBitfield;
}

void LedMatrixMax7219::setPixel(byte x, byte y, byte color)
{
  byte bloc = x >> 3;
  byte pixel = x - (bloc << 3);
  byte *target = &matrix[y][bloc];

  if (color)
    *target |= 128 >> pixel;
  else
    *target &= ~(128 >> pixel);
}

byte LedMatrixMax7219::getPixel(byte x, byte y) const
{
  byte bloc = x >> 3;
  byte pixel = x - (bloc << 3);
  const byte *target = &matrix[y][bloc];

  return ((*target >> pixel) & 1);
}
