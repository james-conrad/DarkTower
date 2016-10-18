#include <Stepper.h>

#define STEPS_PER_ROTATION 21989

#define MOTOR1 19
#define MOTOR2 18
#define MOTOR3 17
#define MOTOR4 16

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  pinMode(MOTOR4, OUTPUT);
}


void motorDelay()
{
  delay(2);
}

unsigned int steps = 1000000;

void step(int dir)
{
  if (dir == 0)
    steps--;
  else
    steps++;

  int phase = steps & 0x07;

  switch (phase)
  {
    case 0:
      digitalWrite(MOTOR1, HIGH);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, LOW);
      break;

    case 1:
      digitalWrite(MOTOR1, HIGH);
      digitalWrite(MOTOR2, HIGH);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, LOW);
      break;

    case 2:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, HIGH);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, LOW);
      break;

    case 3:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, HIGH);
      digitalWrite(MOTOR3, HIGH);
      digitalWrite(MOTOR4, LOW);
      break;

    case 4:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, HIGH);
      digitalWrite(MOTOR4, LOW);
      break;

    case 5:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, HIGH);
      digitalWrite(MOTOR4, HIGH);
      break;

    case 6:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, HIGH);
      break;

 
    case 7:
      digitalWrite(MOTOR1, HIGH);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, HIGH);
      break;
  }

  motorDelay();
}


void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for (i=0; i < 21989 /4; ++i)
    step(0);

  delay(1500);
  
  for (i=0; i< 21989 /4; ++i)
    step(1);

  delay(1500);
}

