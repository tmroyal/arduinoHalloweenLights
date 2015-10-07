#include <Adafruit_NeoPixel.h>

#define PIN 6
#define N_PIXELS 30

#define LIGHTNING "L"
#define MAGIC_ON "M"
#define MAGIC_OFF "m"
#define GHOST_ON "G"
#define GHOST_OFF "g"
#define EYE_ON "E"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint8_t colors[N_PIXELS];
float brightnesses[N_PIXELS];

void setup() {
  setupColors();
  strip.begin();
  strip.setBrightness(64);
  strip.show();

  Serial.begin(57600);
}

void setupColors(){
  for (uint8_t i = 0; i < strip.numPixels(); i++){
    colors[i] = i % 2;
    brightnesses[i] = 0;
  }
}

void loop() {
  uint8_t choice = random(4);
  
  background();

  switch (random(4)){
    case 0:
      lightningStorm();
      
      break;
    case 1:
      spookyGhost();
      break;
    case 2:
      scaryEye();
      break;
    case 3:
      magicPotions();
      break;
  }

}

void background(){
  uint16_t its = random(50,100);
  uint8_t r, b, g;
  float stp;
  
  setStrip(strip.Color(0,0,0));
  setupColors();

  for (uint16_t i = 0; i < its; i++){
    for (uint8_t j = 0; j < strip.numPixels(); j++){
      if (j % 2 == 0 || random(3)== 0){
        if (random(3) == 0){
          stp = 0.15; 
        } else {
          stp = 0.05;
        }
        if (random(2) == 0){
          brightnesses[j] -= stp;
        } else {
          brightnesses[j] += stp;
        }
        if (brightnesses[j] < 0) { brightnesses[j] = 0; }
        if (brightnesses[j] > 1) { brightnesses[j] = 1; }
      }
      
      
      // set color
      if (colors[j] == 0){
        strip.setPixelColor(j, strip.Color(255.0*brightnesses[j], 132.0*brightnesses[j],0));
      } else {
        strip.setPixelColor(j, strip.Color(192.0*brightnesses[j], 0, 255.0*brightnesses[j]));
      }
    }
    strip.show();
    delay(100);
  }
  setStrip(strip.Color(0,0,0));

}

void spookyGhost(){
  uint8_t pos = 0;
  uint16_t white = strip.Color(200, 200, 255);
  uint16_t black = strip.Color(0, 0, 0);
  Serial.print(GHOST_ON);
  while (pos < strip.numPixels()){
    // move randomly towards other side  
    if (pos == 0){
      pos += 1;
    } else {
      if (random(3) == 0){
        pos -= 1;
      } else {
        pos += 1;
      }
    }
    
    for (int i = pos; i < pos+4 && i < strip.numPixels(); i++){
      strip.setPixelColor(i, white);
    }
    strip.show();
    delay(100);
    for (int i = pos; i < pos+4 && i < strip.numPixels(); i++){
      strip.setPixelColor(i, black);
    }  
  }
  Serial.print(GHOST_OFF);
}

void setStrip(uint32_t color){
  for (uint8_t i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, color);
    strip.show();
  }
}

void lightningStorm(){
  uint8_t nStrikes = random(6,10);
  for (uint8_t i = 0; i < nStrikes; i++){
    lightningStrike();
    delay(random(500));
  }
}

void lightningStrike(){
  uint8_t nFlashes = random(1,5);
  uint8_t period = random(10,100);
  uint8_t inter = random(10,50);
  Serial.print(LIGHTNING);
  for (uint8_t i = 0; i < nFlashes; i++){
    setStrip(strip.Color(64,64,168));
    delay(inter);
    setStrip(strip.Color(0,0,0));
    delay(period);
  }
}


void scaryEye(){
  Serial.print(EYE_ON);
  for (uint8_t i = 0; i < strip.numPixels(); i++){
    if (i >= 0){
      strip.setPixelColor(i, strip.Color(255,0,0));
    }
    if (i + 3 < strip.numPixels()){
      strip.setPixelColor(i+3, strip.Color(255,0,0));
    }
    strip.show();
    delay(100);
    setStrip(strip.Color(0,0,0));
  }
  Serial.print(EYE_OFF);
}

void magicPotions(){
  Serial.print(MAGIC_ON);

  uint16_t its = random(1000,3000);
  for (uint16_t i = 0; i < its; i++){
    strip.setPixelColor((uint16_t)random(strip.numPixels()), (uint8_t)random(255),(uint8_t)random(255),(uint8_t)random(255));
    strip.show();
    delay(1);
  }

  Serial.print(MAGIC_OFF);

  setStrip(strip.Color(0,0,0));
}
