
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
