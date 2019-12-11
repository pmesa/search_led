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

#define GND           16
#define CH3A          18
#define GND1          19
#define CH2A          20
#define NOA           21
#define COMA          22
#define NCA           23


#define NCB           34 //changed on board
#define GND2          35
#define COMB          36 //changed on board
#define GND3          37
#define CH2B          38
#define NOB           39
/*
  //DA0 = COMB
  //DA1 = NCB
  //A22 and A21 remapped to 36 and 34 - routing error
*/


//#define PIR1  20
//#define PIR2  13

//#define RESET           19
//#define TIEDIE          18
//#define CIRCLES         17
//#define RECT            16
//#define COMET           15
//#define NOISE           14

//#define RAINBOW_SCROLL_UP 21
//#define RAINBOW_SCROLL_DOWN 22

#define OFFSET 13

//other ideas


bool tiedie = false;
bool circles = false;
bool rect = false;
bool comet = false;
bool rainbowScrollUp = false;
bool rainbowScrollDown = false;
bool noise = false;

bool changePattern = false;

uint8_t switcher = 0;


uint32_t x, y, v_time, hue_time, hxy;
// how many octaves to use for the brightness and hue functions
uint8_t octaves = 1;
uint8_t hue_octaves = 3;
// the 'distance' between points on the x and y axis
int xscale = 57771;
int yscale = 57771;
// the 'distance' between x/y points for the hue noise
int hue_scale = 1;
// how fast we move through time & hue noise
int time_speed = 1111;
int hue_speed = 31;
// adjust these values to move along the x or y axis between frames
int x_speed = 331;
int y_speed = 1111;

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

int16_t counter;

