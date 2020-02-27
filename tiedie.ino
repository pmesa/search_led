void tiediePatternRandom()
{

  while ((!changeRequested) && (!pirRequested))
  {
    randomSeed(analogRead(0));
    myFirstTieDie(random(leds.Width()), random(leds.Height()));
  }
  if (PIR1triggered)
  {
    clearPIRs();
    rainbowScrollUpPattern();
  }

  if (PIR2triggered)
  {
    clearPIRs();
    rainbowScrollDownPattern();
  }
}

void myFirstTieDie(uint8_t x, uint8_t y)

{
  uint8_t r = 0;
  uint8_t i = 0;

  randomSeed(analogRead(0));
  uint8_t randomColour = random(0, 255);

  while ((!changeRequested) && (!pirRequested) && (r < (leds.Height() / 4)))
  {

    leds.DrawFilledCircle(x, y, r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    delay(4);
    leds.DrawFilledCircle(x, y, r + 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    delay(4);
    leds.DrawFilledCircle(x, y, r + 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    delay(4);
    leds.DrawFilledCircle(x, y, r + 3, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    delay(4);

    if (r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV((r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20));
      delay(4);
      leds.DrawFilledCircle(x, y, r - 1, CHSV((r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20));
      delay(4);

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y, r, CHSV((r + 3) * 20 + randomColour, 255, 255 - (r + 3) * 20));
        delay(4);
        leds.DrawFilledCircle(x, y, r - 1, CHSV((r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20));
        delay(4);
        leds.DrawFilledCircle(x, y, r - 2, CHSV((r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20));
        delay(4);
      }
    }

    r++;
    FastLED.show();
    delay(20);
  }

  r = (leds.Height() / 4) - 5;

  while ((!changeRequested) && (r > 0))
  {
    leds.DrawFilledCircle(x, y, r, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 1, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 2, CHSV(r * 20 + randomColour, 255, 255 - r * 20));
    leds.DrawFilledCircle(x, y, r + 3, CHSV(r * 20 + randomColour, 255, 255 - r * 20));

    if (r > 1)
    {
      leds.DrawFilledCircle(x, y, r - 2, CHSV((r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20));
      leds.DrawFilledCircle(x, y, r - 1, CHSV((r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20));

      if (r == leds.Height() / 2)
      {
        leds.DrawFilledCircle(x, y, r, CHSV((r + 3) * 20 + randomColour, 255, 255 - (r + 3) * 20));
        leds.DrawFilledCircle(x, y, r - 1, CHSV((r + 2) * 20 + randomColour, 255, 255 - (r + 2) * 20));
        leds.DrawFilledCircle(x, y, r - 2, CHSV((r + 1) * 20 + randomColour, 255, 255 - (r + 1) * 20));
      }
    }

    r--;
    FastLED.show();
  }
}

void rainbowScrollUpPattern()
{
  int count = 0;
  FastLED.clear();
  while ((!changeRequested) && (count < leds.Width()))
  {
    leds.DrawLine(count, 0, count, leds.Height(), CHSV(25 * count, 255, 255));
    if (count > 0)
    {
      leds.DrawLine(count - 1, 0, count - 1, leds.Height(), CHSV(0, 0, 0));
    }

    //    if (count == leds.Width() - 1)
    //    {
    //      //leds.DrawLine (count, count ,0, leds.Height(),CHSV(0,0,0));
    //      count = 0;
    //    }
    count++;
    FastLED.show();
    delay(10);
  }

  FastLED.clear();
}

void rainbowScrollDownPattern()
{
  int count = leds.Width() - 1;
  FastLED.clear();
  while ((!changeRequested) && (!pirRequested) && (count >= 0))
  {
    leds.DrawLine(count, 0, count, leds.Height(), CHSV(25 * count, 255, 255));
    if (count < leds.Width() - 1)
    {
      leds.DrawLine(count + 1, 0, count + 1, leds.Height(), CHSV(0, 0, 0));
    }

    //    if (count == 0)
    //    {
    //      //leds.DrawLine (count, count ,0, leds.Height(),CHSV(0,0,0));
    //      count = 0;
    //    }
    count--;
    FastLED.show();
    delay(10);
  }

  FastLED.clear();
}
