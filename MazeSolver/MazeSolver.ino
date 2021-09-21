#define IN1 3
#define IN2 2
#define IN3 5
#define IN4 4
#define ENA 9
#define ENB 10
#define ultratrigFront 6
#define ultratrigLeft 11
#define ultraechoFront 7
#define ultraechoLeft 12
#define ultratrigRight 8
#define ultraechoRight 13

unsigned int duration;
unsigned int distance;

unsigned int MotorsSpeed = 100;

unsigned int delayer = 300;

unsigned int rotateDelayer = 200;

unsigned int rotateSpeed = 255;

unsigned int leftSensor = ultraSonic(11, 12);
unsigned int rightSensor = ultraSonic(8, 13);
unsigned int frontSensor = ultraSonic(6, 7);

void setup()
{
  pinMode(ultratrigFront, OUTPUT);
  pinMode(ultraechoFront, INPUT);
  //Serial.begin(9600);
  pinMode(ultratrigLeft, OUTPUT);
  pinMode(ultraechoLeft, INPUT);
  pinMode(ultratrigRight, INPUT);
  pinMode(ultraechoRight, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop()
{
  movingRightorLeftBlind();

  if (leftSensor > 25)
  {
    stopMotors();
    delay(delayer);
    left();
    delay(rotateDelayer);
    stopMotors();
    delay(300);
    forward();
    delay(delayer);
  }

  else if (frontSensor < 12 && leftSensor < 25)
  {
    stopMotors();
    delay(delayer);
    right();
    delay(rotateDelayer);
    stopMotors();
    delay(300);
    forward();
    delay(delayer);
  }

  else if (rightSensor < 15 && frontSensor < 15 && leftSensor < 15)
  {
    stopMotors();
  }
}
unsigned int ultraSonic(unsigned int ultraTrigPin, unsigned int ultraEchoPin)
{
  digitalWrite(ultraTrigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(ultraTrigPin, LOW);
  delayMicroseconds(1000);
  duration = pulseIn(ultraEchoPin, HIGH);
  return distance = duration * 0.034 / 2;
}

void forwardErrorCorrector(int error)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, MotorsSpeed - 2 * error);
  analogWrite(ENB, MotorsSpeed + 2 * error);
}

void movingRightorLeftBlind()
{
  while (frontSensor > 15)
  {

    if (leftSensor <= 35 && rightSensor <= 35)
    {
      forwardErrorCorrector(leftSensor - rightSensor);
    }

    if (rightSensor > 40)
    {
      forwardErrorCorrector(leftSensor - 13);
    }

    if (leftSensor > 40)
    {
      forwardErrorCorrector(13 - rightSensor);
    }

    if (leftSensor > 40 && rightSensor > 40)
    {
      forward();
    }
  }
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, MotorsSpeed);
  analogWrite(ENB, MotorsSpeed);
}
void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, rotateSpeed);
  analogWrite(ENB, rotateSpeed);
}
void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, rotateSpeed);
  analogWrite(ENB, rotateSpeed);
}
