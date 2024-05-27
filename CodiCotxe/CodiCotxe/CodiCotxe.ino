//#include <SoftawareSerial.h>
//LED
#define PIN_LED 2
// Motor: direction of rotation
#define FORWARD 0
#define BACKWARD 1
// Motor driver interface
#define MOTOR_DRIVER_IN_1 6
#define MOTOR_DRIVER_IN_2 9
#define MOTOR_DRIVER_IN_3 11
#define MOTOR_DRIVER_IN_4 10
#define MOTOR_DRIVER_ENABLE1 5
#define MOTOR_DRIVER_ENABLE2 8
//Bluetooth
#define PIN_RX 0
#define PIN_TX 1
//SoftwareSerial blue(PIN_TX, PIN_RX);
//Variables
char letra;
bool motor_rotation;
void setup() {
 pinMode(MOTOR_DRIVER_IN_1, OUTPUT);
 pinMode(MOTOR_DRIVER_IN_2, OUTPUT);
 pinMode(MOTOR_DRIVER_IN_3, OUTPUT);
 pinMode(MOTOR_DRIVER_IN_4, OUTPUT);
 pinMode(MOTOR_DRIVER_ENABLE1, OUTPUT);
 pinMode(MOTOR_DRIVER_ENABLE2, OUTPUT);
 pinMode(PIN_RX, INPUT);
 pinMode(PIN_TX, OUTPUT);

 //blue.begin(9600);
 Serial.begin(9600);

 //Inicialització
 digitalWrite (MOTOR_DRIVER_IN_1, LOW);
 digitalWrite (MOTOR_DRIVER_IN_2, LOW);
 digitalWrite (MOTOR_DRIVER_IN_3, LOW);
 digitalWrite (MOTOR_DRIVER_IN_4, LOW);
 analogWrite (MOTOR_DRIVER_ENABLE1, 0);
 analogWrite (MOTOR_DRIVER_ENABLE2, 0);


 motor_rotation = FORWARD;
}

void loop() {
    if(Serial.available()>0){
      letra = Serial.read();
    }
    switch (letra) {
    case 'w': // Avanzar
      Serial.println("Avanza");
      analogWrite(MOTOR_DRIVER_ENABLE1, 255); // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, 255);
      digitalWrite(MOTOR_DRIVER_IN_1, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_2, LOW);
      digitalWrite(MOTOR_DRIVER_IN_3, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_4, LOW);
      break;
    case 's': // Retroceder
      Serial.println("Retrocede");
      analogWrite(MOTOR_DRIVER_ENABLE1, 255); // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, 255);
      digitalWrite(MOTOR_DRIVER_IN_1, LOW);
      digitalWrite(MOTOR_DRIVER_IN_2, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_3, LOW);
      digitalWrite(MOTOR_DRIVER_IN_4, HIGH);
      break;
    case 'a': // Girar a la izquierda
      Serial.println("Izquierda");
      analogWrite(MOTOR_DRIVER_ENABLE1, 255); // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, 255);
      digitalWrite(MOTOR_DRIVER_IN_1, LOW);
      digitalWrite(MOTOR_DRIVER_IN_2, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_3, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_4, LOW);
      break;
    case 'd': // Girar a la derecha
      Serial.println("Derecha");
      analogWrite(MOTOR_DRIVER_ENABLE1, 255); // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, 255);
      digitalWrite(MOTOR_DRIVER_IN_1, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_2, LOW);
      digitalWrite(MOTOR_DRIVER_IN_3, LOW);
      digitalWrite(MOTOR_DRIVER_IN_4, HIGH);
      break;
    default:
      // Detener los motores si se recibe una letra no reconocida
      digitalWrite(MOTOR_DRIVER_IN_1, LOW);
      digitalWrite(MOTOR_DRIVER_IN_2, LOW);
      digitalWrite(MOTOR_DRIVER_IN_3, LOW);
      digitalWrite(MOTOR_DRIVER_IN_4, LOW);
      analogWrite(MOTOR_DRIVER_ENABLE1, 0);
      analogWrite(MOTOR_DRIVER_ENABLE2, 0);
      break;
  }
}