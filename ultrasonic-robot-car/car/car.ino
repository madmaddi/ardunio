
#include <AFMotor.h> 
#define trigPin 12 
#define echoPin 13 

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

bool motorEnabled = true;

int delayTime = 250;
int turnOverTime = 500;
int waitTime = 500;
int forwardTime = 1000;

int carspeed2 = 200;
int carspeed1 = carspeed2 - 8;

long abstand;
long dauer;
long distance;

/*
  * 0 = STOP
  * 1 = FORWARD
  * 2 = BACKWARD
  * 3 = TURN LEFT
  * 4 = TURN RIGHT
*/
int motorStatus = 0 ;

void setup() {
  Serial.begin(9600); // begin serial communitication  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  setMotorSpeed(carspeed1, carspeed2); //set the speed of the motors, between 0-255
  motor1.run(RELEASE); // stop motors
  motor2.run(RELEASE);
}

void loop() {
  delay(waitTime);
  distance = cumulateDistance();
  
  if ( distance < 40.0 ) { 
    Serial.println(distance);  
    // 1st.: STOP
    stopMotor();  
    
    // change direction unless distance lower than x
    while(distance < 60.0 ) {
      distance = cumulateDistance();  
      delay(waitTime);
      turnLeft();
      delay(turnOverTime);
      stopMotor();
      delay(delayTime);
      distance = cumulateDistance();
      Serial.println("########");
    }
  } else {
    forwardMotor();
    delay(forwardTime); // drive through some ms
    stopMotor();
  }

  Serial.println("--------------");
}

long cumulateDistance(){
  int measurements = 5;
  
  // do x measurements
  long di[5];
  long avg = 0.0;
  long distance = 0.0;
  
  for (int i=0; i<measurements; i++){
    distance = fetchDistance();
    avg += distance;
    di[i] = distance;
  }
  
  avg = avg/measurements;
  
  // get lowest distance from di to avg
  long avgDistance = 0.0;
  long nearestDistance = 1000.0;
  long returnValue = 0.0;
  for ( int i=0; i<measurements; i++) {
    avgDistance = abs(avg - di[i]);
    if (avgDistance < nearestDistance) {
      nearestDistance = avgDistance;
      returnValue = di[i];
    }
  }
  
  Serial.println(returnValue);
  return returnValue;
}


void turnLeft(){
  if ( motorStatus != 3 ) {
    Serial.println("turn left");  
    motorStatus = 3;
    if ( !motorEnabled ) return;
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
  } 
}

void turnRight(){
  if ( motorStatus != 4 ) {
    Serial.println("turn right");  
    motorStatus = 4;
    if ( !motorEnabled ) return;
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
  } 
}

void stopMotor() {
  if ( motorStatus != 0 ) {
    Serial.println("stop motor");  
    motorStatus = 0;
    if ( !motorEnabled ) return;
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  } 
}

void forwardMotor() {
  if ( motorStatus != 1 ) {
    Serial.println("forward motor");  
    motorStatus = 1;
    if ( !motorEnabled ) return;
    setMotorSpeed(carspeed1, carspeed2);
    motor1.run(FORWARD);
    motor2.run(FORWARD);  
  }
}

void setMotorSpeed(int sspeed1, int sspeed2) {
  motor1.setSpeed(sspeed1); //set the speed of the motors, between 0-255
  motor2.setSpeed(sspeed2); 
}


long fetchDistance(){
  long duration, distance; // start the scan
  delay(100);
  
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;// convert the distance to centimeters.
  return distance;
}

