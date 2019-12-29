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
   
   FastLED.clear();

   // Blue Pillars
   // leds.DrawLine(x1, y1, x2, y2, CHSV(H, S, V))
   // Light Blue #1C8EFF HSV(210, 89, 100) CHSV(149, 227, 255)

//   leds.DrawLine(0, 0, 3, leds.Height() - 1, CHSV(0, 0, 0));
//   leds.DrawLine(leds.Width - 4, 0, leds.Width - 1, leds.Height() - 1, CHSV(0, 0, 0));



  // Countdown

  int count_s;

  for (count_s = 0; count_s < 10; count_s++) 
  {
    leds.DrawLine(4, 0, (count_s * 2 + 5), leds.Height() - 1, CHSV(149, 227, 255));
    FastLED.show();
    delay(1000);
  }

  delay(500);

  FastLED.clear();

  delay(500);

  // Celebration

  rainbowNoiseNYE(20, 500, 5000);
  
  
}
  
void rainbowNoiseNYE(uint8_t loops, int delay_time_ms, int fade_time_ms)
{
  uint16_t x, y;

  uint16_t i = 0;
  
  int colours[MATRIX_WIDTH][MATRIX_HEIGHT];
  int saturations[MATRIX_WIDTH][MATRIX_HEIGHT];
  
  while (i <= loops)
  {
    for (x = 0; x < leds.Width(); x++)
    {
      for (y = 0; y < leds.Height(); y++)
      {
        colours[x][y] = random(255);
        saturations[x][y] = 127 + random(127);
        leds.DrawPixel(x, y, CHSV(colours[x][y], saturations[x][y], 255));
      }
    }
    FastLED.show();

    if (loops != 0)
    {
      i++;
    }

    delay(delay_time_ms);

    FastLED.clear();

    delay(delay_time_ms);
  }

  // Fade

  int bright;

  for (bright = 255; bright > 0; bright--)
  {
      for (x = 0; x < leds.Width(); x++)
      {
        for (y = 0; y < leds.Height(); y++)
        {
          leds.DrawPixel(x, y, CHSV(colours[x][y], saturations[x][y], bright));
        }
      }
      
      FastLED.show();
  
      delay(fade_time_ms/255);
    }

    delay(delay_time_ms);
}
