#include "../../config.hpp"

#if ESTRATEGIA == STRAT_EMPUJE

#include "../estrategia.hpp"

#include "../../motores/motores.hpp"

#include "strat.hpp"

enum Estado
{
  BuscandoL = 0,
  BuscandoR,
  Empujando,
  EvitandoCaerse
} estado;

unsigned long ultimoCambio = millis();

void cambiarEstado(Estado nuevoEstado)
{
  estado = nuevoEstado;
  ultimoCambio = millis();
}

// Buscar y matar setup
void setupEstrategia()
{
  // Elegir aleatoriamente entre Buscando L y R
  cambiarEstado((Estado)(rand() % 2));
}

inline unsigned long tiempoPasado(unsigned long tiempo)
{
  return tiempo - ultimoCambio;
}

// Buscar y matar loop
void loopEstrategia(uint16_t distanciaIzquierda, uint16_t distanciaAdelante, uint16_t distanciaDerecha, uint16_t lecturaPisoL, uint16_t lecturaPisoR)
{
  dprintln("STRAT DE BUSCAR Y MATAR >:(");

  unsigned long tiempo = millis();

  if (lecturaPisoL < 500 || lecturaPisoR < 500)
  {
    cambiarEstado(Estado::EvitandoCaerse);
  }
  else if (distanciaAdelante < 60 &&  distanciaAdelante != 0)
  {
    cambiarEstado(Estado::Empujando);
  }

  switch (estado)
  {
  case EvitandoCaerse:
    actualizarMotores(Direccion::Atras, 255);
    if (tiempoPasado(tiempo) > 150)
    {
      cambiarEstado((Estado)(rand() % 2));
    }
    break;
  case Empujando:
    actualizarMotores(Direccion::Adelante, 255);
    if ((distanciaAdelante > 60 || distanciaAdelante == 0) && tiempoPasado(tiempo) > 200)
    {
      cambiarEstado((Estado)(rand() % 2));
    }
    break;  
  case BuscandoL:
    actualizarMotores(Direccion::Izquierda, 135);
    break;
  case BuscandoR:
    actualizarMotores(Direccion::Derecha, 135);
    break;
  }
}

#endif
