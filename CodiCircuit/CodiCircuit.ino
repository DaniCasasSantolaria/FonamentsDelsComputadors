//LDRS
#define LIGHT_SIGNAL0 A0
#define LIGHT_SIGNAL1 A1
#define LIGHT_SIGNAL2 A2
#define LIGHT_SIGNAL3 A3
#define LIGHT_SIGNAL4 A4

//Ultrasonic sensor
#define TRIGGER1 11
#define ECHO1 5
#define TRIGGER2 10
#define ECHO2 3

//LEDS D2,D4,D7,D8,D12,D13
#define RED_LED1 2
#define YELLOW_LED1 4
#define GREEN_LED1 7
#define RED_LED2 8
#define YELLOW_LED2 12
#define GREEN_LED2 13

// BUZZER
#define BUZZER 9

//Configuration parameters
//Traffic light
#define TIME_IN_GREEN 8000
#define TIME_IN_YELLOW 3000
#define TIME_IN_RED 9000
#define CORRECT_DISTANCE 50
//Punctuation
#define MAX_POINTS 100
#define MINUS_TRAFFIC_LIGHT 20
#define MINUS_VELOCITY 10
#define MINUS_TRAFFIC_SIGNALS 25
#define MINUS_COLLISION 15

int punctuation = MAX_POINTS;
unsigned long referenceTime;
long t_pulse1, t_pulse2, distance_cm1, distance_cm2, velocity;
bool isRed, isYellow, isGreen;

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_SIGNAL0, OUTPUT);
  pinMode(LIGHT_SIGNAL1, OUTPUT);
  pinMode(LIGHT_SIGNAL2, OUTPUT);
  pinMode(LIGHT_SIGNAL3, OUTPUT);
  pinMode(LIGHT_SIGNAL4, OUTPUT);
  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(RED_LED1, OUTPUT);
  pinMode(YELLOW_LED1, OUTPUT);
  pinMode(GREEN_LED1, OUTPUT);
  pinMode(RED_LED2, OUTPUT);
  pinMode(YELLOW_LED2, OUTPUT);
  pinMode(GREEN_LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(RED_LED1, HIGH);
  digitalWrite(RED_LED2, HIGH);
  digitalWrite(YELLOW_LED1, LOW);
  digitalWrite(YELLOW_LED2, LOW);
  digitalWrite(GREEN_LED1, LOW);
  digitalWrite(GREEN_LED2, LOW);

  referenceTime = 0;
  isRed = true;
  isYellow = false;
  isGreen = false;
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
  distance_cm1 = t_pulse1 * 10 / 292 / 2;
  distance_cm2 = t_pulse2 * 10 / 292 / 2;
  Serial.println(distance_cm1);
  // SEMÀFORS
  if (isRed && millis() - referenceTime > TIME_IN_RED) {  // RED -> GREEN
    isRed = false;
    isGreen = true;
    digitalWrite(RED_LED1, LOW);
    digitalWrite(RED_LED2, LOW);
    digitalWrite(GREEN_LED1, HIGH);
    digitalWrite(GREEN_LED2, HIGH);
    referenceTime = millis();
  }
  if (isGreen && millis() - referenceTime > TIME_IN_GREEN) {  // GREEN -> YELLOW
    isGreen = false;
    isYellow = true;
    digitalWrite(GREEN_LED1, LOW);
    digitalWrite(GREEN_LED2, LOW);
    digitalWrite(YELLOW_LED1, HIGH);
    digitalWrite(YELLOW_LED2, HIGH);
    referenceTime = millis();
  }
  if (isYellow && millis() - referenceTime > TIME_IN_YELLOW) {  // YELLOW -> RED
    isYellow = false;
    isRed = true;
    digitalWrite(YELLOW_LED1, LOW);
    digitalWrite(YELLOW_LED2, LOW);
    digitalWrite(RED_LED1, HIGH);
    digitalWrite(RED_LED2, HIGH);
    referenceTime = millis();
  }

  // SENSORS DE ULTRASÓ

  if(distance_cm1 < 16 && isRed){
    tone(BUZZER, 100);
  }
  else{
    noTone(BUZZER);
  }
  /*if(distance_cm2 < 16 && isRed){
    tone(BUZZER, 800, 64);
  }*/
}