void setup()
{
  Serial.begin(9600);
  delay(200);
  Serial.println("Starting");

  pinMode(CH3A, INPUT_PULLUP);
  pinMode(CH2A, INPUT_PULLUP);
  pinMode(NOA, INPUT_PULLUP);
  pinMode(NCA, INPUT_PULLUP);
  pinMode(NCB, INPUT_PULLUP);
  pinMode(CH2B, INPUT_PULLUP);
  pinMode(NOB, INPUT_PULLUP);

  pinMode(COMA, OUTPUT);
  pinMode(COMB, OUTPUT);
  pinMode(GND, OUTPUT);
  pinMode(GND1, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(GND3, OUTPUT);

  digitalWrite(COMA, LOW);
  digitalWrite(COMB, LOW);
  digitalWrite(GND, LOW);
  digitalWrite(GND1, LOW);
  digitalWrite(GND2, LOW);
  digitalWrite(GND3, LOW);

  random16_set_seed(8934);
  random16_add_entropy(analogRead(3));

  randomSeed(analogRead(0));

  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  ///FULL
  //FastLED.setBrightness(255);
  ///TEST
  FastLED.setBrightness(100);
  delay(500);


  FastLED.clear(true);

  hxy = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  x = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  y = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  v_time = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  hue_time = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();





  for (int i = 0; i < 72; i++)
  {

    leds.DrawPixel(0, i, CHSV(255, 127, 255));
    FastLED.show();
    delay(50);
  }

}


void loop()
{

  //verticalLineDown(127, 3);

  checkRemoteInputs();

  switch (switcher + OFFSET)
  {
    case TIEDIE:
      changePattern = false;
      tiediePattern();
      break;

    case CIRCLES:
      changePattern = false;
      circlesPattern();
      break;

    case RECT:
      changePattern = false;
      rectPattern();
      break;

    case COMET:
      changePattern = false;
      cometPattern();
      break;

    case NOISE:
      changePattern = false;
      rainbowScrollUpPattern();
      break;

    case RAINBOW_SCROLL_UP:
      changePattern = false;
      rainbowScrollUpPattern();
      switcher = 0;
      break;

    case RAINBOW_SCROLL_DOWN:
      changePattern = false;
      rainbowScrollDownPattern();
      switcher = 0;
      break;

    default:
      changePattern = false;
      noisePattern();
      break;
  }



}



void checkRemoteInputs()
{
  if (changePattern == true) //this  should debounce
  {

  }

  else
  {
    if (digitalRead(TIEDIE) == 0)
    {
      setAllFalse();
      tiedie = true;
      switcher = 1;
      changePattern = true;
    }


    if (digitalRead(CIRCLES) == 0)
    {
      setAllFalse();
      circles = true;
      switcher = 2;
      changePattern = true;
    }

    if (digitalRead(RECT) == 0)
    {
      setAllFalse();
      rect = true;
      switcher = 3;
      changePattern = true;
    }

    if (digitalRead(COMET) == 0)
    {
      setAllFalse();
      comet = true;
      switcher = 4;
      changePattern = true;
    }

    if (digitalRead(NOISE) == 0)
    {
      setAllFalse();
      rainbowScrollUp = true;
      switcher = 5;
      changePattern = true;
    }

    //    if (digitalRead(PIR1) == 1)
    //    {
    //
    //        setAllFalse();
    //        changePattern = false;
    //        rainbowScrollDown = true;
    //        switcher = 8;
    //        changePattern = true;
    //
    //
    //    }
    //
    //        if (digitalRead(PIR2) == 1)
    //    {
    //
    //        setAllFalse();
    //        changePattern = false;
    //        rainbowScrollUp = true;
    //        switcher = 9;
    //        changePattern = true;
    //
    //
    //    }


  }

}

void tiediePattern()
{
  randomSeed(analogRead(0));
  uint8_t randx = random(leds.Width());
  uint8_t randy = random(leds.Height());
  while (!changePattern)
  {

    myFirstTieDie(randx, randy);
  }
}

void rectPattern()
{
  uint8_t k , j, l;
  uint8_t count = 0;

  while ((count < 4) && (!changePattern))
  {
    count++;
    checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(16, 36, ForestColors_p);
  }

  count = 0;
  while ((count < 4) && (!changePattern))
  {
    count++;
    checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(8, 48, LavaColors_p);
  }

  count = 0;
  while ((count < 4) && (!changePattern))
  {
    count++;
    checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(24, 24, OceanColors_p);
  }

  count = 0;
  while ((count < 4) && (!changePattern))
  {
    count++;
    checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(8, 8, CloudColors_p);
  }

  FastLED.clear();
  count = 0;
  while ((count < 4) && (!changePattern))
  {
    count++;
    checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    expandingRainbowRectangle(randx, randy);
  }

  FastLED.clear();
}


void circlesPattern()
{
  randomSeed(analogRead(0));
  uint8_t randx = random(leds.Width());
  uint8_t randy = random(leds.Height());

  expandingRainbowCircle(randx, randy);

}


void cometPattern()
{
  randomSeed(A0);
  int  randCol = random(0, 255);
  while (!changePattern)
  {
    checkRemoteInputs();
    verticalLineUp(randCol, 4);

  }

}


void rainbowScrollUpPattern()
{
  int count = 0;
  while ((!changePattern) && (count < leds.Width()))
  {
    checkRemoteInputs();
    leds.DrawLine (count, 0, count, leds.Height(), CHSV(25 * count, 255, 255));
    if (count > 0)
    {
      leds.DrawLine (count - 1 , 0, count - 1, leds.Height(), CHSV(0, 0, 0));
    }

    if (count == leds.Width() - 1)
    {
      //leds.DrawLine (count, count ,0, leds.Height(),CHSV(0,0,0));
      count = 0;
    }
    count ++;
    FastLED.show();
    delay(100);
  }

}


void rainbowScrollDownPattern()
{
  int count = leds.Width() - 1;
  while ((!changePattern) && (count > 0))
  {
    checkRemoteInputs();
    leds.DrawLine (count, 0, count, leds.Height(), CHSV(25 * count, 255, 255));
    if (count > 0)
    {
      leds.DrawLine (count - 1 , 0, count - 1, leds.Height(), CHSV(0, 0, 0));
    }

    if (count == 0)
    {
      //leds.DrawLine (count, count ,0, leds.Height(),CHSV(0,0,0));
      count = 0;
    }
    count --;
    FastLED.show();
    delay(100);
  }

}


void noisePattern()
{

  checkRemoteInputs();
  fill_2dnoise16(FastLED.leds(), MATRIX_WIDTH, MATRIX_HEIGHT, true,
                 octaves, x, xscale, y, yscale, v_time,
                 hue_octaves, hxy, hue_scale, hxy, hue_scale, hue_time, false);

  checkRemoteInputs();
  LEDS.show();

  // adjust the intra-frame time values
  x += x_speed;
  y += y_speed;
  v_time += time_speed;
  hue_time += hue_speed;
}

void setAllFalse()
{
  delay(100); // becounce
  tiedie = false;
  circles = false;
  rect = false;
  comet = false;
  rainbowScrollUp = false;
  rainbowScrollDown = false;
  noise = false;

  FastLED.clear(true);
  expandingRainbowCircle(16, 36);
  FastLED.clear(true);
}



void expandingRainbowRectangle(uint8_t x, uint8_t y)

{
  uint8_t r = 0;
  uint8_t i = 0;

  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  while ((!changePattern) && (r < (leds.Height() / 2) - 5))
  {
    checkRemoteInputs();

    leds.DrawFilledRectangle(x, y, x + r, y + r, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 1, y + r + 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 2, y + r + 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 3, y + r + 3, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 4, y + r + 4, CHSV( r * 20 + randCol, 255, 255 - r * 20));



    if ( r > 1)
    {
      leds.DrawFilledRectangle(x - r - 2, y - r - 2, x, y, CHSV( r * 20 + randCol, 255, 255 - r * 20));
      leds.DrawFilledRectangle(x - r - 1, y - r - 1, x, y, CHSV( r * 20 + randCol, 255, 255 - r * 20));


      if (r == leds.Height() / 2)
      {

        leds.DrawFilledRectangle(x, y, x - r, y - r, CHSV(r * 20 + randCol, 255, 255 - r * 20));
        leds.DrawFilledRectangle(x, y, x - r - 1, y - r - 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));
        leds.DrawFilledRectangle(x, y, x - r - 2, y - r - 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
      }
    }

    r++;
    FastLED.show();

  }

}

void centralRectangle(uint8_t x, uint8_t y, CRGBPalette16 palette)

{
  uint8_t  i, p;
  uint8_t r = 0;

  float frac;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  while ((!changePattern) && (r < (leds.Height() / 2) - 5))
  {
    checkRemoteInputs();
    frac = (r / float(((leds.Height() / 2) - 5)));

    for (p = 0; p < 9; p++)
    {
      leds.DrawFilledRectangle(x + r, y + r, x + p, y + p, ColorFromPalette(palette, (255 - p)*frac, (255 - p) - frac * 255)); delay(3);
    }

    if ( r > 1)
    {
      for (p = 9; p > 0; p--)
      {
        leds.DrawFilledRectangle(x - p, y - p, x - r, y - r, ColorFromPalette(palette, (255 - p)*frac, (255 - p) - frac * 255)); delay(3);
      }
    }

    if (r == leds.Height() / 2)
    {
      for (p = 0; p < 9; p++)
      {
        leds.DrawFilledRectangle(x - r - p, y - r - p, x + r - p, y + r - p, ColorFromPalette(palette, (255 - p)*frac, (255 - p) - frac * 255)); delay(3);
      }

    }

    r++;

    FastLED.show();
    delay(1);
  }

}


void expandingGapCircle(uint8_t x, uint8_t y)

{
  uint8_t r , i;
  //float frac;

  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  for (r = 0; r < (leds.Height() / 3) - 5; r++)
  {
    //frac = (r / float(((leds.Height()/2)-5)));

    leds.DrawFilledCircle(x, y , r, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    //leds.DrawFilledCircle(x, y, r + 3, ColorFromPalette(palette,252*frac,252-frac*252));

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
      leds.DrawFilledCircle(x, y, r - 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( r * 20 + randCol, 255, 255 - r * 20));
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
      }
    }


    FastLED.show();
    delay(1);
  }

  for (r = 0; r < (leds.Height() / 3) - 5; r++)
  {
    leds.DrawFilledCircle(x, y , r,    CHSV( 0, 0, 0));
    leds.DrawFilledCircle(x, y, r + 1, CHSV( 0, 0, 0));
    leds.DrawFilledCircle(x, y, r + 2, CHSV( 0, 0, 0));
    leds.DrawFilledCircle(x, y, r + 3, CHSV( 0, 0, 0));

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( 0, 0, 0));
      leds.DrawFilledCircle(x, y, r - 1, CHSV( 0, 0, 0));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( 0, 0, 0));
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( 0, 0, 0));
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( 0, 0, 0));
      }
    }


    FastLED.show();
    delay(1);
  }
}


