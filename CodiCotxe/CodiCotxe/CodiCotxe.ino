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
 digitalWrite (MOTOR_DRIVER_IN_1, 0);
 digitalWrite (MOTOR_DRIVER_IN_2, 0);
 digitalWrite (MOTOR_DRIVER_IN_3, 0);
 digitalWrite (MOTOR_DRIVER_IN_4, 0);
 analogWrite (MOTOR_DRIVER_ENABLE1, 0);
 analogWrite (MOTOR_DRIVER_ENABLE2, 0);


 motor_rotation = FORWARD;
}

void loop() {
    if(Serial.available()>0){
      letra = Serial.read();
    }
    switch(letra){
      case 'w':
      Serial.print("Avanza");
        break;
      case 's':
      Serial.print("Retrocede");
        break;
      case 'a':
      Serial.print("Derecha");
        break;
      case 'd':
      Serial.print("Izquierda");
        break;
    }
}
