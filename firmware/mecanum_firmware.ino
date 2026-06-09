#include <AFMotor.h>

// Motor Definitions mapped to L293D Ports
AF_DCMotor motorFL(1); // Front Left
AF_DCMotor motorRL(2); // Rear Left
AF_DCMotor motorRR(3); // Rear Right
AF_DCMotor motorFR(4); // Front Right

int wheelSpeed = 150; // Default Speed (0-255)
int command = 0;

void setup() {
  Serial.begin(115200); 
  delay(100);
  stopMoving();
}

void loop() {
  if (Serial.available() > 0) {
    String incomingString = Serial.readStringUntil('\n');
    int val = incomingString.toInt();

    if (val >= 20) {
      wheelSpeed = val;
    } else {
      command = val;
      processCommand(command);
    }
  }
}

void processCommand(int cmd) {
  setAllSpeed(wheelSpeed);

  switch (cmd) {
    case 2: moveForward(); break;
    case 7: moveBackward(); break;
    case 5: moveSidewaysRight(); break;
    case 4: moveSidewaysLeft(); break;
    case 9: rotateLeft(); break;
    case 10: rotateRight(); break;
    case 3: moveDiagonalFrontRight(); break;
    case 1: moveDiagonalFrontLeft(); break;
    case 8: moveDiagonalBackRight(); break;
    case 6: moveDiagonalBackLeft(); break;
    case 0: stopMoving(); break;
    default: stopMoving(); break;
  }
}

void setAllSpeed(int speed) {
  motorFL.setSpeed(speed);
  motorRL.setSpeed(speed);
  motorRR.setSpeed(speed);
  motorFR.setSpeed(speed);
}

void moveForward() {
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
  motorRR.run(FORWARD);
  motorFR.run(FORWARD);
}

void moveBackward() {
  motorFL.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorRR.run(BACKWARD);
  motorFR.run(BACKWARD);
}

void moveSidewaysRight() {
  motorFL.run(FORWARD);
  motorRL.run(BACKWARD);
  motorFR.run(BACKWARD);
  motorRR.run(FORWARD);
}

void moveSidewaysLeft() {
  motorFL.run(BACKWARD);
  motorRL.run(FORWARD);
  motorFR.run(FORWARD);
  motorRR.run(BACKWARD);
}

void rotateRight() {
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
  motorFR.run(BACKWARD);
  motorRR.run(BACKWARD);
}

void rotateLeft() {
  motorFL.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorFR.run(FORWARD);
  motorRR.run(FORWARD);
}

void moveDiagonalFrontRight() {
  motorFL.run(FORWARD);
  motorRL.run(RELEASE);
  motorFR.run(RELEASE);
  motorRR.run(FORWARD);
}

void moveDiagonalFrontLeft() {
  motorFL.run(RELEASE);
  motorRL.run(FORWARD);
  motorFR.run(FORWARD);
  motorRR.run(RELEASE);
}

void moveDiagonalBackRight() {
  motorFL.run(RELEASE);
  motorRL.run(BACKWARD);
  motorFR.run(BACKWARD);
  motorRR.run(RELEASE);
}

void moveDiagonalBackLeft() {
  motorFL.run(BACKWARD);
  motorRL.run(RELEASE);
  motorFR.run(RELEASE);
  motorRR.run(BACKWARD);
}

void stopMoving() {
  motorFL.run(RELEASE);
  motorRL.run(RELEASE);
  motorFR.run(RELEASE);
  motorRR.run(RELEASE);
}