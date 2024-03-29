#include "../config.hpp"

#ifndef PISO_H
#define PISO_H

// La lectura de cada sensor del piso
extern uint16_t lecturasPiso[N_PISO];

// Setup un sensor del piso
inline void setupPiso(uint8_t n_sensor, uint8_t pin)
{
  pinMode(pin, INPUT);
  lecturasPiso[n_sensor] = 0;
}

// Setup todos los sensores del piso
inline void setupPiso()
{
  for (size_t i = 0; i < N_PISO; i++)
  {
    setupPiso(i, PISO_PINS[i]);
  }
}

// Actualizar cada sensor del piso
void loopPiso();

// Leer el estado de un sensor del piso
inline uint16_t leerPiso(uint8_t n_sensor) {
  return lecturasPiso[n_sensor];
}

#endif