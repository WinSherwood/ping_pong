#include <Adafruit_NeoPixel.h>
#define PIN 6
#define WIDTH 8
#define HEIGHT 8
#define NUMPIXELS WIDTH * HEIGHT // Колличество пикселей
#define PADDLE_SIZE 2 // Размер площадки игрока
#define BUTTON_R 3
#define BUTTON_L 4
#define DELAY 50
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int ballX = random(WIDTH);
int ballY = random(3,6); // /Мяч появляется в верхней или нижней зоне
int ballDirX = random(2) * 2 - 1; // Случайное направление по горизонтали
int ballDirY = random(2) * 2 - 1; // Случайное направление по вертикали
int paddleY1 = HEIGHT / 2 - PADDLE_SIZE / 2; // Начальная позиция 
int paddleX1 = HEIGHT / 2 - PADDLE_SIZE / 2; // Начальная позиция 
int paddleY2 = HEIGHT / 2 - PADDLE_SIZE / 2; // Начальная позиция 
int paddleX2 = HEIGHT / 2 - PADDLE_SIZE / 2; // Начальная позиция 
int scorePlayer = 0;
int scoreOpponent = 0;
void resetBall() {
  ballX = random(WIDTH);
  ballY = random(2) * (HEIGHT - 1);
  ballDirX = random(2) * 2 - 1;
  ballDirY = random(2) * 2 - 1;
                  }
void setup()
{
   strip.begin(); 
   strip.show();
   strip.setBrightness(50);
   pinMode(BUTTON_R, INPUT_PULLUP);
   pinMode(BUTTON_L, INPUT_PULLUP);
   Serial.begin(9600);
   Serial.begin(9600);  
   pinMode(BUTTON_R, INPUT);
   digitalWrite(BUTTON_R, HIGH);
   pinMode(BUTTON_L, INPUT);
   digitalWrite(BUTTON_L, HIGH);
}

void loop() 
{
  strip.clear();
  if (digitalRead(BUTTON_R) == LOW) {
    Serial.println("Button R is pressed");
    delay(DELAY);
  }

  else if (digitalRead(BUTTON_L) == LOW) {
    Serial.println("Button L is pressed");
    delay(DELAY);
  }
   // Обновление позиции мяча
  ballX += ballDirX;
  ballY += ballDirY;

  // Проверка столкновения со стенками
  if (ballX <= 0 || ballX >= WIDTH - 1) {
    ballDirX *= -1;
  }
  if (ballY <= 0 || ballY >= HEIGHT - 1) {
    ballDirY *= -1;
  }

    // Проверка на пропуск мяча игроком
  if (ballY == 0 && (ballX < paddleY1 || ballX >= paddleY1 + PADDLE_SIZE)) 
  {
    scoreOpponent++;
    resetBall();
  }
   else if (ballY == HEIGHT - 1 && (ballX < paddleY1 || ballX >= paddleY1 + PADDLE_SIZE)) {
    scorePlayer++;
    resetBall();
  }

    // Управление площадкой игрока 1
  if (!digitalRead(BUTTON_R) && paddleY1 > 0)
   {
    paddleY1--;
   }
  if (digitalRead(BUTTON_R) && paddleY1 < HEIGHT - PADDLE_SIZE)
   {
    paddleY1++;
  }

// Управление площадкой игрока 2
  if (!digitalRead(BUTTON_R) && paddleY2 > 0)
   {
    paddleY2--;
   }
  if (digitalRead(BUTTON_R) && paddleY2 < HEIGHT - PADDLE_SIZE)
   {
    paddleY2++;
  }}