#include <LiquidCrystal.h>
//#include <SoftawareSerial.h>
//LED
#define PIN_LED 2
//PANTALLA
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Motor: direction of rotation
#define FORWARD 0
#define BACKWARD 1
// Motor driver interface
#define MOTOR_DRIVER_IN_1 6
#define MOTOR_DRIVER_IN_2 9
#define MOTOR_DRIVER_IN_3 10
#define MOTOR_DRIVER_IN_4 7
#define MOTOR_DRIVER_ENABLE1 8
#define MOTOR_DRIVER_ENABLE2 13
//Bluetooth
#define PIN_RX 0
#define PIN_TX 1
//SoftwareSerial blue(PIN_TX, PIN_RX);
//Variables
char letra;
float motorVelocity;
bool motor_rotation;
int targetVelocity = 120;
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
  lcd.begin(16, 2);

  //Inicialització
  digitalWrite(MOTOR_DRIVER_IN_1, LOW);
  digitalWrite(MOTOR_DRIVER_IN_2, LOW);
  digitalWrite(MOTOR_DRIVER_IN_3, LOW);
  digitalWrite(MOTOR_DRIVER_IN_4, LOW);
  analogWrite(MOTOR_DRIVER_ENABLE1, 0);
  analogWrite(MOTOR_DRIVER_ENABLE2, 0);


  motor_rotation = FORWARD;
  motorVelocity = 120;
  letra = 'z';
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(motorVelocity - 120);
  if (Serial.available() > 0) {
    letra = Serial.read();
  }
  switch (letra) {
    case 'w':  // Avanzar
      if (motorVelocity < 255) {
        motorVelocity += 10;
      }
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Avanza");
      analogWrite(MOTOR_DRIVER_ENABLE1, (motorVelocity / 3));  // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, (motorVelocity / 3));
      digitalWrite(MOTOR_DRIVER_IN_1, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_2, LOW);
      digitalWrite(MOTOR_DRIVER_IN_3, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_4, LOW);
      break;
    case 's':  // Retroceder
      if (motorVelocity > 14) {
        motorVelocity -= 15;
      } else {
        motorVelocity = 0;
      }
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Retrocede");
      analogWrite(MOTOR_DRIVER_ENABLE1, (motorVelocity / 3));  // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, (motorVelocity / 3));
      digitalWrite(MOTOR_DRIVER_IN_1, LOW);
      digitalWrite(MOTOR_DRIVER_IN_2, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_3, LOW);
      digitalWrite(MOTOR_DRIVER_IN_4, HIGH);
      break;
    case 'a':  // Girar a la izquierda
      if (motorVelocity < 255) {
        motorVelocity += 10;
      }
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Izquierda");
      analogWrite(MOTOR_DRIVER_ENABLE1, (motorVelocity / 3));  // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, (motorVelocity / 3));
      digitalWrite(MOTOR_DRIVER_IN_1, LOW);
      digitalWrite(MOTOR_DRIVER_IN_2, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_3, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_4, LOW);
      break;
    case 'd':  // Girar a la derecha
      if (motorVelocity < 255) {
        motorVelocity += 10;
      }
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Derecha");
      analogWrite(MOTOR_DRIVER_ENABLE1, (motorVelocity / 3));  // Velocidad máxima
      analogWrite(MOTOR_DRIVER_ENABLE2, (motorVelocity / 3));
      digitalWrite(MOTOR_DRIVER_IN_1, HIGH);
      digitalWrite(MOTOR_DRIVER_IN_2, LOW);
      digitalWrite(MOTOR_DRIVER_IN_3, LOW);
      digitalWrite(MOTOR_DRIVER_IN_4, HIGH);
      break;
  }
  letra = 'z';
}