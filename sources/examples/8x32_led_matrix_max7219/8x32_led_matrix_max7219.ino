/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

#include <ledMatrixMax7219Control.h>

ledMatrixMax7219Control matrix;

typedef struct s_ball
{
  float x;
  float y;
  float xspeed;
  float yspeed;
} t_ball;

t_ball balls[3];

void setup_ball(t_ball *ball)
{
  ball->x = random(matrix.getScreenWidth());
  ball->y = random(matrix.getScreenHeight());
  ball->xspeed = random(-10, 10) / 10.0;
  ball->yspeed = random(-10, 10) / 10.0;
}

void setup() 
{
  matrix.init();
  randomSeed(analogRead(0));
  for (int i = 0; i < sizeof(balls) / sizeof(balls[0]); ++i)
    setup_ball(&balls[i]);
}

void move_ball(t_ball *ball)
{
  if ((ball->x += ball->xspeed) < 0 || ball->x >= matrix.getScreenWidth())
    {
      ball->xspeed *= -1;
      ball->x += ball->xspeed;
    }
  if ((ball->y += ball->yspeed) < 0 || ball->y >= matrix.getScreenHeight())
    {
      ball->yspeed *= -1;
      ball->y += ball->yspeed;
    }
}

void display_ball(t_ball *ball, uint8_t color)
{
  matrix.setPixel(ball->x, ball->y, color);
}

void loop() 
{
  for (int i = 0; i < sizeof(balls) / sizeof(balls[0]); ++i)
    {
      display_ball(&balls[i], 0);
      move_ball(&balls[i]);
      display_ball(&balls[i], 1);
    }
  matrix.displayScreen();
  delay(10);
}
