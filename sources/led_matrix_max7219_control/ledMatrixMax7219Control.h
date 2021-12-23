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
	 * @brief The enum Brightness
	 *
	 * @details This enum is the screen brightness intensity
	 */
	enum Brightness
	{
		Brightness_MinIntensity,
		Brightness_Intensity1,
		Brightness_Intensity2,
		Brightness_Intensity3,
		Brightness_Intensity4,
		Brightness_Intensity5,
		Brightness_Intensity6,
		Brightness_Intensity7,
		Brightness_Intensity8,
		Brightness_Intensity9,
		Brightness_Intensity10,
		Brightness_Intensity11,
		Brightness_Intensity12,
		Brightness_Intensity13,
		Brightness_Intensity14,
		Brightness_MaxIntensity
	};

	/**
	 * @brief The enum ModuleId
	 *
	 * @details This enum is the module identificator of the LED matrix MAX7219 component
	 */
	enum ModuleId
	{
		ModuleId_1,
		ModuleId_2,
		ModuleId_3,
		ModuleId_4
	};

	/**
	 * @brief The function init
	 *
	 * @details This function initialize the LED matrix MAX7219 component
	 */
	void init();

	/**
	 * @brief The function setIntensityOfModules
	 * @details This function
	 *
	 * @param[in] moduleId is identification of the LED matrix module
	 * @param[in] intensity of the matrix brightness
	 */
	void setIntensityOfModules(ModuleId moduleId, Brightness intensity);

	/**
	 * @brief The function setPixel
	 * @details This function set a pixel lighting in x and y dot of the matrix
	 *
	 * @param[in] x is a coordinate of the matrix horizontal axis
	 * @param[in] y is a coordinate of the matrix vertical axis
	 * @param[in] lighting of the pixel
	 */
	void setPixel(uint8_t x, uint8_t y, uint8_t lighting);

	/**
	 * @brief The function getPixel
	 * @details This function get a pixel lighting in x and y dot of the matrix
	 *
	 * @param[in] x is a coordinate of the matrix horizontal axis
	 * @param[in] y is a coordinate of the matrix vertical axis
	 * @return the pixel lighting
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
	 * @brief The function beginFrame
	 * @details This function begin the frame to write to the Max7219 component
	 */
	void beginFrame() const;

	/**
	 * @brief The function endFrame
	 * @details This function end the frame to write to the Max7219 component
	 */
	void endFrame() const;

	/**
	 * @brief The function writeDataToModule
	 * @details This function send data to the next register.
	 * Required to call beginFrame() before first used and endFrame() at the end of used.
	 *
	 * @param[in] registerId is register identification of the Max7219 component
	 * @param[in] data to send to the Max7219 component
	 */
	void writeDataToModule(uint8_t registerId, uint8_t data) const;

	/**
	 * @brief The function writeDataToRegister
	 * @details This function write data to a register
	 *
	 * @param[in] registerId is register identification of the Max7219 component
	 * @param[in] data to send to the Max7219 component
	 */
	void writeDataToRegister(uint8_t registerId, uint8_t data) const;

	/**
	 * @brief The function writeDataToMax7219
	 * @details This function write data to the Max7219 component
	 *
	 * @param[in] data to send to the Max7219 component
	 */
	void writeDataToMax7219(uint8_t data) const;

	/**
	 * @brief The function setPixelRange
	 * @details This function set a pixel lighting in x and y dot of the matrix
	 *
	 * @param[in] x is a coordinate of the matrix horizontal axis
	 * @param[in] y is a coordinate of the matrix vertical axis
	 * @param[in] lightingBitfield is the lighting of the pixel range
	 */
	void setPixelRange(uint8_t x, uint8_t y, uint8_t lightingBitfield);

	/**
	 * @brief The function emptyModules
	 * @details This function empty a module
	 */
	void emptyModules();

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
	enum ScanLimitHeight
	{
		ScanLimitHeight_1,
		ScanLimitHeight_2,
		ScanLimitHeight_3,
		ScanLimitHeight_4,
		ScanLimitHeight_5,
		ScanLimitHeight_6,
		ScanLimitHeight_7,
		ScanLimitHeight_8
	};

	/**
	 * @brief Shutdown mode values
	 */
	enum Shutdown
	{
		Shutdown_PowerDown,
		Shutdown_NormalMode
	};

	/**
	 * @brief Display mode values
	 */
	enum DisplayMode
	{
		DisplayMode_Normal,
		DisplayMode_Test
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
	 * @brief Empty pixel value
	 */
	enum { EmptyPixel   = 0x00 };

	/**
	 * @brief Pins definition
	 */
	static uint8_t const clockPin      = 10;
	static uint8_t const chipSelectPin = 11;
	static uint8_t const dataInPin     = 12;

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
		RegisterId_Digit6,
		RegisterId_Digit7
	};
	uint8_t intensityOfModules[matrixWidth];
	uint8_t matrix[matrixHeight][matrixWidth];
};

#endif // LED_MATRIX_MAX7219_H_
