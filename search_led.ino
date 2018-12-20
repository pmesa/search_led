#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix

// Change the next defines to match your matrix type and size
#define DATA_PIN            1

#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        32
#define MATRIX_HEIGHT       72
#define MATRIX_TYPE         VERTICAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;



int16_t counter;

void setup()
{

  randomSeed(analogRead(0));


  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  //FastLED_GFX.setTextColor(CRGB::White);
  delay(500);
 
    verticalLineUp(127, 3, 1);
    verticalLineDown(127, 3, 1);

  rainbowVerticalStripsLoop(1);

  rainbowHorizontalStripsLoop(5);

  FastLED.clear(true);


  counter = 0;
}


void loop()
{
  randomSeed(analogRead(0));

  uint8_t randx = random(leds.Width());
  uint8_t randy = random(leds.Height());
  expandingRainbowCircle(randx, randy);

/*

  rainbowVerticalStripsLoop(1);

  rainbowHorizontalStripsLoop(5);
  FastLED.clear(true);


  FastLED.showColor(CRGB::Blue);
  delay(2000);





  verticalLineUp(127, 3, 10);
  verticalLineDown(127, 3, 10);
  FastLED.showColor(CRGB::Red);
  delay(2000);
  FastLED.showColor(CRGB::Lime);
  delay(2000);
  FastLED.showColor(CRGB::Blue);
  delay(2000);
  FastLED.showColor(CRGB::Red);
  delay(2000);
  FastLED.clear(true);
  verticalLineUp(127, 3, 10);
  verticalLineDown(127, 3, 10);


  rainbowVerticalStripsLoop(5);
  FastLED.clear(true);
  delay(500);
  rainbowVerticalStripsLoop(5);
*/
}


void expandingRainbowCircle(uint8_t x, uint8_t y)

{
  uint8_t r , i;

  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  for (r = 0; r < (leds.Height() / 2) - 5; r++)
  {
    leds.DrawCircle(x, y , r,    CHSV( r * 20 + randCol, 255, 255-r*20));
    leds.DrawCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255-r*20));
    leds.DrawCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255-r*20));
    leds.DrawCircle(x, y, r + 3, CHSV( r * 20 + randCol, 255, 255-r*20));
    leds.DrawCircle(x, y, r + 4, CHSV( r * 20 + randCol, 255, 255-r*20));


    //leds.DrawFilledCircle(leds.Width()/2, leds.Height()/2, r,CHSV(0, 0,0));
    if ( r > 1)
    {
      leds.DrawCircle(x, y, r - 2, CHSV(0, 0, 0));
      leds.DrawCircle(x, y, r - 1, CHSV(0, 0, 0));
      // leds.DrawCircle(leds.Width() / 2, leds.Height() / 2, r-2, CHSV(0, 0, 0));

      if (r == leds.Height() / 2)
      {
        leds.DrawCircle(x, y,  r, CHSV(0, 0, 0));
        leds.DrawCircle(x, y,  r - 1, CHSV(0, 0, 0));
        leds.DrawCircle(x, y,  r - 2, CHSV(0, 0, 0));
      }
    }


    FastLED.show();
    delay(1);
  }




}



void verticalLineUp(uint8_t hue, uint8_t thickness, uint8_t wait)
{
  int16_t y, t;
  for (y = 0; y < leds.Height(); y++)
  {

    for (t = 0; t < thickness; t++)
    {
      leds.DrawLine(0, y + t, leds.Width() - 1, y + t, CHSV(hue, 255, 255));
      if (y >= thickness)
        leds.DrawLine(0, y - thickness + t, leds.Width() - 1, y - thickness + t, CHSV(0, 0, 0));
    }

    FastLED.show();
    // delay(wait);
  }
}

void verticalLineDown(uint8_t hue, uint8_t thickness, uint8_t wait)
{
  int16_t y, t;
  for (y = leds.Height(); y > 0; y--)
  {

    for (t = 0; t < thickness; t++)
    {
      leds.DrawLine(0, y - t, leds.Width() - 1, y - t, CHSV(hue, 255, 255));
      if (y >= thickness)
        leds.DrawLine(0, y + thickness - t, leds.Width() - 1, y + thickness - t, CHSV(0, 0, 0));
    }

    FastLED.show();
    //    delay(wait);
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

void rainbowNoise(uint8_t loops, int delay_time)
{
  uint16_t x,y,i;

  while(i <= loops)
  {
    for(x = 0; x < leds.Width(); x++)
    {
      for(y = 0; y < leds.Height(); y++)
      {
        leds.DrawPixel(x, y, CHSV(random(255), 127+random(127), random(255)));
      }
    }
    FastLED.show();

    if(loops != 0)
    {
      i++;
    }

    delay(delay_time);
  }
  
}

void chevron(int x, int y, int l, boolean dir, CRGB Col,CRGB BGCol)
{
  int j = 0;

  leds.DrawFilledRectangle(0, 0, leds.Width(), leds.Height(), BGCol);
  
  for(int i=0;i<max(y,leds.Height()-y);i++)
  {
    leds.DrawLine(x+((dir?-1:1)*(l+j)), y-i, x+((dir?-1:1)*(j)), y-i, Col);
    leds.DrawLine(x+((dir?-1:1)*(l+j)), y+i, x+((dir?-1:1)*(j)), y+i, Col);    
    j++;
  }
  FastLED.show();
}
