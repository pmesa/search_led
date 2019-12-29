
int dropLength = 3;
int defaultSpeed = 1;
int lightningSpeed = 100;

typedef struct
{
  bool isOn;
  int velocity;
  int yPos;
  int xPos;
  int hue;

} rainSprite;

rainSprite raindrop[14];

void simpleRainPattern( )
{
  initialiseRain();
  while (!changeRequested)
  {
    updateRaindrops(defaultSpeed);

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

  }
}




void initialiseRain()
{

  for ( int i = 0 ; i < 14; i++)
  {
    raindrop[i].isOn = true;//random(0,255)%2;
    raindrop[i].velocity = random(2, 6);
    raindrop[i].yPos = leds.Height() - 1;
    raindrop[i].xPos = random(leds.Width() / 2);
    raindrop[i].hue = 127;
  }

}

void initialiseRaindrop(int drop)
{
    raindrop[drop].isOn = true;//random(0,255)%2;
    raindrop[drop].velocity = random(1, 5);
    raindrop[drop].yPos = leds.Height() - 1;
    //raindrop[drop].xPos = random(leds.Width() / 2);
    raindrop[drop].hue = 127;
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
        //initialiseRaindrop[i];
      }
      else
      {
        raindrop[i].yPos -= raindrop[i].velocity ; //TODO this potentially writes to a negative line position
      }
    }
  }

  //check if the values are all false and need to get more rain!
  int resetRain = false;
  for ( int i = 0 ; i < 14; i++) {
    resetRain += !(raindrop[i].isOn);
  }

  if (resetRain>12) {
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
