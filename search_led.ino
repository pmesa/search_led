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


#define LED           13
#define GND           16
#define CH3ACOM       19 //swapped pins on RF reciever
#define CH3A          18 //swapped pins on RF reciever
#define CH2ACOM       20
#define CH2A          21
#define CH1ACOM       22
#define CH1A          23


#define NCB           34 //changed on board
#define GND2          35
#define COMB          36 //changed on board
#define GND3          37
#define CH2B          38
#define NOB           39


int UP = NOB;
int DOWN = CH2B;
int NYE = CH1A;
int PIR1 = CH2A;
int PIR2 = CH3A;

//DA0 = COMB
//DA1 = NCB
//A22 and A21 remapped to 36 and 34 - routing error

int debounceMs = 1050;
unsigned long lastRequested = 0;

//bool tiedie = false;
//bool circles = false;
//bool rect = false;
//bool comet = false;
//bool rainbowScrollUp = false;
//bool rainbowScrollDown = false;
//bool noise = false;



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


volatile int  mode = 1;
int firstMode = 1;
int lastMode = 5;
volatile bool changeRequested;
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
//  FastLED.setBrightness(255);
  ///TEST
  FastLED.setBrightness(100);

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

    case 2:
      changeRequested = false;
      blindMe();
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
      rainbowScrollUpPattern();
      break;

    case 12:
      changeRequested = false;
      rainbowScrollUpPattern();
      mode = 1;
      break;

    case 13:
      changeRequested = false;
      rainbowScrollDownPattern();
      mode = 1;
      break;
      
    default:
      changeRequested = false;
      tiediePatternRandom();
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

      mode = 12;
      modeChange();
    }


    if (digitalRead(PIR2) == 0)
    {

      mode = 13;
      modeChange();
    }

  }
}

void modeChange()
{
  digitalWrite(LED, !digitalRead(LED));
  changeRequested = true;
}

void tiediePattern()
{
  randomSeed(analogRead(0));
  uint8_t randx = random(leds.Width());
  uint8_t randy = random(leds.Height());
  
  while (!changeRequested)
  {
    myFirstTieDie(randx, randy);
  }
}


void tiediePatternRandom()
{
  
  while (!changeRequested)
  {
    randomSeed(analogRead(0));
    myFirstTieDie(random(leds.Width()), random(leds.Height()));
  }
}

