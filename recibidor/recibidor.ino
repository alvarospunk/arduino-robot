#include <Wire.h>
#include <VirtualWire.h>

//radiofrecuencia
#define rxPin 13

byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;
size_t n = 0; //cantidad de datos recibida


void setup() {
  Serial.begin(9600);

  //i2c
  Wire.begin();

  //radiofrecuencia
  vw_set_rx_pin(rxPin); //recibiremos por el puerto 13
  vw_setup(2000); //instanciamos una comunicación de 2000bps
  vw_rx_start();
}


void loop() {


  if ((n = vw_get_message(message, &messageLength)))
  {
    Serial.println(n);
    Serial.println(message[0]);

    Wire.beginTransmission(8); // transmitimos al esclavo etiquetado como número 8
    Wire.write(message, n);
    Wire.endTransmission(); //cerramos la conexión
  }


}
