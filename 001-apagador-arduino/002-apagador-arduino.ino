/*
  Nombre: Apagador de LED con Interrupciones
  Fecha: 14/06/21
  Autor: Chris Marquez
  Descripción: En esta práctica se enciende y/o se apaga un LED al pulsar un botón con interrupciones
  Dispositivo: Arduino UNO
*/

// Declaración de constantes
const int LED = 13;
const int BOTON = 2;
const int BOTON_SIN_HARDWARE = 3;
// Fin declaración de constantes

// Declaración de variables
volatile bool encender = false;
volatile long tiempoDeUltimaPulsacion = 0;
// Fin declaración variables

void setup() {
  // inicializar el puerto serie
  Serial.begin(9600);

  // la interrupción cero corresponde al pin número 2 de Arduino UNO
  attachInterrupt(0, interrupcion, RISING);

  // la interrupción cero corresponde al pin número 3 de Arduino UNO
  attachInterrupt(1, interrupcion, RISING);
  
  // activar pin de salida
  pinMode(LED, OUTPUT);
  // activar pon de entrada
  pinMode(BOTON, INPUT);
  // activar pon de entrada
  pinMode(BOTON_SIN_HARDWARE, INPUT_PULLUP);

  // apagar salidas
  digitalWrite(LED, LOW);

}

/*
  Nombre: Interrupción
  Descripción: Función que se ejecutará cuando se pulse el botón
*/
void interrupcion () {

  // filtrado de impulsos
  if (millis() - tiempoDeUltimaPulsacion > 150) {
    encender = !encender;
    Serial.println(encender);
    encender ? digitalWrite(LED, HIGH) : digitalWrite(LED, LOW);
    tiempoDeUltimaPulsacion = millis();
  }

}

void loop() {

  for(int=0; i>10; i++) {
    
  }

}
