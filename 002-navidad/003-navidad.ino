/*
  Nombre: Apagador de LED con Interrupciones
  Fecha: 17/06/21
  Autor: Chris Maqruez
  Descripción: En esta práctica se hace un corrimiento de izquierda a derecha
  Dispositivo: Arduino UNO
*/
// Declaración de constantes
const int LEDS[] = {13,12,11,10};
const int NUMERO_LEDS = (sizeof(LEDS)/sizeof(LEDS[0]));
const int NUMERO_DE_OPCIONES = 2;
// Fin declaración de constantes

// Declaración de variables
volatile int posicionActual = 0;
volatile long tiempoDeUltimaPulsacion = 0;
volatile int opcionActual = 1;
// Fin declaración variables

void setup() {
  //Inicializar el puerto serie
  Serial.begin(9600);

  // la interrupción cero corresponde al pin número 2 de Arduino UNO
  attachInterrupt(0, interrupcion, RISING);
  
  for(int i=0; i < NUMERO_LEDS; i++) {
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], LOW);
  }

}
void izquierdaADerecha() {
  // SEGUNDA OPCIÓN
  if(posicionActual <= NUMERO_LEDS -1) {
    digitalWrite(LEDS[posicionActual], HIGH);
    delay(1000);
    digitalWrite(LEDS[posicionActual], LOW);
    posicionActual = 1;
  } else {
    posicionActual = 0;
  }
}

void interrupcion () {

  // filtrado de impulsos
  if (millis() - tiempoDeUltimaPulsacion > 150) {
    opcionActual == 1 ? 2:1;
    tiempoDeUltimaPulsacion = millis();
  }
  Serial.println(opcionActual);

}

void derechaAIzquierda() {
  if(posicionActual <= 0) {
    digitalWrite(LEDS[posicionActual], HIGH);
    delay(1000);
    digitalWrite(LEDS[posicionActual], LOW);
    posicionActual--;
  } else {
    posicionActual = NUMERO_LEDS - 1;
  }
}
void pares() {
  
}

void loop() {
  izquierdaADerecha();

  switch(opcionActual) {
    case 1:
      izquierdaADerecha();
      break;
    case 2:
      derechaAIzquierda();
      break;
     case 3:
      pares();
      break;
     default:
      break;
  }

 /* for(int i=0; <NUMERO_LEDS; i++) {
    digitalWrite(LEDS[i], HIGH)
    delay(1000)
    digitalWrite(LEDS[i], LOW)
  }
*/
  
}
