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
	pinMode(loadPin, OUTPUT);
	pinMode(dataInPin, OUTPUT);
	delay(50);
}

void ledMatrixMax7219Control::initMax7219() const
{
	writeWordToChipset(RegisterId_DecodeMode, DecodeMode_LedMatrix);
	writeWordToChipset(RegisterId_Intensity, Intensity_0);
	writeWordToChipset(RegisterId_ScanLimit, ScanLimit_8);
	writeWordToChipset(RegisterId_Shutdown, Shutdown_NormalOperation);
	writeWordToChipset(RegisterId_DisplayTest, DisplayTest_NormalOperation);
}

void ledMatrixMax7219Control::writeWordToChipset(uint8_t registerId, uint8_t data) const
{
	beginLoadWord();
	for (uint8_t i = 0; i < matrixWidth; ++i)
	{
		loadWordToChipset(registerId, data);
	}
	endLoadWord();
}

void ledMatrixMax7219Control::loadWordToChipset(uint8_t registerId, uint8_t data) const
{
	writeDataToChipset(registerId);
	writeDataToChipset(data);
}

void ledMatrixMax7219Control::writeDataToChipset(uint8_t data) const
{
	for (uint8_t x = 0; x < DataLen; ++x)
	{
		digitalWrite(clockPin, LOW);
		digitalWrite(dataInPin, data & 0x80);
		data = data << 1;
		digitalWrite(clockPin, HIGH); // Data is loaded into the internal 16-bit shift register on CLK’s rising edge.
	}
}

void ledMatrixMax7219Control::beginLoadWord() const
{
	digitalWrite(loadPin, LOW);
}

void ledMatrixMax7219Control::endLoadWord() const
{
	digitalWrite(clockPin, LOW); // On CLK’s falling edge, data is clocked out of DOUT
	digitalWrite(loadPin, HIGH); // Load-Data Input. The last 16 bits of serial data are latched on LOAD’s rising edge
}

void ledMatrixMax7219Control::displayScreen() const
{
	beginLoadWord();
	for (uint8_t x = 0; x < matrixWidth; ++x)
	{
		loadWordToChipset(RegisterId_Intensity, brightnessOfLEDMatrix[x]);
	}
	endLoadWord();
	for (uint8_t y = 0; y < matrixHeight; ++y)
	{
		beginLoadWord();
		for (uint8_t x = 0; x < matrixWidth; ++x)
		{
			loadWordToChipset(registerOfDigits[y], matrix[y][x]);
		}
		endLoadWord();
	}
}

void ledMatrixMax7219Control::setPixelRange(uint8_t x, uint8_t y, uint8_t colorBitfield)
{
	x &= matrixWidth - 1;
	y &= matrixHeight - 1;
	matrix[y][x] = colorBitfield;
}

uint8_t ledMatrixMax7219Control::getPixelRange(uint8_t x, uint8_t y) const
{
	x &= matrixWidth - 1;
	y &= matrixHeight - 1;
	return (matrix[y][x]);
}

void ledMatrixMax7219Control::setPixel(uint8_t x, uint8_t y, uint8_t color)
{
	uint8_t const bloc = (x >> 3) & (matrixWidth - 1);
	uint8_t const pixel = x - (bloc << 3);
	uint8_t * target = &matrix[y & (matrixHeight - 1)][bloc];

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
	uint8_t const bloc = (x >> 3) & (matrixWidth - 1);
	uint8_t const pixel = x - (bloc << 3);
	uint8_t const * target = &matrix[y & (matrixHeight - 1)][bloc];

	return ((*target >> pixel) & 1);
}
