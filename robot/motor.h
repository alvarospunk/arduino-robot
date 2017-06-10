#ifndef motor_h
#define motor_h

#if ARDUINO >= 100
#include "Arduino.h"
#endif

int velocidad = 0;

void setVelocidad(int vel) {
  if (vel > 0 && vel < 256) velocidad = vel;
}

void setMovimient(char mov) {
  switch (mov) {
    case 'a': //frente
      Robot.motorsWrite(velocidad, velocidad);
      break;
    case 'f': //atrás
      Robot.motorsWrite(-velocidad, -velocidad);
      break;
    case 'i': //izquierda
      Robot.motorsWrite(-velocidad, velocidad);
      break;
    case 'd': //derecha
      Robot.motorsWrite(velocidad, -velocidad);
      break;
    case 'p': //parar
      Robot.motorsWrite(0, 0);
      Robot.motorsStop();
      break;
    case '1': //arriba izquierda
      Robot.motorsWrite(velocidad / 2, velocidad);
      Robot.motorsStop();
      break;
    case '3': //arriba derecha
      Robot.motorsWrite(velocidad, velocidad / 2);
      Robot.motorsStop();
      break;
    case '7': //abajo izquierda
      Robot.motorsWrite(-velocidad / 2, -velocidad);
      Robot.motorsStop();
      break;
    case '9': //abajo derecha
      Robot.motorsWrite(-velocidad, -velocidad / 2);
      Robot.motorsStop();
      break;
    default:
      break;
  }


};


#endif
