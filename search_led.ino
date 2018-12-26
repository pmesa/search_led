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

//other ideas

#define METEOR_SHOWER 6

bool tidie = false;
bool circles = false;
bool rect = false;
bool comet = false;
bool scroll_rainbow = false;

bool changePattern = false;


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


  counter = 0;
}


void loop()
{

  uint8_t k , j, l;
  randomSeed(analogRead(0));

  for (l = 0; l < 3; l++)
  {
    randomSeed(analogRead(0));
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(16, 36, ForestColors_p);
  }

  for (l = 0; l < 3; l++)
  {
    randomSeed(analogRead(0));
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(8, 48, LavaColors_p);
  }

  for (l = 0; l < 3; l++)
  {
    randomSeed(analogRead(0));
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(24, 24, OceanColors_p);
  }

  for (l = 0; l < 3; l++)
  {
    randomSeed(analogRead(0));
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    centralRectangle(8, 8, CloudColors_p);
  }

  FastLED.clear();

  for (k = 0; k < 12; k++)
  {
    randomSeed(analogRead(0));
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    expandingRainbowRectangle(randx, randy);
  }

  FastLED.clear();

  for (j = 0; j < 12; j++)
  {
    randomSeed(analogRead(0));
    uint8_t randx = random(leds.Width());
    uint8_t randy = random(leds.Height());
    myFirstTieDie(randx, randy);
  }

  FastLED.clear();



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
      tidie = true;
      changePattern = true;
    }


    if (digitalRead(CIRCLES) == 0)
    {
      setAllFalse();
      circles = true;
      changePattern = true;
    }

    if (digitalRead(RECT) == 0)
    {
      setAllFalse();
      changePattern = true;
    }

    if (digitalRead(COMET) == 0)
    {
      setAllFalse();
      comet = true;
      changePattern = true;
    }

    if (digitalRead(SCROLL_RAINBOW) == 0)
    {
      setAllFalse();
      scroll_rainbow = true;
      changePattern = true;
    }


  }

}


void setAllFalse()
{
  delay(100); // becounce
  tidie = false;
  circles = false;
  rect = false;
  comet = false;
  scroll_rainbow = false;
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
    //    leds.DrawFilledCircle(x+16,y+36, r,    CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x+16,y+36, r + 1, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x+16,y+36, r + 2, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x+16,y+36, r + 3, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x, y+36 , r, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x, y+36, r + 1, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x, y+36, r + 2, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x, y+36, r + 3, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x+16,y, r,    CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x+16,y, r + 1, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x+16,y, r + 2, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);
    //    leds.DrawFilledCircle(x+16,y, r + 3, CHSV( r * 20 + randCol, 255, 255-r*20));delay(1);

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20)); delay(4);
      leds.DrawFilledCircle(x, y, r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20)); delay(4);
      //      leds.DrawFilledCircle(x+16,y+36, r - 2, CHSV( (r+1) * 20 + randCol, 255, 255-(r+1)*20));delay(1);
      //      leds.DrawFilledCircle(x+16,y+36, r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));delay(1);
      ////      leds.DrawFilledCircle(x+16,y, r - 2, CHSV( (r+1) * 20 + randCol, 255, 255-(r+1)*20));delay(1);
      //      leds.DrawFilledCircle(x+16,y, r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));delay(1);
      //      leds.DrawFilledCircle(x,y+36, r - 2, CHSV( (r+1) * 20 + randCol, 255, 255-(r+1)*20));delay(1);
      //      leds.DrawFilledCircle(x,y+36, r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));delay(1);

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( (r + 3) * 20 + randCol, 255, 255 - (r + 3) * 20)); delay(4);
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20)); delay(4);
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20)); delay(4);
        //        leds.DrawFilledCircle(x+16,y+36,  r, CHSV( (r+3) * 20 + randCol, 255, 255-(r+3)*20));delay(1);
        //        leds.DrawFilledCircle(x+16,y+36,  r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));delay(1);
        //        leds.DrawFilledCircle(x+16,y+36,  r - 2, CHSV( (r+1)* 20 + randCol, 255, 255-(r+1)*20));delay(1);
        ////        leds.DrawFilledCircle(x+16,y,  r, CHSV( (r+3) * 20 + randCol, 255, 255-(r+3)*20));delay(1);
        //        leds.DrawFilledCircle(x+16,y,  r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));delay(1);
        //        leds.DrawFilledCircle(x+16,y,  r - 2, CHSV( (r+1)* 20 + randCol, 255, 255-(r+1)*20));delay(1);
        //        leds.DrawFilledCircle(x,y+36,  r, CHSV( (r+3) * 20 + randCol, 255, 255-(r+3)*20));delay(1);
        //        leds.DrawFilledCircle(x,y+36,  r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));delay(1);
        //        leds.DrawFilledCircle(x,y+36,  r - 2, CHSV( (r+1)* 20 + randCol, 255, 255-(r+1)*20));delay(1);
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
    //    leds.DrawFilledCircle(x+16,y+36, r,    CHSV( r * 20 + randCol, 255, 255-r*20));
    //    leds.DrawFilledCircle(x+16,y+36, r + 1, CHSV( r * 20 + randCol, 255, 255-r*20));
    //    leds.DrawFilledCircle(x+16,y+36, r + 2, CHSV( r * 20 + randCol, 255, 255-r*20));
    //    leds.DrawFilledCircle(x+16,y+36, r + 3, CHSV( r * 20 + randCol, 255, 255-r*20));

    if ( r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20));
      leds.DrawFilledCircle(x, y, r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20));
      //      leds.DrawFilledCircle(x+16,y+36, r - 2, CHSV( (r+1) * 20 + randCol, 255, 255-(r+1)*20));
      //      leds.DrawFilledCircle(x+16,y+36, r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y,  r, CHSV( (r + 3) * 20 + randCol, 255, 255 - (r + 3) * 20));
        leds.DrawFilledCircle(x, y,  r - 1, CHSV( (r + 2) * 20 + randCol, 255, 255 - (r + 2) * 20));
        leds.DrawFilledCircle(x, y,  r - 2, CHSV( (r + 1) * 20 + randCol, 255, 255 - (r + 1) * 20));
        //        leds.DrawFilledCircle(x+16,y+36,  r, CHSV( (r+3) * 20 + randCol, 255, 255-(r+3)*20));
        //        leds.DrawFilledCircle(x+16,y+36,  r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));
        //        leds.DrawFilledCircle(x+16,y+36,  r - 2, CHSV( (r+1)* 20 + randCol, 255, 255-(r+1)*20));
      }
    }


    FastLED.show();
    delay(5);
  }
}

