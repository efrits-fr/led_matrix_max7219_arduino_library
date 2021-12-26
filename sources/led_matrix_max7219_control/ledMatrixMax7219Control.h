/**
 * @author		Lisa Monpierre
 * @copyright	EFRITS SAS
 *
 * @brief		MAX7219 Library
 * @date		December 2021
 */

#ifndef LED_MATRIX_MAX7219_H_
#define LED_MATRIX_MAX7219_H_

#include <stdint.h>

/**
 * @brief ledMatrixMax7219Control class
 *
 * @details This class manage the LED matrix MAX7219 component
 */
class ledMatrixMax7219Control
{
public:
	/**
	 * @brief The enum Intensity
	 *
	 * @details This enum is the screen intensity of the LED
	 */
	enum Intensity
	{
		Intensity_0,
		Intensity_1,
		Intensity_2,
		Intensity_3,
		Intensity_4,
		Intensity_5,
		Intensity_6,
		Intensity_7,
		Intensity_8,
		Intensity_9,
		Intensity_10,
		Intensity_11,
		Intensity_12,
		Intensity_13,
		Intensity_14,
		Intensity_15
	};

	/**
	 * @brief The enum ChipsetId
	 *
	 * @details This enum is the chipset identificator of the LED matrix MAX7219 component
	 */
	enum ChipsetId
	{
		ChipsetId_1,
		ChipsetId_2,
		ChipsetId_3,
		ChipsetId_4
	};

	/**
	 * @brief The function ledMatrixMax7219Control
	 *
	 * @details This function construct the ledMatrixMax7219Control object
	 */
	ledMatrixMax7219Control();

	/**
	 * @brief The function init
	 *
	 * @details This function initialize the LED matrix MAX7219 component
	 */
	void init();

	/**
	 * @brief The function setIntensityOfChipset
	 * @details This function
	 *
	 * @param[in] chipsetId is identification of the LED matrix chipset
	 * @param[in] intensity of the LED
	 */
	inline void setIntensityOfChipset(ChipsetId chipsetId, Intensity intensity) { chipsetsIntensity[chipsetId] = intensity; }

	/**
	 * @brief The function setPixel
	 * @details This function set a pixel color in x and y dot of the matrix
	 *
	 * @param[in] x is a coordinate of the matrix horizontal axis
	 * @param[in] y is a coordinate of the matrix vertical axis
	 * @param[in] color of the pixel
	 */
	void setPixel(uint8_t x, uint8_t y, uint8_t color);

	/**
	 * @brief The function getPixel
	 * @details This function get a pixel color in x and y dot of the matrix
	 *
	 * @param[in] x is a coordinate of the matrix horizontal axis
	 * @param[in] y is a coordinate of the matrix vertical axis
	 * @return the pixel color
	 */
	uint8_t getPixel(uint8_t x, uint8_t y) const;

	/**
	 * @brief The function displayScreen
	 * @details This function display the matrix updates on screen
	 */
	void displayScreen() const;

	/**
	 * @brief The function getScreenWidth
	 * @details This function return the screen width
	 *
	 * @return the screen width
	 */
	inline uint8_t getScreenWidth() const { return (screenWidth); }

	/**
	 * @brief The function getScreenHeight
	 * @details This function return the screen height
	 *
	 * @return the screen height
	 */
	inline uint8_t getScreenHeight() const { return (screenHeight); }

	/**
	 * @brief The function clearScreen
	 * @details This function clear the screen with the color provided
	 *
	 * @param[in] color of the pixel
	 */
	void clearScreen(uint8_t color);

private:
	/**
	 * @brief The function initPins
	 * @details This function initialize pins to communicate with the Max7219 component
	 */
	void initPins() const;

	/**
	 * @brief The function initComponent
	 * @details This function initialize the Max7219 component
	 */
	void initMax7219() const;

	/**
	 * @brief The function beginLoadWord
	 * @details This function indicate to the Max7219 component the beginning of a serial data transmission
	 */
	void beginLoadWord() const;

	/**
	 * @brief The function endLoadWord
	 * @details This function indicate to the Max7219 component the ending of a serial data transmission
	 */
	void endLoadWord() const;

