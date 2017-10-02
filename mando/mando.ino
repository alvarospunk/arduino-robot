#include <VirtualWire.h>
#include <Keypad.h>


//Radio frecuencia
#define radioPin 12
char buffer[2];

//Definiciones para el teclado
const byte fil = 4;
const byte col = 4;
char mapaTeclas[fil][col] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte filPins[fil] = {9, 8, 7, 6};
byte colPins[col] = {5, 4, 3, 2};
Keypad teclado = Keypad(makeKeymap(mapaTeclas), filPins, colPins, fil, col);



void setup()
{
  Serial.begin(9600);

  //radio
  vw_set_tx_pin(radioPin);
  vw_setup(2000);  
}

void loop() {


  buffer[0] = teclado.getKey();
  if (buffer[0] != NO_KEY)
  {
    Serial.println(buffer[0]);
    vw_send((uint8_t *)buffer, strlen(buffer));
    //vw_wait_tx();
  }

}

