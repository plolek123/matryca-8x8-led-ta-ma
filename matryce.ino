#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 9
#define CS_PIN 10

// Obiekty Parola i MAX72XX
MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Bitmapy
uint8_t smiley[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};



// Pokazuje bitmapę na wszystkich 9 modułach
void showBitmap(uint8_t *bitmap) {
  display.displayClear();
  matrix.begin();  // inicjalizacja
  for (uint8_t mod = 0; mod < MAX_DEVICES; mod++) {
    for (uint8_t row = 0; row < 8; row++) {
      matrix.setRow(mod, row, bitmap[row]);
    }
  }
  delay(1500);
}

void showText(const char* text, textPosition_t align = PA_CENTER, uint16_t speed = 100, uint16_t pause = 1000, textEffect_t inEffect = PA_SCROLL_DOWN, textEffect_t outEffect = PA_SCROLL_UP) {
  display.displayReset();
  display.displayClear();
  display.displayText(text, align, speed, pause, inEffect, outEffect);
  while (!display.displayAnimate()) {
    // animuj tekst dopóki trwa
  }
}



void setup() {
  display.begin();
  matrix.begin();
  display.setIntensity(5);
  display.displayClear();
  display.setTextAlignment(PA_CENTER);
}

void loop() {
  showText("TECHNIKUM", PA_CENTER, 100, 1000, PA_SCROLL_DOWN, PA_SCROLL_UP);

  showText("ENERGETYCZNE", PA_LEFT, 80, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

  showBitmap(smiley);

  showText("ZAWODY:", PA_CENTER, 80, 1500, PA_SCROLL_DOWN, PA_SCROLL_UP);

  showText("TECHNIK ELEKTRONIK", PA_LEFT, 80, 1500, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

  showText("TECHNIK ELEKTRYK", PA_LEFT, 80, 1500, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

  showText("TECHNIK ENERGETYK", PA_LEFT, 80, 1500, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

  showText("TECHNIK AUTOMATYK", PA_LEFT, 80, 1500, PA_SCROLL_LEFT, PA_SCROLL_LEFT);


  showBitmap(smiley);
}






