#include <FastLED.h>   //https://github.com/FastLED/FastLED
#include <LEDMatrix.h> //https://github.com/Jorgen-VikingGod/LEDMatrix

// Change the next defines to match your matrix type and size
#define DATA_PIN 1

#define COLOR_ORDER GRB
#define CHIPSET WS2812B

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH 28
#define MATRIX_HEIGHT 72
#define MATRIX_TYPE VERTICAL_ZIGZAG_MATRIX
#define MATRIX_SIZE (MATRIX_WIDTH * MATRIX_HEIGHT)
#define NUMPIXELS MATRIX_SIZE

#define LED 13
#define GND 16
#define CH3ACOM 19 //swapped pins on RF reciever
#define CH3A 18    //swapped pins on RF reciever
#define CH2ACOM 20
#define CH2A 21
#define CH1ACOM 22
#define CH1A 23

#define NCB 34 //changed on board
#define GND2 35
#define COMB 36 //changed on board
#define GND3 37
#define CH2B 38
#define NOB 39

//#define

int UP = NOB;
int DOWN = CH2B;
int NYE = CH1A;
int PIR1 = CH2A;
int PIR2 = CH3A;

//DA0 = COMB
//DA1 = NCB
//A22 and A21 remapped to 36 and 34 - routing error

unsigned long debounceMs = 1050;
unsigned long lastRequested = 0;


// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

volatile int mode = 1;
int firstMode = 1;
int lastMode = 6;

volatile bool changeRequested;
volatile bool pirRequested;
volatile bool PIR1triggered = false;
volatile bool PIR2triggered = false;

bool doNotDisturb = false;

void setup()
{

  Serial.begin(115200);
  delay(200);
  Serial.println("Starting");

  // Set initialization values for

  pinMode(CH3A, INPUT_PULLUP);
  pinMode(CH2A, INPUT_PULLUP);
  pinMode(CH1A, INPUT_PULLUP);
  pinMode(NCB, INPUT_PULLUP);
  pinMode(CH2B, INPUT_PULLUP);
  pinMode(NOB, INPUT_PULLUP);

  pinMode(LED, OUTPUT);
  pinMode(COMB, OUTPUT);
  pinMode(GND, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(GND3, OUTPUT);
  pinMode(CH3ACOM, OUTPUT);
  pinMode(CH2ACOM, OUTPUT);
  pinMode(CH1ACOM, OUTPUT);

  digitalWrite(CH1ACOM, LOW);
  digitalWrite(CH2ACOM, LOW);
  digitalWrite(CH3ACOM, LOW);
  digitalWrite(COMB, LOW);
  digitalWrite(GND, LOW);
  digitalWrite(GND2, LOW);
  digitalWrite(GND3, LOW);

  attachInterrupt(digitalPinToInterrupt(UP), checkRemoteInputs, FALLING);
  attachInterrupt(digitalPinToInterrupt(DOWN), checkRemoteInputs, FALLING);
  attachInterrupt(digitalPinToInterrupt(NYE), checkRemoteInputs, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIR1), checkRemoteInputs, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIR2), checkRemoteInputs, FALLING);

  random16_set_seed(8934);
  random16_add_entropy(analogRead(3));

  randomSeed(analogRead(0));

  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  ///FULL
  FastLED.setBrightness(25);
  ///TEST
  //  FastLED.setBrightness(255);

  FastLED.clear(true);

  for (int i = 0; i < 10; i++)
  {

    leds.DrawPixel(0, i, CHSV(255, 127, 255));
    FastLED.show();
    delay(1);
  }

  delay(1000);
  FastLED.clear();
}

void loop()
{

  Serial.print("Mode: ");
  Serial.println(mode);

  //Menu
  switch (mode)
  {
    case 1:
      changeRequested = false;
      tiediePatternRandom();
      break;

      break;

    case 2:
      changeRequested = false;
      noisePattern();
      break;

    case 3:
      changeRequested = false;
      rectPattern();
      break;

    case 4:
      changeRequested = false;
      cometPattern();
      break;

    case 5:
      changeRequested = false;
      circlesPattern();
      break;

    case 6:
      changeRequested = false;
      simpleRainPattern();

      break;

   case 2020:
    changeRequested = false;
    nye();
    mode = 1;
    break;

    default:
      changeRequested = false;
      simpleRainPattern();
      break;
  }
}

void modeUp()
{
  mode++;

  if (mode > lastMode)
  {
    mode = firstMode;
  }
}

void modeDown()
{
  mode--;

  if (mode > lastMode)
  {
    mode = firstMode;
  }
  else if (mode <= 0)
  {
    mode = lastMode;
  }
}

void checkRemoteInputs()
{

  if (millis() - lastRequested > debounceMs)
  {

    lastRequested = millis();
    delay(15);

    if (digitalRead(UP) == 0)
    {
      modeUp();
      modeChange();
    }

    if (digitalRead(DOWN) == 0)
    {

      modeDown();
      modeChange();
    }

    if (digitalRead(NYE) == 0)
    {

      mode = 2020;

      modeChange();
    }

    if (digitalRead(PIR1) == 0)
    {
      digitalWrite(LED, !digitalRead(LED));
      PIR1triggered = true;
      pirRequested = true;
    }

    if (digitalRead(PIR2) == 0)
    {
      digitalWrite(LED, !digitalRead(LED));
      PIR2triggered = true;
      pirRequested = true;
    }
  }
}

void modeChange()
{
  digitalWrite(LED, !digitalRead(LED));
  FastLED.clear(true);
  FastLED.show();
  changeRequested = true;
}

void clearPIRs()
{
  PIR1triggered = false;
  PIR2triggered = false;
  pirRequested = false;
}