void myFirstTieDie(uint8_t x, uint8_t y)

{
  uint8_t r = 0;
  uint8_t i = 0;


  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  while ((!changePattern) && (r < (leds.Height() / 4)))
  {

    checkRemoteInputs();

    leds.DrawFilledCircle(x, y , r,    CHSV( r * 20 + randCol, 255, 255 - r * 20)); delay(4);
    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255 - r * 20)); delay(4);
    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255 - r * 20)); delay(4);
    leds.DrawFilledCircle(x, y, r + 3, CHSV( r * 20 + randCol, 255, 255 - r * 20)); delay(4);

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20)); delay(4);
      leds.DrawFilledCircle(x, y, r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20)); delay(4);

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( (r + 3) * 20 + randCol, 255, 255 - (r + 3) * 20)); delay(4);
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20)); delay(4);
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20)); delay(4);

      }
    }

    r++;
    FastLED.show();
    delay(1);
  }

  r =  (leds.Height() / 4) - 5;

  while ((!changePattern) && (r > 0))
  {
    checkRemoteInputs();
    leds.DrawFilledCircle(x, y , r,    CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 3, CHSV( r * 20 + randCol, 255, 255 - r * 20));

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20));
      leds.DrawFilledCircle(x, y, r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( (r + 3) * 20 + randCol, 255, 255 - (r + 3) * 20));
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20));
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20));

      }
    }

    r--;
    FastLED.show();

  }
}

