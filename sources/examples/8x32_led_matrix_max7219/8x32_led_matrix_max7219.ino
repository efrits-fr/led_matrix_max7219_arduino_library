/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

#include <ledMatrixMax7219Control.h>

enum { NbBalls = 3 };
enum { CountMax = 500 };

ledMatrixMax7219Control matrix;

uint8_t countLoop = 0;

typedef struct s_ball
{
  float x;
  float y;
  float xSpeed;
  float ySpeed;
} t_ball;

t_ball balls[NbBalls];

void setupBall(t_ball * ball)
{
  ball->x = random(matrix.getScreenWidth());
  ball->y = random(matrix.getScreenHeight());
  ball->xSpeed = random(-10, 10) / 10.0;
  ball->ySpeed = random(-10, 10) / 10.0;
}

void setup()
{
  matrix.init();
  matrix.clearScreen(1);
  
  randomSeed(analogRead(0));
  for (uint8_t i = 0; i < NbBalls; ++i)
  {
    setupBall(&balls[i]);
  }

  matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_1, ledMatrixMax7219Control::Intensity_0);
  matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_2, ledMatrixMax7219Control::Intensity_15);
  matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_3, ledMatrixMax7219Control::Intensity_0);
  matrix.setBrightnessOfLEDMatrix(ledMatrixMax7219Control::ChipsetId_4, ledMatrixMax7219Control::Intensity_15);

}

void moveBall(t_ball * ball)
{
  if ((ball->x += ball->xSpeed) < 0 || ball->x >= matrix.getScreenWidth())
  {
    ball->xSpeed *= -1;
    ball->x += ball->xSpeed;
  }
  if ((ball->y += ball->ySpeed) < 0 || ball->y >= matrix.getScreenHeight())
  {
    ball->ySpeed *= -1;
    ball->y += ball->ySpeed;
  }
}

void displayBall(t_ball * ball, uint8_t color)
{
  matrix.setPixel(ball->x, ball->y, color);
}

void loop() 
{
  if (countLoop == CountMax)
  {
    matrix.clearScreen(1);
    countLoop = 0;
  }
  
  for (uint8_t i = 0; i < NbBalls; ++i)
  {
    displayBall(&balls[i], 0);
    moveBall(&balls[i]);
    displayBall(&balls[i], 1);
  }
  
  matrix.displayScreen();
  ++countLoop;
  delay(10);
}
