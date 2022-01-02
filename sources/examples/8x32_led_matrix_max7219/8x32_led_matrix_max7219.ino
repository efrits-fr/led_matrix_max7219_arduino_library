/*
 * Lisa Monpierre
 * EFRITS SAS
 *
 * MAX7219 Library
 * Dec. 2021
 */

#include <ledMatrixMax7219Control.h>

// The representation of the screen in memory
ledMatrixMax7219Control matrix;

// Variables used for the animation
float ballX;
float ballY;
float ballXSpeed;
float ballYSpeed;
// How many loops are required before doing a screen clear again
enum { CountMax = 500 };
int countLoop = CountMax;
bool stepLoop = false;

void resetBall()
{
  // Set the horizontal ball position somewhere between 0 and the width of the screen randomly
  ballX = random(matrix.getScreenWidth());
  // Set the vertical ball position somewhere between 0 and the height of the screen randomly
  ballY = random(matrix.getScreenHeight());
  // Set an horizontal and vertical speed between -1 and 1, but not inside -0.2 0.2 so the
  // ball does not follow perfectly horizontal or vertical lines
  while (fabs(ballXSpeed = random(-10, 10) / 10.0) < 0.2);
  while (fabs(ballYSpeed = random(-10, 10) / 10.0) < 0.2);
}

// This function is only called once at startup to set up the demo
void setup()
{
  // Initialization of the matrix, allow it to work correctly
  matrix.init();
  // Set a seed from an analog entry so the random generator generates differents values at each startup
  randomSeed(analogRead(0));
}

void moveBall()
{
  // We add the horizontal speed to the ball. If the ball goes outside the screen,
  // then we flip the speed and then add the speed to the position again
  if ((ballX += ballXSpeed) < 0 || ballX >= matrix.getScreenWidth())
  {
    ballXSpeed *= -1;
    ballX += ballXSpeed;
  }
  // We add the vertical speed to the ball. If the ball goes outside the screen,
  // then we flip the speed and then add the speed to the position again
  if ((ballY += ballYSpeed) < 0 || ballY >= matrix.getScreenHeight())
  {
    ballYSpeed *= -1;
    ballY += ballYSpeed;
  }
}

void displayBall(uint8_t color)
{
  // A ball is a single dot
  matrix.setPixel(ballX, ballY, color);
}

// This function is called repeatedly
void loop()
{
  // We set the whole screen to ON every CountMax loops
  if (countLoop == CountMax)
  {
    ledMatrixMax7219Control::Intensity intensity[2] =
      {
       ledMatrixMax7219Control::Intensity_0,
       ledMatrixMax7219Control::Intensity_15
      };

    resetBall();
    matrix.clearScreen(1);
    // Set different brightness levels of matrix, so a little variety appears when balls move from
    // a matrix to another one.
    matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_1, intensity[stepLoop]);
    matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_2, intensity[!stepLoop]);
    matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_3, intensity[stepLoop]);
    matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_4, intensity[!stepLoop]);
    countLoop = 0;
    stepLoop = !stepLoop;
  }

  // Remove the ball from screen (old position)
  displayBall(0);
  // Move the ball to its new position
  moveBall();
  // Set the ball on screen on its new position
  displayBall(1);

  // Refresh the screen
  matrix.displayScreen();
  // Increment the loop counter, so it finaly reach CountMax
  ++countLoop;
  // Sleep to temper the speed of the animation
  delay(10);
}
