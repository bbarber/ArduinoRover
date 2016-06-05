#include <Servo.h>

// Constants
int maxMoveSpeed = 10;
int maxTurnSpeed = 6;
int maxCenterDiff = 10;

// Max values from tx/rx
int pwmMin = 1050;
int pwmMax = 1910;

// Initial center depends what
// you set your servo pot to
int lCenterInit = 55;
int rCenterInit = 54;

int lCenter;
int rCenter;

// Pins
int lPotPin = 0;
int rPotPin = 1;

int upDownPin = 10;
int leftRightPin = 11;

Servo lServo;
Servo rServo;

void setup() {
  lServo.attach(8);
  rServo.attach(9);

  Serial.begin(9600);
}

void loop() {

  centerServos();

  // Get pwm values from rx
  int upDownVal = pulseIn(upDownPin, HIGH);
  int leftRightVal = pulseIn(leftRightPin, HIGH);

  int moveSpeed = map(upDownVal, pwmMin, pwmMax, -maxMoveSpeed, maxMoveSpeed);
  int turnSpeed = map(leftRightVal, pwmMin, pwmMax, maxTurnSpeed, -maxTurnSpeed);

  lServo.write(lCenter + moveSpeed + turnSpeed);
  rServo.write(rCenter - moveSpeed + turnSpeed);

  delay(100);
}

void centerServos() {
  // value between 0 and 1023
  int lPotVal = analogRead(lPotPin);
  int rPotVal = analogRead(rPotPin);

  int lDiff = map(lPotVal, 0, 1023, -maxCenterDiff, maxCenterDiff);
  int rDiff = map(rPotVal, 0, 1023, -maxCenterDiff, maxCenterDiff);

  lCenter = lCenterInit + lDiff;
  rCenter = rCenterInit + rDiff;
}





