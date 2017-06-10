#include <ArduinoRobot.h>
#include <Wire.h>
#include "motor.h"

//declaraciones ultrasonidos
#define trigPin D4
#define echoPin D3

//modo acústico
byte acustic = 0;
byte automatico = 0 ;
int velocida = 200;
bool mode_derecha;

//variables control del zumbido
long indiceT, referencia = millis();
int periodo = 3000;


void setup() {

  Serial.begin(9600);

  //i2c
  Wire.begin(8);                // nos identificamos en el bus como dispositivo 8
  Wire.onReceive(receiveEvent); // manejador del evento i2c
  Serial.println("I2C inicializada");

  //ultrasonidos
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.println("Ultrasonidos inicializado");

  // initialize the robot
  Robot.begin();
  setVelocidad(velocida);

  // initialize the sound library
  Robot.beginSpeaker();
  Serial.println("Buzzer inicializada");

  Serial.println("Arduino robot inicializado");

}
//int i = 0;
void loop() {
  //Serial.println("xdese");
  //Serial.println(i);
  //i = i + 1;
  velocida = map(Robot.knobRead(), 0, 1023, -255, 255);
  setVelocidad(velocida);
  //si acustic está activado, cambia la frecuencia del zumbido según la distancia
  if (acustic) {
    ajustaPeriodo(); //solo haremos mediciones si queremos escuchar el zumbido
    indiceT = millis();
    if (indiceT - referencia > periodo) {
      Robot.beep(BEEP_SIMPLE);
      referencia = millis();
    }
  }
  if (automatico) {
    automatic();
  }


  delay(50);
}

void automatic() {
  //setVelocidad(velocida);
  float distancia = distanciaCM();
  while (distancia < 20) {
    setVelocidad(100);
    if (mode_derecha) {
      setMovimient('d');
    }
    else {
      setMovimient('i');
    }
    delay(200);
    distancia = distanciaCM();
  }
  setMovimient('a');
  setVelocidad(velocida);
}





void receiveEvent(int howMany) {

  while (Wire.available()) { // mientras hay bytes que recibir por I2C...

    char opcion = char( Wire.read()); // recibe el primer y tal vez último byte y lo transforma a char
    Serial.println(opcion);

    switch (opcion) {
      case 'A'://se activa o desactiva modo sonoro
        acustic = 1 - acustic;
        if (acustic)
          Serial.println("Se activa modo acustico");
        else
          Serial.println("Se desactiva modo acustico");
        break;
      case '2': //delante
        setMovimient('a');
        break;
      case '8': //atrás
        setMovimient('f');
        break;
      case '4': //izquierda
        setMovimient('i');
        break;
      case '6': //derecha
        setMovimient('d');
        break;
      case '5': //parar
        setMovimient('p');
        break;
      case '1': //arriba izquierda
        setMovimient('1');
        break;
      case '3': //arriba derecha
        setMovimient('3');
        break;
      case '7': //abajo izquierda
        setMovimient('7');
        break;
      case '9': //abajo derecha
        setMovimient('9');
        break;
      case 'B':
        automatico = 1 - automatico;
        if (automatico)
          Serial.println("Se activa modo automatico");
        else {
          setMovimient('p');
          Serial.println("Se desactiva modo automatico");
        }
        break;
      case 'C':
        //tecla sin cubrir
        break;
      case 'D':
        //tecla sin cubrir
        break;
      case '*':
        mode_derecha = false;
        break;
      case '0':
        //tecla sin cubrir
        break;
      case '#':
        mode_derecha = true;
        break;
    }
  }
}


//devuelve la distancia en CM al próximo obstáculo
//(tal vez se pueda encontrar una configuración por ahí que de mejores resultados para esta función)
int distanciaCM() {

  long duration;
  int distance;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //-Serial.print("Distance: ");
  //-Serial.println(distance);
  return distance;

}

//ajusta el periodo o la frecuencia del zumbido en función a la distancia
//a menos de 10cm, un zumbido cada 1/10 segundo. A partir de 100cm, un zumbido cada 3 segundos
void ajustaPeriodo() {
  int dist = distanciaCM();
  if (dist > 100) dist = 100;
  else if (dist < 10) dist = 10;
  periodo = map(dist, 10, 100, 100, 3000);
  //-Serial.print("Periodo: ");
  //-Serial.println(periodo);
}

