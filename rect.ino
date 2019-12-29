void rectPattern()
{
  uint8_t count = 0;
  uint8_t randx;
  uint8_t randy;

  uint8_t repeats = 4;

  FastLED.clear();

  centralRectangle(16, 36, ForestColors_p);
  centralRectangle(24, 24, LavaColors_p);

  count = 0;
  while ((count < repeats * 2) && (!changeRequested))
  {
    count++;
    randx = random(leds.Width());
    randy = random(leds.Height());
    centralRectangle(randx, randy, CloudColors_p);
  }

  count = 0;
  while ((count < repeats) && (!changeRequested))
  {
    count++;
    randx = random(leds.Width());
    randy = random(leds.Height());
    expandingRainbowRectangle(randx, randy);
  }

  FastLED.clear();
}

void expandingRainbowRectangle(uint8_t x, uint8_t y)

{
  uint8_t r = 0;
  uint8_t i = 0;

  randomSeed(analogRead(0));
  uint8_t randomColour = random(0, 255);

  while ((!changeRequested) && (r < (leds.Height() / 2) - 5))
  {
    leds.DrawFilledRectangle(x, y, x + r, y + r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 1, y + r + 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 2, y + r + 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 3, y + r + 3, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledRectangle(x, y, x + r + 4, y + r + 4, CHSV(r * 20 + randomColour, 255, 255 - r * 20));

    if (r > 1)
    {
      leds.DrawFilledRectangle(x - r - 2, y - r - 2, x, y, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
      leds.DrawFilledRectangle(x - r - 1, y - r - 1, x, y, CHSV(r * 20 + randomColour, 255, 255 - r * 20));

      if (r == leds.Height() / 2)
      {

        leds.DrawFilledRectangle(x, y, x - r, y - r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledRectangle(x, y, x - r - 1, y - r - 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
        leds.DrawFilledRectangle(x, y, x - r - 2, y - r - 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
      }
    }

    r++;
    FastLED.show();
  }
}

void centralRectangle(uint8_t x, uint8_t y, CRGBPalette16 palette)

{
  uint8_t i, p;
  uint8_t r = 0;

  float frac;
  randomSeed(analogRead(0));
  uint8_t randomColour = random(0, 255);

  while ((!changeRequested) && (r < (leds.Height() / 2) - 5))
  {
    frac = (r / float(((leds.Height() / 2) - 5)));

    for (p = 0; p < 9; p++)
    {
      leds.DrawFilledRectangle(x + r, y + r, x + p, y + p, ColorFromPalette(palette, (255 - p) * frac, (255 - p) - frac * 255));
      delay(3);
    }

    if (r > 1)
    {
      for (p = 9; p > 0; p--)
      {
        leds.DrawFilledRectangle(x - p, y - p, x - r, y - r, ColorFromPalette(palette, (255 - p) * frac, (255 - p) - frac * 255));
        delay(3);
      }
    }

    if (r == leds.Height() / 2)
    {
      for (p = 0; p < 9; p++)
      {
        leds.DrawFilledRectangle(x - r - p, y - r - p, x + r - p, y + r - p, ColorFromPalette(palette, (255 - p) * frac, (255 - p) - frac * 255));
        delay(3);
      }
    }

    r++;

    FastLED.show();
    delay(1);
  }
}
