
uint32_t x, y, v_time, hue_time, hxy;
// how many octaves to use for the brightness and hue functions
uint8_t octaves = 54;
uint8_t hue_octaves = 10;
// the 'distance' between points on the x and y axis
int xscale = 57771;
int yscale = 57771;
// the 'distance' between x/y points for the hue noise
int hue_scale = 1;
// how fast we move through time & hue noise
int time_speed = 1111;
int hue_speed = 31;
// adjust these values to move along the x or y axis between frames
int x_speed = 331;
int y_speed = 1111;

void noisePattern()
{

  hxy = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  x = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  y = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  v_time = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();
  hue_time = (uint32_t)((uint32_t)random16() << 16) + (uint32_t)random16();

  fill_2dnoise16(FastLED.leds(), MATRIX_WIDTH, MATRIX_HEIGHT, true,
                 octaves, x, xscale, y, yscale, v_time,
                 hue_octaves, hxy, hue_scale, hxy, hue_scale, hue_time, false);

  FastLED.show();
  if ((PIR1triggered) || (PIR2triggered))
  {
    fastFlash(20, random(255));
    clearPIRs();
  }

  // adjust the intra-frame time values
  x += x_speed;
  y += y_speed;
  v_time += time_speed;
  hue_time += hue_speed;
}

void fastFlash(int wait_ms, int hue)
{
  for (int i = 0; i < 3; i++)
  {
    leds.DrawFilledRectangle(0, 0, leds.Width(), leds.Height(), CHSV(hue, 255, 255));
    FastLED.show();
    delay(wait_ms);
    FastLED.clear();
  }
}
