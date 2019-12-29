
void cometPattern()
{
  randomSeed(A0);
  int randomColour = random(0, 255);
  while (!changeRequested)
  {
    verticalLineUp(randomColour, 4);
  }
}

void pingPong()
{
  randomSeed(A0);
  int randomColour = random(0, 255);
  while (!changeRequested)
  {
    verticalLineUp(randomColour, 4);
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
    for (relativePixelRow = thickness; relativePixelRow > 0; relativePixelRow--)
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
