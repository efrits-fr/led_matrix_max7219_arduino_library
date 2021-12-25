/**
 * @author		Lisa Monpierre
 * @copyright	EFRITS SAS
 *
 * @brief		MAX7219 Library
 * @date		December 2021
 */

#include "ledMatrixMax7219Control.h"
#include <Arduino.h>

ledMatrixMax7219Control::ledMatrixMax7219Control()
{
	clearScreen(0);
}

void ledMatrixMax7219Control::clearScreen(uint8_t color)
{
	for (uint8_t y = 0; y < matrixHeight; ++y)
	{
		for (uint8_t x = 0; x < matrixWidth; ++x)
		{
			setPixelRange(x, y, color ? 255 : 0);
		}
	}
}

void ledMatrixMax7219Control::init()
{
	initPins();
	initMax7219();
	displayScreen();
}

void ledMatrixMax7219Control::initPins() const
{
	pinMode(clockPin, OUTPUT);
	pinMode(chipSelectPin, OUTPUT);
	pinMode(dataInPin, OUTPUT);
	delay(50);
}

void ledMatrixMax7219Control::initMax7219() const
{
	writeDataToRegister(RegisterId_DecodeMode,  DecodeMode_LedMatrix);
	writeDataToRegister(RegisterId_Intensity,   Brightness_Intensity1);
	writeDataToRegister(RegisterId_ScanLimit,   ScanLimitHeight_8);
	writeDataToRegister(RegisterId_Shutdown,    Shutdown_NormalMode);
	writeDataToRegister(RegisterId_DisplayTest, DisplayMode_Normal);
}

void ledMatrixMax7219Control::setIntensityOfModules(ModuleId moduleId, Brightness intensity)
{
	intensityOfModules[moduleId] = intensity;
}

void ledMatrixMax7219Control::writeDataToRegister(uint8_t registerId, uint8_t data) const
{
	beginFrame();
	writeDataToMax7219(registerId);
	writeDataToMax7219(data);
	endFrame();
}

void ledMatrixMax7219Control::writeDataToModule(uint8_t registerId, uint8_t data) const
{
	writeDataToMax7219(registerId);
	writeDataToMax7219(data);
}

void ledMatrixMax7219Control::writeDataToMax7219(uint8_t data) const
{
	digitalWrite(chipSelectPin, LOW);
	for (uint8_t x = 0; x < matrixHeight; ++x)
	{
		digitalWrite(clockPin, LOW);
		digitalWrite(dataInPin, data & 0x80);
		data = data << 1;
		digitalWrite(clockPin, HIGH);
	}
}

void ledMatrixMax7219Control::beginFrame() const
{
	digitalWrite(chipSelectPin, LOW);
}

void ledMatrixMax7219Control::endFrame() const
{
	digitalWrite(chipSelectPin, HIGH);
}

void ledMatrixMax7219Control::displayScreen() const
{
	beginFrame();
	for (uint8_t x = 0; x < matrixWidth; ++x)
	{
		writeDataToModule(RegisterId_Intensity, intensityOfModules[x]);
	}
	endFrame();
	for (uint8_t y = 0; y < matrixHeight; ++y)
	{
		beginFrame();
		for (uint8_t x = 0; x < matrixWidth; ++x)
		{
			writeDataToModule(registerOfDigits[y], matrix[y][x]);
		}
		endFrame();
	}
}

void ledMatrixMax7219Control::setPixelRange(uint8_t x, uint8_t y, uint8_t colorBitfield)
{
	matrix[y][x] = colorBitfield;
}

void ledMatrixMax7219Control::setPixel(uint8_t x, uint8_t y, uint8_t color)
{
	uint8_t const bloc = x >> 3;
	uint8_t const pixel = x - (bloc << 3);
	uint8_t * target = &matrix[y][bloc];

	if (color)
	{
		*target |= 128 >> pixel;
	}
	else
	{
		*target &= ~(128 >> pixel);
	}
}

uint8_t ledMatrixMax7219Control::getPixel(uint8_t x, uint8_t y) const
{
  uint8_t const bloc = x >> 3;
  uint8_t const pixel = x - (bloc << 3);
  uint8_t const * target = &matrix[y][bloc];

  return ((*target >> pixel) & 1);
}