//  for (r = (leds.Height() / 4) - 5; r == 0 ; r--)
//  {
//    leds.DrawFilledCircle(x, y , r,    CHSV( r * 20 + randCol, 255, 255-r*20));
//    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255-r*20));
//    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255-r*20));
//    leds.DrawFilledCircle(x, y, r + 3, CHSV( r * 20 + randCol, 255, 255-r*20));
////    leds.DrawFilledCircle(x, y, r + 4, CHSV( r * 20 + randCol, 255, 255-r*20));
////    leds.DrawFilledCircle(x, y, r + 3, CHSV( r * 20 + randCol, 255, 255-r*20));
////    leds.DrawFilledCircle(x, y, r + 2, CHSV( r * 20 + randCol, 255, 255-r*20));
////    leds.DrawFilledCircle(x, y, r + 1, CHSV( r * 20 + randCol, 255, 255-r*20));
////    leds.DrawFilledCircle(x, y , r,    CHSV( r * 20 + randCol, 255, 255-r*20));
//
//
//    //leds.DrawFilledCircle(leds.Width()/2, leds.Height()/2, r,CHSV(0, 0,0));
//    if ( r > 1)
//    {
//      leds.DrawFilledCircle(x, y, r - 2, CHSV( (r+1) * 20 + randCol, 255, 255-(r+1)*20));
//      leds.DrawFilledCircle(x, y, r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));
//      // leds.DrawFilledCircle(leds.Width() / 2, leds.Height() / 2, r-2, CHSV(0, 0, 0));
//
//      if (r == leds.Height() / 2)
//      {
//        leds.DrawFilledCircle(x, y,  r, CHSV( (r+3) * 20 + randCol, 255, 255-(r+3)*20));
//        leds.DrawFilledCircle(x, y,  r - 1, CHSV( (r+2) * 20 + randCol, 255, 255-(r+2)*20));
//        leds.DrawFilledCircle(x, y,  r - 2, CHSV( (r+1)* 20 + randCol, 255, 255-(r+1)*20));
//      }
//    }
//
//
//    FastLED.show();
//    delay(1);
//  }

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
// void rainbowHorizontalStripsLoop(uint8_t loops)
//{
//  uint8_t hue;
//  int16_t x, y, i;
//  uint8_t h;
//
//  for (i = 0; i < loops * 50; i++)
//  {
//    h = hue;
//
//    // ** Fill LED's with horizontal stripes
//    for (y = 0; y < leds.Height(); y++)
//    {
//      leds.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 255));
//      h += 16;
//    }
//
//    hue += 2;
//
//    FastLED.show();
//  }
//}

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
