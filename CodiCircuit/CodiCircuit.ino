//LDRS
#define LIGHT_SIGNAL0 A0
#define LIGHT_SIGNAL1 A1
#define LIGHT_SIGNAL2 A2
#define LIGHT_SIGNAL3 A3
#define LIGHT_SIGNAL4 A4
#define MIN_LIGHT 400

//Ultrasonic sensor
#define TRIGGER1 11
#define ECHO1 5
#define TRIGGER2 9
#define ECHO2 3
#define MIN_TIME_STOPPED 3000

//LEDS D2,D4,D7,D8,D12,D13
#define RED_LED1 2
#define YELLOW_LED1 4
#define GREEN_LED1 7
#define RED_LED2 8
#define YELLOW_LED2 12
#define GREEN_LED2 13

// BUZZER
#define BUZZER 6

//Configuration parameters
//Traffic light
#define TIME_IN_GREEN 8000
#define TIME_IN_YELLOW 3000
#define TIME_IN_RED 9000
#define CORRECT_DISTANCE 50
//Punctuation
#define MAX_POINTS 9
#define MINUS_TRAFFIC_LIGHT 2
#define MINUS_VELOCITY 1
#define MINUS_TRAFFIC_SIGNALS 2
#define MINUS_COLLISION 2

int punctuation = MAX_POINTS;
unsigned long referenceTime, timeStopped;
long t_pulse1, t_pulse2, distance_cm1, distance_cm2, velocity;
bool isRed, isYellow, isGreen, hasTimed;

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_SIGNAL0, INPUT);
  pinMode(LIGHT_SIGNAL1, INPUT);
  pinMode(LIGHT_SIGNAL2, INPUT);
  pinMode(LIGHT_SIGNAL3, INPUT);
  pinMode(LIGHT_SIGNAL4, INPUT);
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
  timeStopped = 0;
  hasTimed = false;
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

  t_pulse1 = pulseIn(ECHO1, HIGH, 30000);
  t_pulse2 = pulseIn(ECHO2, HIGH, 30000);
  distance_cm1 = t_pulse1 * 10 / 292 / 2;
  distance_cm2 = t_pulse2 * 10 / 292 / 2;
  /*Serial.print("Distance 1: ");
  Serial.println(distance_cm1);
  Serial.print("Distance 2: ");
  Serial.println(distance_cm2);*/

  int ldr0 = analogRead(LIGHT_SIGNAL0);
  /*int ldr1 = analogRead(LIGHT_SIGNAL1);
  int ldr2 = analogRead(LIGHT_SIGNAL2);
  int ldr3 = analogRead(LIGHT_SIGNAL3);
  int ldr4 = analogRead(LIGHT_SIGNAL4);*/

  Serial.print("LDR 0: ");
  Serial.println(ldr0);
  /*Serial.print("LDR 1: ");
  Serial.println(ldr1);
  Serial.print("LDR 2: ");
  Serial.println(ldr2);
  Serial.print("LDR 3: ");
  Serial.println(ldr3);
  Serial.print("LDR 4: ");
  Serial.println(ldr4);*/
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

  if (distance_cm1 < 16 && isRed) {
    tone(BUZZER, 500, 4000);
  }
  /*
  if (distance_cm2 < 16 && isRed) {
    tone(BUZZER, 100);
  } else {
    noTone(BUZZER);
  }*/

  if (ldr0 < MIN_LIGHT) {
    // Si la luz es menor que el umbral y no se ha registrado el tiempo de parada
    if (!hasTimed) {
      hasTimed = true;
      timeStopped = millis();
    } else if (millis() - timeStopped > MIN_TIME_STOPPED + 3000) {
      // Si la luz es menor que el umbral y ha pasado el tiempo mínimo más un margen de 3 segundos
      hasTimed = false;
      timeStopped = 0;
    }
  } else {
    // Si la luz es mayor que el umbral antes de que el tiempo mínimo pase
    if (hasTimed && millis() - timeStopped < MIN_TIME_STOPPED) {
      tone(BUZZER, 900, 4000); // Suena el buzzer
    }
    hasTimed = false;
    timeStopped = 0;
  }

}
