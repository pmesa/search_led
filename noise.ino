
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