	/**
	 * @brief The function loadWordToChipset
	 * @details This function load a word (16-bit data) to the chipset
	 * Required to call beginLoadWord() before first used and endLoadWord() at the end of used.
	 *
	 * @param[in] registerId is register identification of the Max7219 component
	 * @param[in] data to send to the Max7219 component
	 */
	void loadWordToChipset(uint8_t registerId, uint8_t data) const;

	/**
	 * @brief The function writeWordToChipset
	 * @details This function write a word (16-bit data) to a chipset
	 *
	 * @param[in] registerId is register identification of the Max7219 component
	 * @param[in] data to send to the Max7219 component
	 */
	void writeWordToChipset(uint8_t registerId, uint8_t data) const;

	/**
	 * @brief The function writeDataToChipset
	 * @details This function write data to the Max7219 component
	 *
	 * @param[in] data to send to the Max7219 component
	 */
	void writeDataToChipset(uint8_t data) const;

	/**
	 * @brief The function setPixelRange
	 * @details This function set a pixel color in x and y dot of the matrix
	 *
	 * @param[in] x is a coordinate of the matrix horizontal axis
	 * @param[in] y is a coordinate of the matrix vertical axis
	 * @param[in] colorBitfield is the color of the pixel range
	 */
	void setPixelRange(uint8_t x, uint8_t y, uint8_t colorBitfield);

	/**
	 * @brief Register Identification
	 */
	enum RegisterId
	{
		RegisterId_NoOperation = 0x00,
		RegisterId_Digit0      = 0x01,
		RegisterId_Digit1      = 0x02,
		RegisterId_Digit2      = 0x03,
		RegisterId_Digit3      = 0x04,
		RegisterId_Digit4      = 0x05,
		RegisterId_Digit5      = 0x06,
		RegisterId_Digit6      = 0x07,
		RegisterId_Digit7      = 0x08,
		RegisterId_DecodeMode  = 0x09,
		RegisterId_Intensity   = 0x0A,
		RegisterId_ScanLimit   = 0x0B,
		RegisterId_Shutdown    = 0x0C,
		RegisterId_DisplayTest = 0x0F
	};

	/**
	 * @brief Sccan limit values
	 */
	enum ScanLimit
	{
		ScanLimit_1,
		ScanLimit_2,
		ScanLimit_3,
		ScanLimit_4,
		ScanLimit_5,
		ScanLimit_6,
		ScanLimit_7,
		ScanLimit_8
	};

	/**
	 * @brief Shutdown mode values
	 */
	enum Shutdown
	{
		Shutdown_ShutdownMode,
		Shutdown_NormalOperation
	};

	/**
	 * @brief Display mode values
	 */
	enum DisplayTest
	{
		DisplayTest_NormalOperation,
		DisplayTest_DisplayTestMode
	};

	/**
	 * @brief Decode mode values
	 */
	enum DecodeMode
	{
		DecodeMode_LedMatrix,
		DecodeMode_DigitSegments
	};

	/**
	 * @brief Length of a data to write
	 */
	enum { DataLen = 8 };

	/**
	 * @brief Pins definition
	 */
	static uint8_t const clockPin   = 10;
	static uint8_t const loadPin 	= 11;
	static uint8_t const dataInPin  = 12;

	/**
	 * @brief Matrix height, y
	 */
	static uint8_t const matrixHeight  = 8;

	/**
	 * @brief Matrix width, x
	 */
	static uint8_t const matrixWidth   = 4;

	/**
	 * @brief Screen Height, y
	 */
	static uint8_t const screenHeight  = matrixHeight;

	/**
	 * @brief Screen width, x
	 */
	static uint8_t const screenWidth   = matrixWidth * matrixHeight;


	uint8_t const registerOfDigits[matrixHeight] =
	{
		RegisterId_Digit0,
		RegisterId_Digit1,
		RegisterId_Digit2,
		RegisterId_Digit3,
		RegisterId_Digit4,
		RegisterId_Digit5,
		RegisterId_Digit6,
		RegisterId_Digit7
	};
	uint8_t chipsetsIntensity[matrixWidth];
	uint8_t matrix[matrixHeight][matrixWidth];
};

#endif // LED_MATRIX_MAX7219_H_
