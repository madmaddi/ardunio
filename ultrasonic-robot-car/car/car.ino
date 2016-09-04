/* Code Written by Roy Pe'er. I've explained all the code in the grey comments.
I recommend you to go over the code, examine it, play with it, improve it and modify it according to your needs. 
For more awesome videos, subsrice to my channel:
http://www.youtube.com/subscription_center?add_user=Roypeer1
*/

#include <AFMotor.h> //import your motor shield library
#define trigPin 12 // define the pins of your sensor
#define echoPin 13 
//AF_DCMotor motor1(1,MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor1(1, MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_64KHZ);

// Benoetigte Variablen werden definiert
int maximumRange = 300; 
int minimumRange = 2; 

long abstand;
long dauer;
long distance;
bool motorEnabled = true;

int delayTime = 250;
int turnOverTime = 500;
int waitTime = 500;
int forwardTime = 1000;
/*
  * 0 = STOP
  * 1 = FORWARD
  * 2 = BACKWARD
  * 3 = TURN LEFT
  * 4 = TURN RIGHT
*/
int motorStatus = 0 ;

int carspeed2 = 200;
int carspeed1 = carspeed2 - 8;


void setup() {
  
  Serial.begin(9600); // begin serial communitication  
  Serial.println("Motor test!");
  pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)

  setMotorSpeed(carspeed1, carspeed2); //set the speed of the motors, between 0-255

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
  delay(waitTime);
  distance = cumulateDistance();
  //Serial.println(distance);
  
  if ( distance < 40.0 ) { 
    Serial.println(distance);  
    // 1st.: STOP
    stopMotor();  
    
    // change direction unless distance greater than 0.4m
    while(distance < 60.0 ) {
      distance = cumulateDistance();
      //Serial.println(distance);
      //Serial.println("turn over");  
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
    delay(forwardTime); // drive through 0.5s
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
//  Serial.println("Distance:");
  for (int i=0; i<measurements; i++){
    distance = fetchDistance();
//    Serial.println(distance);
    avg += distance;
    di[i] = distance;
  }
  
  avg = avg/measurements;
  //Serial.println("avg: ");
  //Serial.println(avg);
  
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
  //Serial.println("Distance");
  Serial.println(returnValue);
  return returnValue;
}


void turnLeft(){
  if ( motorStatus != 3 ) {
    Serial.println("turn left");  
    motorStatus = 3;
    //setMotorSpeed(50);
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
  //Serial.println("setMotorSpeed");
  //Serial.println(sspeed);
  delay(10);
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

