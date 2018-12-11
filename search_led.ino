#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix

// Change the next defines to match your matrix type and size
#define DATA_PIN            1

#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        8
#define MATRIX_HEIGHT       72
#define MATRIX_TYPE         VERTICAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;



int16_t counter;

void setup()
{
  // initial LEDs
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(5);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(200);
  FastLED.showColor(CRGB::Lime);
  delay(200);
  FastLED.showColor(CRGB::Blue);
  delay(200);
  FastLED.showColor(CRGB::White);
  delay(200);
  FastLED.clear(true);

  counter = 0;
}


void loop()
{

  verticalLineUp(127,3,10);
  verticalLineDown(127,3,10);
  
  rainbowHorizontalStripsLoop(5);
  FastLED.clear(true);
  delay(500);
  rainbowVerticalStripsLoop(5);
  FastLED.clear(true);
  delay(500);
}





void verticalLineUp(uint8_t hue, uint8_t thickness, uint8_t wait)
{
  int16_t y, t;
  for (y = 0; y < leds.Height(); y++)
  {
    
    for (t = 0; t < thickness; t++)
    {
      leds.DrawLine(0, y + t, leds.Width() - 1, y + t, CHSV(hue, 255, 255));
      if(y>=thickness)
        leds.DrawLine(0,y -thickness + t, leds.Width() - 1, y - thickness + t, CHSV(0, 0, 0));
    }

    FastLED.show();
    delay(wait);
  }
}

void verticalLineDown(uint8_t hue, uint8_t thickness, uint8_t wait)
{
  int16_t y, t;
  for (y = leds.Height(); y>0; y--)
  {
    
    for (t = 0; t < thickness; t++)
    {
      leds.DrawLine(0, y - t, leds.Width() - 1, y - t, CHSV(hue, 255, 255));
      if(y>=thickness)
        leds.DrawLine(0,y +thickness - t, leds.Width() - 1, y + thickness - t, CHSV(0, 0, 0));
    }

    FastLED.show();
    delay(wait);
  }
}

void rainbowVerticalStripsLoop(uint8_t loops)
{
  uint8_t hue;
  int16_t x, y, i;
  uint8_t h;

  for (i = 0; i < loops * 50; i++)
  {
    h = hue;

    // ** Fill LED's with Vertical stripes
    for (x = 0; x < leds.Width(); x++)
    {
      leds.DrawLine(x, 0, x, leds.Height() - 1, CHSV(h, 255, 255));
      h += 16;
    }

    hue += 2;

    FastLED.show();
  }
}

void rainbowHorizontalStripsLoop(uint8_t loops)
{
  uint8_t hue;
  int16_t x, y, i;
  uint8_t h;

  for (i = 0; i < loops * 50; i++)
  {
    h = hue;

    // ** Fill LED's with horizontal stripes
    for (y = 0; y < leds.Height(); y++)
    {
      leds.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 255));
      h += 16;
    }

    hue += 2;

    FastLED.show();
  }
}
