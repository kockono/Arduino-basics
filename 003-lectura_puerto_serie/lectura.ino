// Declaración de constantes
const int LED = 13;
const int BOTON = 2;
const int BOTON_SIN_HARDWARE = 3;
// Fin declaración de constantes

// Declaración de variables
volatile bool encender = false;
volatile long tiempoDeUltimaPulsacion = 0;
// Fin declaración variables

void setup () {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

}

void loop(){

}

void serialEvent() {
    if(Serial.available()>0) {
        
    }

    char lectura = Serial.read();
    Serial.println(lectura);
}