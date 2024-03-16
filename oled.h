#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>

#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64 // alto pantalla OLED
#define Peque 1
#define Mediano 2
#define Grande 3

class Oled: public Stream {

  private:

    uint8_t size;
    
  public:

    void Cursor(uint8_t x, uint8_t y);
    void begin();
    void Imprimir();
    void Borrar();
    void SizeText(uint8_t size);
    size_t write(uint8_t c);
    int available() override{}
    int read() override{}
    int peek() override{}
};