void rectPattern()
{
  uint8_t k , j, l;
  uint8_t count = 0;

  while ((count < 4) && (!changeRequested))
  {
    count++;
    //checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(16, 36, ForestColors_p);
  }

  count = 0;
  while ((count < 4) && (!changeRequested))
  {
    count++;
    //checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(8, 48, LavaColors_p);
  }

  count = 0;
  while ((count < 4) && (!changeRequested))
  {
    count++;
    //checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(24, 24, OceanColors_p);
  }

  count = 0;
  while ((count < 4) && (!changeRequested))
  {
    count++;
    //checkRemoteInputs();
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(8, 8, CloudColors_p);
  }

  FastLED.clear();
  count = 0;
  while ((count < 4) && (!changeRequested))
  {
    count++;
    //checkRemoteInputs();
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
  int  randomColour = random(0, 255);
  while (!changeRequested)
  {
    //checkRemoteInputs();
    verticalLineUp(randomColour, 4);

  }
}

void pingPong()
{
  randomSeed(A0);
  int  randomColour = random(0, 255);
  while (!changeRequested)
  {
    //checkRemoteInputs();
    verticalLineUp(randomColour, 4);

  }
}

void rainbowScrollUpPattern()
{
  int count = 0;
  FastLED.clear();
  while ((!changeRequested) && (count < leds.Width()))
  {
    //checkRemoteInputs();
    leds.DrawLine (count, 0, count, leds.Height(), CHSV(25 * count, 255, 255));
    if (count > 0)
    {
      leds.DrawLine (count - 1 , 0, count - 1, leds.Height(), CHSV(0, 0, 0));
    }

//    if (count == leds.Width() - 1)
//    {
//      //leds.DrawLine (count, count ,0, leds.Height(),CHSV(0,0,0));
//      count = 0;
//    }
    count ++;
    FastLED.show();
    delay(100);
  }

  FastLED.clear();
}


void rainbowScrollDownPattern()
{
  int count = leds.Width() - 1;
  FastLED.clear();
  while ((!changeRequested) && (count >= 0))
  {
    //checkRemoteInputs();
    leds.DrawLine (count, 0, count, leds.Height(), CHSV(25 * count, 255, 255));
    if (count < leds.Width() - 1)
    {
      leds.DrawLine (count + 1 , 0, count + 1, leds.Height(), CHSV(0, 0, 0));
    }

//    if (count == 0)
//    {
//      //leds.DrawLine (count, count ,0, leds.Height(),CHSV(0,0,0));
//      count = 0;
//    }
    count --;
    FastLED.show();
    delay(100);
  }

  FastLED.clear();
}


void noisePattern()
{

  hxy = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  x = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  y = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  v_time = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  hue_time = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();

  //checkRemoteInputs();
  fill_2dnoise16(FastLED.leds(), MATRIX_WIDTH, MATRIX_HEIGHT, true,
                 octaves, x, xscale, y, yscale, v_time,
                 hue_octaves, hxy, hue_scale, hxy, hue_scale, hue_time, false);

  //checkRemoteInputs();
  LEDS.show();

  // adjust the intra-frame time values
  x += x_speed;
  y += y_speed;
  v_time += time_speed;
  hue_time += hue_speed;
}

void expandingRainbowRectangle(uint8_t x, uint8_t y)

{
  uint8_t r = 0;
  uint8_t i = 0;

  randomSeed(analogRead(0));
  uint8_t randomColour = random(0, 255);

  while ((!changeRequested) && (r < (leds.Height() / 2) - 5))
  {
    //checkRemoteInputs();

    leds.DrawFilledRectangle(x, y, x + r, y + r, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 1, y + r + 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 2, y + r + 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 3, y + r + 3, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 4, y + r + 4, CHSV( r * 20 + randomColour, 255, 255 - r * 20));



    if ( r > 1)
    {
      leds.DrawFilledRectangle(x - r - 2, y - r - 2, x, y, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
      leds.DrawFilledRectangle(x - r - 1, y - r - 1, x, y, CHSV( r * 20 + randomColour, 255, 255 - r * 20));


      if (r == leds.Height() / 2)
      {

        leds.DrawFilledRectangle(x, y, x - r, y - r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledRectangle(x, y, x - r - 1, y - r - 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledRectangle(x, y, x - r - 2, y - r - 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
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
  uint8_t randomColour = random(0, 255);

  while ((!changeRequested) && (r < (leds.Height() / 2) - 5))
  {
    //checkRemoteInputs();
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
  uint8_t randomColour = random(0, 255);

  for (r = 0; r < (leds.Height() / 3) - 5; r++)
  {
    //frac = (r / float(((leds.Height()/2)-5)));

    leds.DrawFilledCircle(x, y , r, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    //leds.DrawFilledCircle(x, y, r + 3, ColorFromPalette(palette,252*frac,252-frac*252));

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
      leds.DrawFilledCircle(x, y, r - 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
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
  uint8_t randomColour = random(0, 255);

  while ((!changeRequested) && (r < (leds.Height() / 4)))
  {

    leds.DrawFilledCircle(x, y , r,    CHSV( r * 20 + randomColour, 255, 255 - r * 20)); delay(4);
    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20)); delay(4);
    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20)); delay(4);
    leds.DrawFilledCircle(x, y, r + 3, CHSV( r * 20 + randomColour, 255, 255 - r * 20)); delay(4);

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( (r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20)); delay(4);
      leds.DrawFilledCircle(x, y, r - 1, CHSV( (r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20)); delay(4);

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( (r + 3) * 20 + randomColour, 255, 255 - (r + 3) * 20)); delay(4);
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( (r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20)); delay(4);
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( (r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20)); delay(4);

      }
    }

    r++;
    FastLED.show();
    delay(20);
  }

  r =  (leds.Height() / 4) - 5;

  while ((!changeRequested) && (r > 0))
  {
    //checkRemoteInputs();
    leds.DrawFilledCircle(x, y , r,    CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 3, CHSV( r * 20 + randomColour, 255, 255 - r * 20));

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( (r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20));
      leds.DrawFilledCircle(x, y, r - 1, CHSV( (r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( (r + 3) * 20 + randomColour, 255, 255 - (r + 3) * 20));
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( (r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20));
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( (r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20));

      }
    }

    r--;
    FastLED.show();

  }
}

void verticalLineUp(uint8_t hue, uint8_t thickness)
{
  int16_t pixelRow = 0;
  
  while ((!changeRequested) && (pixelRow < leds.Height()))
  {
    int16_t relativePixelRow;
    for (relativePixelRow = 0; relativePixelRow < thickness; relativePixelRow++)
    {
      leds.DrawLine(0, pixelRow + relativePixelRow, leds.Width() - 1, pixelRow + relativePixelRow, CHSV(hue + pixelRow * 20, 255, 255));
      
      if (pixelRow > relativePixelRow)
      {
        leds.DrawLine(0, pixelRow - thickness + relativePixelRow, leds.Width() - 1, pixelRow - thickness + relativePixelRow, CHSV(0, 0, 0));
      }

      if (pixelRow > thickness - 1)
      {
        leds.DrawLine(0, pixelRow - thickness + relativePixelRow, leds.Width() - 1, pixelRow - thickness + relativePixelRow, CHSV(0, 0, 0));
      }
    }

    pixelRow++;
    
    FastLED.show();

  }
  
  leds.DrawLine(0, leds.Height() - 1, leds.Width() - 1, leds.Height() - 1, CHSV(0, 0, 0));
}

void verticalLineDown(uint8_t hue, uint8_t thickness)
{
  int16_t pixelRow = leds.Height() - 1;
  while ((!changeRequested) && (pixelRow >= 0))
  {
    int16_t relativePixelRow;
    for (relativePixelRow = thickness; relativePixelRow > 0 ; relativePixelRow--)
    {
      leds.DrawLine(0, pixelRow + relativePixelRow, leds.Width() - 1, pixelRow + relativePixelRow, CHSV(hue + pixelRow * 20, 255, 255));
      
      if (pixelRow < relativePixelRow)
      {
        leds.DrawLine(0, pixelRow - thickness + relativePixelRow, leds.Width() - 1, pixelRow - thickness + relativePixelRow, CHSV(0, 0, 0));
      }

      if (pixelRow > thickness - 1)
      {
        leds.DrawLine(0, pixelRow - thickness + relativePixelRow, leds.Width() - 1, pixelRow - thickness + relativePixelRow, CHSV(0, 0, 0));
      }
    }

    pixelRow++;
    
    FastLED.show();

  }
  
  leds.DrawLine(0, leds.Height() - 1, leds.Width() - 1, leds.Height() - 1, CHSV(0, 0, 0));
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
  uint8_t randomColour = random(0, 255);
  int r = 0;

  while ((!changeRequested) && (r < (leds.Height() / 2) - 5))
  {
    leds.DrawCircle(x, y , r,    CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 1, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 2, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 3, CHSV( r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 4, CHSV( r * 20 + randomColour, 255, 255 - r * 20));



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

void blindMe()
{
  leds.DrawFilledRectangle(0, 0, leds.Width() - 1, leds.Height() - 1, CRGB(255, 255, 255));
  delay(100);
  FastLED.show();
}

//void setAllFalse()
//{
//  delay(100); // becounce
////  tiedie = false;
////  circles = false;
////  rect = false;
////  comet = false;
////  rainbowScrollUp = false;
////  rainbowScrollDown = false;
////  noise = false;
//
//  FastLED.clear(true);
//  expandingRainbowCircle(16, 36);
//  FastLED.clear(true);
//}
