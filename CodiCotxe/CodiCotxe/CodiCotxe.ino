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
#define CTS 0
#define TX 1

void setup() {
 pinMode(MOTOR_DRIVER_IN_1, OUTPUT);
 pinMode(MOTOR_DRIVER_IN_2, OUTPUT);
 pinMode(MOTOR_DRIVER_IN_3, OUTPUT);
 pinMode(MOTOR_DRIVER_IN_4, OUTPUT);
 pinMode(MOTOR_DRIVER_ENABLE1, OUTPUT);
 pinMode(MOTOR_DRIVER_ENABLE2, OUTPUT);
 pinMode(CTS, );
 pinMode(TX, )

 //Inicialització
 digitalWrite (MOTOR_DRIVER_IN_1, 0);
 digitalWrite (MOTOR_DRIVER_IN_2, 0);
 digitalWrite (MOTOR_DRIVER_IN_3, 0);
 digitalWrite (MOTOR_DRIVER_IN_4, 0);
 analogWrite (MOTOR_DRIVER_ENABLE1, 0);
 analogWrite (MOTOR_DRIVER_ENABLE2, 0);

 boolean motor_rotation;
 motor_rotation = 
}

void loop() {
    
}
