#include <Wire.h>
#include <VirtualWire.h>

//radiofrecuencia
#define rxPin 13
#define serialBaudsPerSec 9600

byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;
size_t n = 0; //cantidad de datos recibida
int rf_bps = 2000
int slaveToTx = 8


void setup() {
  Serial.begin(serialBaudsPerSec);

  //i2c
  Wire.begin();

  //radiofrecuencia
  vw_set_rx_pin(rxPin);
  vw_setup(rf_bps);
  vw_rx_start();
}


void loop() {


  if ((n = vw_get_message(message, &messageLength)))
  {
    Serial.println(n);
    Serial.println(message[0]);

    Wire.beginTransmission(slaveToTx);
    Wire.write(message, n);
    Wire.endTransmission();
  }


}
