from machine import Pin, Timer
from time import sleep, ticks_ms
from menu import Menu

from machine import Pin, I2C
import ssd1306

# ESP32 Pin assignment 
i2c = I2C(0, scl=Pin(22), sda=Pin(21))

oled_width = 128
oled_height = 64
oled = ssd1306.SSD1306_I2C(oled_width, oled_height, i2c)


led1= Pin(4,Pin.OUT )
led2= Pin(16,Pin.OUT )
led3= Pin(17,Pin.OUT )
boton1=Pin(12,Pin.IN,Pin.PULL_UP)
boton2=Pin(14,Pin.IN,Pin.PULL_UP)
boton3=Pin(27,Pin.IN,Pin.PULL_UP)

one = True
Inicio = 0
last_time = 0
opcion = 0
Hora = 0
Minutos = 0
Segundos = 0
bandera = 0


tim0 = Timer(0)
tim1 = Timer(1)
tim2 = Timer(2)

#tim0.definit()      



def option0():
    global Inicio, Minutos, Segundos, opcion

    if Inicio == 1: 
        tim0.init(period=2000, mode=Timer.PERIODIC, callback=changeLed1)
        opcion = 1
    if Inicio == 2:
        Inicio = 0
        Minutos = 0
        Segundos = 0
        tim0.deinit()

    
def option1():
    global Inicio, Minutos, Segundos, opcion
    if Inicio == 1:
        tim1.init(period=1000, mode=Timer.PERIODIC, callback=changeLed2)
        opcion = 2
    if Inicio == 2:
        Inicio = 0
        Minutos = 0
        Segundos = 0
        tim1.deinit()


def option2():
    global Inicio, opcion
    if Inicio == 1:
        Hora = "WAIT"
        tim2.init(period=5000, mode=Timer.ONE_SHOT, callback=changeLed3)
        opcion = 3
    if Inicio == 2:
        Inicio = 0
        tim2.deinit()



def changeLed1(t):
    global Hora, Minutos, Segundos, Inicio
    led1.value(not led1.value())

    Segundos += 1
    if Segundos == 60:
        Minutos += 1
        Segundos = 0
    if Minutos == 60:
        Minutos == 0
        Segundos = 0

    if Segundos < 10 & Minutos < 9:
        Hora = "0" + str (Minutos) + ":" + "0" + str (Segundos)
    elif Segundos >= 10 & Minutos < 9:
        Hora = "0" + str (Minutos) + ":" + str (Segundos)
    else:
        Hora = str (Minutos) + ":" + str (Segundos)
    
def changeLed2(t):
    global Hora, Minutos, Segundos, Inicio
    led2.value(not led2.value())

    Segundos += 1
    if Segundos == 60:
        Minutos += 1
        Segundos = 0
    if Minutos == 60:
        Minutos == 0
        Segundos = 0

    if Segundos < 10 & Minutos < 9:
        Hora = "0" + str (Minutos) + ":" + "0" + str (Segundos)
    elif Segundos >= 10 & Minutos < 9:
        Hora = "0" + str (Minutos) + ":" + str (Segundos)
    else:
        Hora = str (Minutos) + ":" + str (Segundos)

def changeLed3(t):
    global Hora, Segundos, bandera
    Segundos = 0
    bandera = 1
    led3.value(not led3.value())
    Hora = "ONE.SHOT"
    


menu = Menu(oled.print)

menu.addItem("Option 0",option0)
menu.addItem("Option 1",option1)
menu.addItem("Option 2",option2)

def upp(pin):
    global last_time, Inicio
    if ticks_ms() - last_time > 500:
        if Inicio == 0:
            limpiar_pantalla()
            menu.up()
        last_time = ticks_ms()
        
def downn(pin):
    global last_time, Inicio
    if ticks_ms() - last_time > 500:
        if Inicio == 0:
            limpiar_pantalla()
            menu.down()
        last_time = ticks_ms()
        #limpiar_pantalla()

def enterr(pin):
    global last_time, Inicio
    if ticks_ms() - last_time > 500:
        Inicio += 1
        menu.enter()        
        last_time = ticks_ms()
        

def limpiar_pantalla():
  oled.fill(0)  # Llena la pantalla de negro 
  oled.show()   # Actualiza la pantalla
        

boton1.irq(upp, Pin.IRQ_FALLING)

boton2.irq(downn, Pin.IRQ_FALLING)

boton3.irq(enterr, Pin.IRQ_FALLING)

while True:
    #print(ticks_ms())

    if one == True:
        oled.text("WELCOME..", 10, 10)
        oled.text("ROJO: ENTER", 0, 25)
        oled.text("AMARILLO: SUBIR", 0, 35)
        oled.text("VERDE: ABAJO", 0, 45)
        one = False

    if opcion == 1:
        limpiar_pantalla()
        oled.text("2 segundos", 10, 10)
        opcion = 0
    elif opcion == 2:
        limpiar_pantalla()
        oled.text("1 segundo", 10, 10)
        opcion = 0
    elif opcion == 3:
        limpiar_pantalla()
        oled.text("WAIT.....5 s", 10, 10)
        opcion = 0

    if Segundos != bandera:
        limpiar_pantalla()
        oled.text(str(Hora), 10, 50)       
        bandera = Segundos
    oled.show()
    sleep(1)
