//LDRS
#define LIGHT_SIGNAL0 A0
#define LIGHT_SIGNAL1 A1
#define LIGHT_SIGNAL2 A2
#define LIGHT_SIGNAL3 A3
#define LIGHT_SIGNAL4 A4

//Ultrasonic sensor
#define TRIGGER1 6
#define ECHO1 5
#define TRIGGER2 9
#define ECHO2 3

//LEDS D2,D4,D7,D8,D12,D13
#define RED_LED1 2
#define YELLOW_LED1 4
#define GREEN_LED1 7
#define RED_LED2 8
#define YELLOW_LED2 12
#define GREEN_LED2 13

//Configuration parameters
//Traffic light
#define TIME_IN_GREEN 7000
#define TIME_IN_YELLOW 3000
#define TIME_IN_RED 10000
#define CORRECT_DISTANCE 50
//Puntuation
#define MAX_POINTS 100
#define MINUS_TRAFFIC_LIGHT 20
#define MINUS_VELOCITY 10
#define MINUS_TRAFFIC_SIGNALS 25
#define MINUS_COLISION 15

int puntuation, referenceTime, timePassed;
long t_pulse, distance_cm, velocity;
bool wasRed, wasYellow, wasGreen, isRed, isYellow, isGreen;
void setup() {
  pinMode(RED_LED1, OUTPUT);
  pinMode(YELLOW_LED1, OUTPUT);
  pinMode(GREEN_LED1, OUTPUT);
  pinMode(RED_LED2, OUTPUT);
  pinMode(YELLOW_LED2, OUTPUT);
  pinMode(GREEN_LED2, OUTPUT);
  //INITIALIZATION
  analogWrite(LIGHT_SIGNAL0, 0);
  analogWrite(LIGHT_SIGNAL1, 0);
  analogWrite(LIGHT_SIGNAL2, 0);
  analogWrite(LIGHT_SIGNAL3, 0);
  analogWrite(LIGHT_SIGNAL4, 0);
  digitalWrite(TRIGGER1, 0);
  digitalWrite(ECHO1, 0);
  digitalWrite(TRIGGER2, 0);
  digitalWrite(ECHO2, 0);
  digitalWrite(RED_LED1, HIGH);
  digitalWrite(RED_LED2, HIGH);
  puntuatuon = MAX_POINTS;
  referenceTime, timePassed = 0;
  t_pulse, distance_cm1, distance_cm2, velocity = 0;
  isRed = true;
  isYellow, isGreen = false;
  wasRed wasYellow, wasGreen = false;
}

void loop() {
 digitalWrite(TRIGGER1, LOW);
 digitalWrite(TRIGGER2, LOW);
 delayMicroseconds(4);
 digitalWrite(TRIGGER1, HIGH);
 digitalWrite(TRIGGER2, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIGGER1, LOW);
 digitalWrite(TRIGGER2, LOW);
 t_pulse1 = pulseIn(ECHO1, HIGH);
 t_pulse2 = pulseIn(ECHO2, HIGH);
 distance_cm1 = ((t_pulse1/1000000)*340*100)/2;
 distance_cm2 = ((t_pulse2/1000000)*340*100)/2;
 if(isRed || isGreen || isYellow){
   referenceTime = millis();
 }

 if(isRed && millis() - referenceTime > TIME_IN_RED){
   isRed = false;
   isGreen = true;
   digitalWrite(RED_LED1, LOW);
   digitalWrite(RED_LED2, LOW);
   digitalWrite(GREEN_LED1, HIGH);
   digitalWrite(GREEN_LED2, HIGH);
 }
 if(isRed && (distance_cm1 < CORRECT_DISTANCE || distance_cm2 < CORRECT_DISTANCE)){
   //Puntuacio -= MINUS_TRAFFIC_LIGHT
 }

  if(isGreen && millis() - referenceTime > TIME_IN_GREEN){
   isGreen = false;
   isYellow = true;
   digitalWrite(GREEN_LED1, LOW);
   digitalWrite(GREEN_LED2, LOW);
   digitalWrite(YELLOW_LED1, HIGH);
   digitalWrite(YELLOW_LED2, HIGH);
 }
 if(isYellow && millis() - referenceTime > TIME_IN_YELLOW){
   isYellow = false;
   isRed = true;
   digitalWrite(YELLOW_LED1, LOW);
   digitalWrite(YELLOW_LED2, LOW);
   digitalWrite(RED_LED1, HIGH);
   digitalWrite(RED_LED2, HIGH);
 }
}
