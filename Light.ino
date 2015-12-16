#include <NeoPixelBus.h>

NeoPixelBus strip = NeoPixelBus(4, 1);
NeoPixelAnimator anim = NeoPixelAnimator(&strip);
#define colorSaturation 255
RgbColor red =    RgbColor(255, 0, 0);
RgbColor pink =   RgbColor(255, 0, 128);
RgbColor lila =   RgbColor(255, 0, 255);
RgbColor violet = RgbColor(128, 0, 255);
RgbColor blue =   RgbColor(0, 0, 255);
RgbColor mblue =  RgbColor(0, 128, 255);
RgbColor cyan =   RgbColor(0, 255, 255);
RgbColor green =  RgbColor(0, 255, 0);
RgbColor yellow = RgbColor(255, 255, 0);
RgbColor orange = RgbColor(255, 100, 0);
RgbColor white = RgbColor(colorSaturation);
RgbColor black = RgbColor(0);

void handleAnimation() {
  while (anim.IsAnimating())  {
    anim.UpdateAnimations();
    strip.Show();
    delay(31); // ~30hz change cycle
  }
}

void initLight() {
  strip.Begin();
}

void processCommand(String color) {
  color.trim();
  Serial << "Received Command: " << color << endl;
  RgbColor c = yellow;
  if (color == "red") c = red;
  else if (color == "blue") c = blue;
  else if (color == "green") c = green;
  else if (color == "yellow") c = yellow;
  else if (color == "orange") c = orange;
  else if (color == "white") c = white;
  else if (color == "black") c = black;
  else if (color == "pink") c = pink;
  else if (color == "lila") c = lila;
  else if (color == "violet") c = violet;
  else if (color == "mblue") c = mblue;
  else if (color == "cyan") c = cyan;

  anim.FadeTo(1000, c);
//  for (int i=0; i<4; i++) strip.SetPixelColor(i, c);
//  strip.Show();    
}


