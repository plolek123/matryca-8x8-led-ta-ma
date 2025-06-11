#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Konfiguracja wyświetlacza
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 9
#define CS_PIN 10

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Bitmapa – smiley (8x8)
uint8_t smiley[8] = 
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

// Wyświetlanie bitmapy (na całym wyświetlaczu)
void showBitmap(uint8_t *bitmap) 
{
  display.displayClear();
  for (uint8_t col = 0; col < 8; col++) {
    for (uint8_t row = 0; row < 8; row++) {
      bool pixel = bitRead(bitmap[row], 7 - col);
      for (uint8_t mod = 0; mod < MAX_DEVICES; mod++) {
        display.setPixel(mod * 8 + col, row, pixel);
      }
    }
  }
  delay(1500);
}

// Funkcja animująca tekst (blokująca)
void showText(const char* text, textPosition_t align = PA_CENTER, uint16_t speed = 100, uint16_t pause = 1000, textEffect_t inEffect = PA_SCROLL_DOWN, textEffect_t outEffect = PA_SCROLL_UP) {
  display.displayText(text, align, speed, pause, inEffect, outEffect);
  while (!display.displayAnimate()) {
    // Czekaj aż animacja się zakończy
  }
}

void setup() 
{
  display.begin();
  display.setIntensity(5);  // Jasność 0-15
  display.displayClear();
  display.setTextAlignment(PA_CENTER);
}

void loop() 
{
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
