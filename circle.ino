void circlesPattern()
{
  randomSeed(analogRead(0));
  uint8_t randx = random(leds.Width());
  uint8_t randy = random(leds.Height());

  expandingRainbowCircle(randx, randy);
}


void expandingRainbowCircle(uint8_t x, uint8_t y)
{
  uint8_t i;

  randomSeed(analogRead(0));
  uint8_t randomColour = random(0, 255);
  int r = 0;

  while ((!changeRequested) && (r < (leds.Height() / 2) - 5))
  {
    leds.DrawCircle(x, y, r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 3, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawCircle(x, y, r + 4, CHSV(r * 20 + randomColour, 255, 255 - r * 20));

    if (r > 1)
    {
      leds.DrawCircle(x, y, r - 2, CHSV(0, 0, 0));
      leds.DrawCircle(x, y, r - 1, CHSV(0, 0, 0));
      if (r == leds.Height() / 2)
      {
        leds.DrawCircle(x, y, r, CHSV(0, 0, 0));
        leds.DrawCircle(x, y, r - 1, CHSV(0, 0, 0));
        leds.DrawCircle(x, y, r - 2, CHSV(0, 0, 0));
      }
    }
    FastLED.show();
    r++;
  }
}
