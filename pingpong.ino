#include <Adafruit_NeoPixel.h>
#ifdef _AVR_
#include <avr/power.h>
#endif
#define PIN 6
#define WIDTH 16 
#define HEIGHT 16 
#define NUMPIXELS WIDTH * HEIGHT // количество пикселей
#define PADDLE_SIZE 4 // размер платформы
#define BUTTON_1 3 // пин кнопки игрока 1
#define BUTTON_2 4 // пин кнопки игрока 2

int ballX = random(WIDTH);
int ballY = random(7,9); // мяч в верхней или нижне й зоне
int ballDirX = 1; // направление по горизонтали
int ballDirY = 1; // направление по вертикали
int paddleY1 = 0; // начальное положение первого по оси y
int paddleX1 = WIDTH/2; // начальное положение первого по оси x
int paddleY2 = HEIGHT-1; // начальное положение второго по оси y
int paddleX2 = WIDTH/2; // начальное положение первого по оси x
int scorePlayer1 = 0;
int scorePlayer2 = 0;

Adafruit_NeoPixel NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
   NeoPixel.begin();
   NeoPixel.show();
   Serial.begin(9600);
   pinMode(BUTTON_1, INPUT_PULLUP);
   pinMode(BUTTON_2, INPUT_PULLUP);

}

int getPixelNumber(int x, int y)
{
  // связь осей(x,y) и номера светодиода
  if (y % 2 == 0)
  {
    return y * WIDTH + x;
  } 
  else
  {
    return y * WIDTH + (WIDTH - 1 - x);
  }
}

void resetBall() // возврат мяча
 {
   ballX = random(WIDTH);
   ballY = random(7,9);
   ballDirX = 1;
   ballDirY = 1;
 }

void loop()
 {
  NeoPixel.clear();

   ballX += ballDirX;
   ballY += ballDirY;

  // столкновение по стенами
  if (ballX == 0 || ballX == WIDTH - 1) 
  {
    ballDirX *= -1;
  }

  
   if ( (ballY == 0 || ballY == HEIGHT - 1) && (ballX > paddleX1 && ballX <= paddleX1 + PADDLE_SIZE))
   {
    ballDirY *= -1;
   }
   else if ( (ballY == 0 || ballY == HEIGHT - 1) && (ballX > paddleX2 && ballX <= paddleX2 + PADDLE_SIZE))
   {
    ballDirY *= -1;
   }

  // проверка пропуска мяча
  if (ballY == 0 && (ballX < paddleX1 || ballX >= paddleX1 + PADDLE_SIZE)) 
  {
    scorePlayer2++;
    resetBall();
  }
   else if (ballY == HEIGHT - 1 && (ballX < paddleX2 || ballX >= paddleX2 + PADDLE_SIZE)) 
   {
    scorePlayer1++;
    resetBall();
   }

  // управление первой платформой
  if (!digitalRead(BUTTON_1) && paddleX1 < WIDTH - PADDLE_SIZE)
   {
    paddleX1++;
   }
  if (digitalRead(BUTTON_1) && paddleX1 > 0)
   {
    paddleX1--;
  }

   // управление второй платформой
  if (!digitalRead(BUTTON_2)&& paddleX2 > 0)
   {
    paddleX2--;
   }
  if (digitalRead(BUTTON_2) && paddleX2 < WIDTH - PADDLE_SIZE )
   {
    paddleX2++;
  }

  // отображние первой платформы
  for (int i = 0; i < PADDLE_SIZE; i++)
  {
    NeoPixel.setPixelColor(getPixelNumber(paddleX1 + i, 0), NeoPixel.Color(0, 0, 150));
  }

  // отображение второй платформы
  for (int i = 0; i < PADDLE_SIZE; i++)
  {
    NeoPixel.setPixelColor(getPixelNumber(paddleX2 + i, HEIGHT - 1), NeoPixel.Color(0, 150, 0));
  }

  // отображение мяча
   NeoPixel.setPixelColor(getPixelNumber(ballX, ballY), NeoPixel.Color(150, 0, 0));

   NeoPixel.show();
   delay(100); // скорость мяча

   // обновление счета 
  static unsigned long LastScoreUpdateTime = 0;
  if (millis() - LastScoreUpdateTime >= 1000)
   {
    Serial.print("Player 1: ");
    Serial.print(scorePlayer1);
    Serial.print(" - Player 2: ");
    Serial.println(scorePlayer2);
    LastScoreUpdateTime = millis();
   }
 }