void verticalLineUp(uint8_t hue, uint8_t thickness)
{
  int16_t y, t;

  while ((!changePattern) && (y < leds.Height()))
  {
    checkRemoteInputs();
    for (t = 0; t < thickness; t++)
    {
      leds.DrawLine(0, y + t, leds.Width() - 1, y + t, CHSV(hue + y * 20, 255, 255));
      if (y > t)
      {
        leds.DrawLine(0, y - thickness + t, leds.Width() - 1, y - thickness + t, CHSV(0, 0, 0));

      }


      if (y > thickness - 1)
      {
        leds.DrawLine(0, y - thickness + t, leds.Width() - 1, y - thickness + t, CHSV(0, 0, 0));

      }
    }

    y++;
    FastLED.show();

  }
  leds.DrawLine(0, leds.Height() - 1, leds.Width() - 1, leds.Height() - 1, CHSV(0, 0, 0));

}

void verticalLineDown(uint8_t hue, uint8_t thickness)
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



void expandingRainbowCircle(uint8_t x, uint8_t y)

{
  uint8_t i;

  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);
  int r = 0;

  while ((!changePattern) && (r < (leds.Height() / 2) - 5))
  {
    leds.DrawCircle(x, y , r,    CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 3, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 4, CHSV( r * 20 + randCol, 255, 255 - r * 20));



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
    r++;
  }






}


void rainbowNoise(uint8_t loops, int delay_time)
{
  uint16_t x, y, i;

  while (i <= loops)
  {
    for (x = 0; x < leds.Width(); x++)
    {
      for (y = 0; y < leds.Height(); y++)
      {
        leds.DrawPixel(x, y, CHSV(random(255), 127 + random(127), random(255)));
      }
    }
    FastLED.show();

    if (loops != 0)
    {
      i++;
    }

    delay(delay_time);
  }

}

void chevron(int x, int y, int l, boolean dir, CRGB Col, CRGB BGCol)
{
  int j = 0;

  leds.DrawFilledRectangle(0, 0, leds.Width(), leds.Height(), BGCol);

  for (int i = 0; i < max(y, leds.Height() - y); i++)
  {
    leds.DrawLine(x + ((dir ? -1 : 1) * (l + j)), y - i, x + ((dir ? -1 : 1) * (j)), y - i, Col);
    leds.DrawLine(x + ((dir ? -1 : 1) * (l + j)), y + i, x + ((dir ? -1 : 1) * (j)), y + i, Col);
    j++;
  }
  FastLED.show();
}


void scrolling_chevrons(int y, int len, int Col, int delay_time)
{
  int starting_x = leds.Width() + max(y, leds.Height() - y) + len;
  int num_chev = starting_x / len;

  for (int f = 0; f < len; f++)
  {

    for (int i = 0; i < num_chev; i++)
    {
      chevron(starting_x - (i * len), y, len, true, CHSV(Col, ((i + f) % len) * (255 / len), 80), CHSV(0, 0, 0));
    }

    FastLED.show();
    delay(delay_time);
  }
}
