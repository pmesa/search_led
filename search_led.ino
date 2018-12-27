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


#define PIR1  13
#define PIR2  12

#define RESET           19
#define TIEDIE          18
#define CIRCLES         17
#define RECT            16
#define COMET           15
#define SCROLL_RAINBOW  14

#define OFFSET 13

//other ideas

#define METEOR_SHOWER 6

bool tiedie = false;
bool circles = false;
bool rect = false;
bool comet = false;
bool scroll_rainbow = false;

bool changePattern = false;

uint8_t switcher = 0;

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;



int16_t counter;

void setup()
{

  pinMode(RESET, INPUT_PULLUP);
  pinMode(TIEDIE, INPUT_PULLUP);
  pinMode(CIRCLES, INPUT_PULLUP);
  pinMode(RECT, INPUT_PULLUP);
  pinMode(COMET, INPUT_PULLUP);
  pinMode(SCROLL_RAINBOW, INPUT_PULLUP);
  pinMode(PIR1, INPUT_PULLUP);
  pinMode(PIR2, INPUT_PULLUP);


  randomSeed(analogRead(0));

  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  delay(500);


  FastLED.clear(true);

  verticalLineUp(127, 3);
  verticalLineDown(127, 3);

  counter = 0;
}


void loop()
{
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

    case SCROLL_RAINBOW:
      changePattern = false;
      scrollRainbowPattern();
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

    if (digitalRead(SCROLL_RAINBOW) == 0)
    {
      setAllFalse();
      scroll_rainbow = true;
      switcher = 5;
      changePattern = true;
    }


  }

}

void tiediePattern()
{
  randomSeed(analogRead(0));
  uint8_t randx = random(leds.Width());
  uint8_t randy = random(leds.Height());
  while(!changePattern)
  {
  checkRemoteInputs();
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
  myFirstTieDie(randx, randy);
}


void cometPattern()
{
  randomSeed(A0); 
  int  randCol = random(0,255);
  while(!changePattern)
  {
    checkRemoteInputs();
    verticalLineUp(randCol, 4);

  }

}


void scrollRainbowPattern()
{
 int count =0; 
 while ((!changePattern)&&(count<leds.Width()))
 {
  checkRemoteInputs();
  leds.DrawLine (count, 0, count, leds.Height(),CHSV(25*count,255,255));
  if(count>0)
  {
   leds.DrawLine (count-1 ,0, count-1, leds.Height(),CHSV(0,0,0));
  }

  if(count == leds.Width()-1)
  {
    //leds.DrawLine (count, count ,0, leds.Height(),CHSV(0,0,0));
    count = 0;
  }
  count ++;
  FastLED.show();
  delay(100);
 }
 
}

void setAllFalse()
{
  delay(100); // becounce
  tiedie = false;
  circles = false;
  rect = false;
  comet = false;
  scroll_rainbow = false;
  FastLED.clear(true);
  expandingRainbowCircle(16, 36);
  FastLED.clear(true);
}



void expandingRainbowRectangle(uint8_t x, uint8_t y)

{
  uint8_t r , i;

  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  for (r = 0; r < (leds.Height() / 2) - 5; r++)
  {
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


    FastLED.show();
    delay(1);
  }

}

void centralRectangle(uint8_t x, uint8_t y, CRGBPalette16 palette)

{
  uint8_t r , i, p;

  float frac;
  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);



  for (r = 0; r < (leds.Height() / 2) - 5; r++)
  {
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
  uint8_t r , i;

  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  for (r = 0; r < (leds.Height() / 4) - 5; r++)
  {
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


    FastLED.show();
    delay(1);
  }


  for (r =  (leds.Height() / 4) - 5; r > 0 ; r--)
  {
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


    FastLED.show();

  }
}

void verticalLineUp(uint8_t hue, uint8_t thickness)
{
  int16_t y, t;
  
  while ((!changePattern)&&(y < leds.Height()))
  {
    checkRemoteInputs();
    for (t = 0; t < thickness; t++)
    {
      leds.DrawLine(0, y + t, leds.Width() - 1, y + t, CHSV(hue+y*20, 255, 255));
      if (y>t)
      {
        leds.DrawLine(0, y - thickness + t, leds.Width() - 1, y - thickness + t, CHSV(0, 0, 0));
        
      }

      
      if (y > thickness-1)
      {
        leds.DrawLine(0, y - thickness + t, leds.Width() - 1, y - thickness + t, CHSV(0, 0, 0));
        
      }
    }

    y++;
    FastLED.show();
    
  }
   leds.DrawLine(0, leds.Height()-1, leds.Width() - 1, leds.Height()-1, CHSV(0, 0, 0));
        
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
  uint8_t r , i;

  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randCol = random(0, 255);

  for (r = 0; r < (leds.Height() / 2) - 5; r++)
  {
    leds.DrawCircle(x, y , r,    CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 3, CHSV( r * 20 + randCol, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 4, CHSV( r * 20 + randCol, 255, 255 - r * 20));


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
