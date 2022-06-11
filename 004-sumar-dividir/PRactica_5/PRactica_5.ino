#include <ArduinoJson.h>

/*
  Nombre: JSON
  Fecha: 21/06/21
  Autor: Joshua Komaba
  Descripción: En esta práctica se verán librerías de arduino JSON
  Dispositivo: Arduino UNO
*/

// Declaración de constantes
// Contiene el led que se va a encender
const int LED = 13;
StaticJsonDocument<200> json;
// DynamicJsonDocument<1024>;
// Fin de declaración

// Declaración de variables
volatile bool encender = false;
volatile long tiempoDeUltimaPulsacion = 0;
// Fin declaración variables

void setup() {
  Serial.begin(9600);
  // la interrupción cero corresponde al pin número 2 de Arduino UNO
  attachInterrupt(0, interrupcion, RISING);
  pinMode(LED, OUTPUT);
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
  Serial.println("Hola desde arduino");
}

void serialEvent() {
  // Se manda {"numero1": 5, "numero2": 5, "operacion": "+"}
  if(Serial.available() > 0) {

    String lectura = Serial.readString();

    DeserializationError error = deserializeJson(json, lectura);
    
    // char lectura = Serial.read();
    // String lectura = Serial.readString();

    if (error) {
      Serial.println("El JSON está incorrecto");
      return;
    }

    if (!json.containsKey("numero1")) {
      Serial.println("El JSON no contiene el elemento numero1");
      return;
    }

    if (!json.containsKey("numero2")) {
      Serial.println("El JSON no contiene el elemento numero2");
      return;
    }

    if (!json.containsKey("operacion")) {
      Serial.println("El JSON no contiene el elemento operacion");
      return;
    }

    if (json["operacion"] != "+" and json["operacion"] != "-" and json["operacion"] != "*") {
      Serial.println("La operación no es válida");
      return;
    }

    int numero1 = json["numero1"];
    int numero2 = json["numero2"];
    String operacion = json["operacion"];

    Serial.println(numero1);
    Serial.println(numero2);
    Serial.println(operacion);

    if (operacion == "+") {
      int suma = numero1 + numero2;
      
      String impresionJson;

      json["resultado"] = suma;

      serializeJson(json, impresionJson);
      Serial.println(impresionJson);
      
    } else if (operacion == "-") {
      int resta = numero1 - numero2;
      
      String impresionJson;

      json["resultado"] = resta;

      serializeJson(json, impresionJson);
      Serial.println(impresionJson);
    } else if (operacion == "*") {
      int multiplicacion = numero1 * numero2;
      
      String impresionJson;

      json["resultado"] = multiplicacion;

      serializeJson(json, impresionJson);
      Serial.println(impresionJson);
    }
  }
}
