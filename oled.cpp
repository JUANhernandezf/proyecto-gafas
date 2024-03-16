#include "oled.h"

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

 void Oled::begin ()
  {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.display();
    delay(500);
    display.clearDisplay();

  }


  void Oled::Cursor (uint8_t x, uint8_t y)
  {
    display.setCursor(x, y);
  }
      
  void Oled::Imprimir()
  {
      display.setCursor(10,10);
      display.display();
  }
      
  void Oled::Borrar()
  {
    display.clearDisplay();
  }

  void Oled::SizeText(uint8_t size)
  {
    if(size == 1)
    {
      display.setTextSize(1);
    }else if(size == 2)
    {
      display.setTextSize(1.5);
    }else 
    display.setTextSize(2);
  }

  size_t Oled::write(uint8_t c)
  {
    display.display();
    return display.write(c);
  }

  
