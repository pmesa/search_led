
int dropLength = 5;
int defaultSpeed = 500;
int lightningSpeed = 100;

void simpleRainPattern( )
{
  initialiseRain();
  while (!changeRequested)
  {
    if ((PIR1triggered) || (PIR2triggered))
    {
      if (PIR1triggered) {
        lightning (true);
      }
      else {
        lightning (false);
      }
      clearPIRs();
    }
    updateRaindrops(defaultSpeed);
  }
}


typedef struct
{
  bool isOn;
  int velocity;
  int yPos;
  int xPos;
  int hue;

} rainSprite;

rainSprite raindrop[14];

void initialiseRain()
{

  for ( int i = 0 ; i < 14; i++)
  {
    raindrop[i].isOn = random(0, 1);
    raindrop[i].velocity = random(1, 5);
    raindrop[i].yPos = leds.Height();
    raindrop[i].xPos = random(leds.Width() / 2);
    raindrop[i].hue = 127;
  }

}

void updateRaindrops(int rainSpeed)
{
  //draw the drops
  for ( int i = 0 ; i < 14; i++)
  {
    if (raindrop[i].isOn)
    {
      leds.DrawLine(raindrop[i].xPos * 2, raindrop[i].yPos, raindrop[i].xPos * 2 , raindrop[i].yPos - dropLength, CHSV(raindrop[i].hue, 255, 255));
      leds.DrawLine(raindrop[i].xPos * 2 + 1, raindrop[i].yPos, raindrop[i].xPos * 2 + 1 , raindrop[i].yPos - dropLength, CHSV(raindrop[i].hue, 255, 255));
    }
  }

  FastLED.show();
  delay(rainSpeed);
  FastLED.clear();

  //update the postions
  for ( int i = 0 ; i < 14; i++)
  {
    if (raindrop[i].isOn)
    {
      if (raindrop[i].yPos <= 0)
      {
        raindrop[i].isOn = false;
      }
      else
      {
        raindrop[i].yPos -= 1 ; //TODO this potentially writes to a negative line position
      }
    }
  }

  //check if the values are all false and need to get more rain!
  bool rainOn = false;
  for ( int i = 0 ; i < 14; i++) {
    rainOn |= raindrop[i].isOn;
  }

  if (rainOn) {
    initialiseRain();
  }

}

void lightning (boolean startsFromTheRight)
{
  if (startsFromTheRight)
  {
    leds.DrawLine(0, 0, leds.Width() / 3, leds.Height(), CRGB(255, 255, 255));
    FastLED.show();
    delay(lightningSpeed);

    leds.DrawLine(leds.Width() / 3, leds.Height(), leds.Width() / 3 * 2, 0, CRGB(255, 255, 255));
    FastLED.show();
    delay(lightningSpeed);

    leds.DrawLine(leds.Width() / 3 * 2, 0, leds.Width(), leds.Height(), CRGB(255, 255, 255));
    FastLED.show();
    delay(lightningSpeed);
  }
  else
  {
    leds.DrawLine(leds.Width() / 3 * 2, 0, leds.Width(), leds.Height(), CRGB(255, 255, 255));
    FastLED.show();
    delay(lightningSpeed);

    leds.DrawLine(leds.Width() / 3, leds.Height(), leds.Width() / 3 * 2, 0, CRGB(255, 255, 255));
    FastLED.show();
    delay(lightningSpeed);

    leds.DrawLine(0, 0, leds.Width() / 3, leds.Height(), CRGB(255, 255, 255));
    FastLED.show();
    delay(lightningSpeed);
  }
}
