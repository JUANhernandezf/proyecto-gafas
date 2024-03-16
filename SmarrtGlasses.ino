#include "menu.h"
#include "oled.h"

hw_timer_t *timer = NULL; // Puntero igualado a null para inicializarlo
hw_timer_t *timer1 = NULL; // Puntero igualado a null para inicializarlo
hw_timer_t *timer2 = NULL; // Puntero igualado a null para inicializarlo

Oled oled;
Menu menu;

volatile unsigned long lastTime = 0; //Modificador dentro de la interrupción "volatile"
volatile boolean bUp, bDown, bEnter, IniciarHora, IniciarConteo; // Si se debe ejecutar o no esas interrupciones
volatile int bparpadeo, hora, Conteo, segundo;


void setup() {

  Serial.begin(115200);
  oled.begin();
  oled.SizeText(Grande);
  

  menu.begin(oled);

  menu.addItem("Option 0", option0);
  menu.addItem("Option 1", option1);
  menu.addItem("Option 2", option2);

  pinMode(2, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  
  pinMode(14, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  attachInterrupt(14, enter, FALLING);
  attachInterrupt(4, up, FALLING);
  attachInterrupt(12, down, FALLING);

  bUp, bDown, bEnter = false;

  timer = timerBegin(0, 80, true); //Funcion (timer, preescalador) 
  timer1 = timerBegin(1, 80, true); //Funcion (timer, preescalador) 
  timer2 = timerBegin(2, 80, true); //Funcion (timer, preescalador) 

  timerAttachInterrupt(timer, blink, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);

  timerAttachInterrupt(timer1, Tempo, true);
  timerAlarmWrite(timer1, 1000000, true);
  timerAlarmEnable(timer1);

  timerAttachInterrupt(timer2, Hora, true);
  timerAlarmWrite(timer2, 1000000, true);
  timerAlarmEnable(timer2);

  timerStop(timer);
  timerRestart(timer);

  timerStop(timer1);
  timerRestart(timer1);

  timerStop(timer2);
  timerRestart(timer2);


}

void loop() {

    if (IniciarHora)
    {
      oled.Borrar();
      oled.Cursor(10,20);
       oled.print(hora);
      oled.print(":");
      oled.print(segundo);
    }

    if (IniciarConteo)
    {
      oled.Borrar();
      oled.Cursor(10,20);
      oled.print(Conteo);
    }

  if(bparpadeo != 1)
  {
    IniciarHora = false;
    IniciarConteo = false;
    Conteo = 0;
    if(bUp)
    {
      oled.Borrar();
      menu.up();
      bUp = false;
    }

    if(bDown)
    {
      oled.Borrar();
      menu.down();
      bDown = false;
    }
  }else{
    bUp = false;
    bDown = false;
    
  } 

    if(bEnter)
    {
      menu.enter();
      bEnter = false;
    }
      oled.Imprimir();
}

void ARDUINO_ISR_ATTR blink()
  {
    digitalWrite(2, !digitalRead(2));
  }

  void ARDUINO_ISR_ATTR Tempo()
  {
    digitalWrite(16, !digitalRead(16));
    segundo ++;
      if (segundo > 59)
      {
        hora++;
        segundo = 0;
      }
      if (hora > 23)
      {
        hora = 0;
      }
    IniciarHora = true;
    
  }

  void ARDUINO_ISR_ATTR Hora()
  {
    digitalWrite(17, !digitalRead(17));
    Conteo ++;
    IniciarConteo = true;
  }

void ARDUINO_ISR_ATTR enter()
{
  if((millis() - lastTime) > 250){
    bEnter = true;
    lastTime = millis();
  }
}

void ARDUINO_ISR_ATTR up()
{
  if((millis() - lastTime) > 250){
    bUp = true;
    lastTime = millis();
    //oled.Borrar();
  }
}

void ARDUINO_ISR_ATTR down()
{
  if((millis() - lastTime) > 250){
    bDown = true;
    lastTime = millis();
    //oled.Borrar();
  }
}

void option0() 
{

  bparpadeo++;

  if (bparpadeo == 1)
  {
    timerRestart(timer);
    timerStart(timer);
  }
  if (bparpadeo == 2)
  {
    timerStop(timer);
    digitalWrite(2, LOW);
    bparpadeo = 0;
  }

}

void option1() 
{
   bparpadeo++;

  if (bparpadeo == 1)
  {
    timerRestart(timer1);
    timerStart(timer1);
  }
  if (bparpadeo == 2)
  {
    timerStop(timer1);
    digitalWrite(16, LOW);
    bparpadeo = 0;
  }
}

void option2() 
{
   bparpadeo++;

  if (bparpadeo == 1)
  {
    timerRestart(timer2);
    timerStart(timer2);
  }
  if (bparpadeo == 2)
  {
    timerStop(timer2);
    digitalWrite(17, LOW);
    bparpadeo = 0;
  }
}
