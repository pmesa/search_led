void nye(void) 
{
  /*
   *  |      |      |      |      |      |      |      |      |      |      |      |      |      |
   *  |      |      |      |      |      |      |      |      |      |      |      |      |      |
   *  |      |      |      |      |      |      |      |      |      |      |      |      |      |
   *  |      |      |      |      |      |      |      |      |      |      |      |      |      |
   *  |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * 0/1    2/3    4/5    6/7    8/9   10/11  12/13  14/15  16/17  18/19  20/21  22/23  24/25  26/27
   *                                                                                    -4/-3  -2/-1
   */

  // HSV(hue_in_degrees/360 * 255, sat/100 * 255, V/100 * 255)
  // V proportionally changes each RGB channels brightness eg . V(100%) = RGB(100, 255, 200) then V(50%) = (50, 127, 100)
   
//   FastLED.clear();

   // Blue Pillars
   // leds.DrawLine(x1, y1, x2, y2, CHSV(H, S, V))
   // Light Blue #1C8EFF HSV(210, 89, 100) CHSV(149, 227, 255)

//   Countdown

  int count_s;

  for (count_s = 0; count_s < 10; count_s++) 
  {
    leds.DrawLine(2 * count_s + 4, 0, 2 * count_s + 4, leds.Height(), CHSV(149, 227, 255));
    leds.DrawLine(2 * count_s + 5, 0, 2 * count_s + 5, leds.Height(), CHSV(149, 227, 255));
    FastLED.show();
    delay(100);
  }

  delay(500);

  FastLED.clear();

  delay(500);

  expandingGapCircle(leds.Width()/2, leds.Height()/2);

  

//  // Celebration
//
  rainbowNoiseNYE(200, 20, 500);
  
  
}
  
void rainbowNoiseNYE(uint8_t loops, int delay_time_ms, int fade_time_ms)
{
  uint16_t x, y;

  uint16_t i = 0;
  
  int colours[MATRIX_WIDTH][MATRIX_HEIGHT];
  int saturations[MATRIX_WIDTH][MATRIX_HEIGHT];
  int brightnesss[MATRIX_WIDTH][MATRIX_HEIGHT];
  
  while (i <= loops)
  {
    for (x = 0; x < leds.Width(); x++)
    {
      for (y = 0; y < leds.Height(); y++)
      {
        colours[x][y] = random(255);
        saturations[x][y] = 127 + random(127);
        brightnesss[x][y] = random(255);
        leds.DrawLine(x, y, x, y,CHSV(colours[x][y], saturations[x][y], brightnesss[x][y]));
      }
    }
    
    FastLED.show();

    if (loops != 0)
    {
      i++;
    }

    delay(delay_time_ms);
    leds.DrawFilledRectangle(0,0, leds.Width(),leds.Height(), CHSV(0,0,0));

    FastLED.show();

    delay(delay_time_ms);
  }

  // Fade

  int bright;

  for (bright = 100; bright > 0; bright--)
  {
      for (x = 0; x < leds.Width(); x++)
      {
        for (y = 0; y < leds.Height(); y++)
        {
          leds.DrawPixel(x, y, CHSV(colours[x][y], saturations[x][y], brightnesss[x][y] * bright / 100));
        }
      }
      
      FastLED.show();
  
      delay(fade_time_ms/100);
    }

    delay(delay_time_ms);
}


void expandingGapCircle(uint8_t x, uint8_t y)

{
  uint8_t r, i;
  //float frac;

  //  x = leds.Width() / 2;
  //  y = leds.Height() / 2;
  randomSeed(analogRead(0));
  uint8_t randomColour = random(0, 255);

  for (r = 0; r < (leds.Height() / 2) - 5; r++)
  {
    //frac = (r / float(((leds.Height()/2)-5)));

    leds.DrawFilledCircle(x, y, r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    //leds.DrawFilledCircle(x, y, r + 3, ColorFromPalette(palette,252*frac,252-frac*252));

    if (r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
      leds.DrawFilledCircle(x, y, r - 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y, r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledCircle(x, y, r - 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledCircle(x, y, r - 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
      }
    }

    FastLED.show();
  }

  for (r = 0; r < (leds.Height() / 3) - 5; r++)
  {
    leds.DrawFilledCircle(x, y, r, CHSV(0, 0, 0));
    leds.DrawFilledCircle(x, y, r + 1, CHSV(0, 0, 0));
    leds.DrawFilledCircle(x, y, r + 2, CHSV(0, 0, 0));
    leds.DrawFilledCircle(x, y, r + 3, CHSV(0, 0, 0));

    if (r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV(0, 0, 0));
      leds.DrawFilledCircle(x, y, r - 1, CHSV(0, 0, 0));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y, r, CHSV(0, 0, 0));
        leds.DrawFilledCircle(x, y, r - 1, CHSV(0, 0, 0));
        leds.DrawFilledCircle(x, y, r - 2, CHSV(0, 0, 0));
      }
    }

    FastLED.show();
  }
}
