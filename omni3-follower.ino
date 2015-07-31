//  Line_Follower_Display_Tripod_150725

//  Direction coordinates in Direction subroutine programmed according to paper obtained at this site:
//  http://www.researchgate.net/publication/228786543_Three_omni-directional_wheels_control_on_a_mobile_robot
//  Some fine tuning was required, due to differences between the three servos

#define SIZE 14
#define CUTOFF 150
#include <Servo.h>
Servo myservoA; 
Servo myservoB;  
Servo myservoC;
int TRUE = HIGH;
int FALSE = LOW;
int black;
int blacks = 0;
int CENTER = 13;
int find = 0;
int i = 0;
int inside = 0;
int loops = 0;
int outside = 0;
int STOP = 15;
int quit = FALSE;
long time;
long time0;
int ledPins[SIZE] = {0,31,32,33,34,35,36,37,38,39,40,41,42,43};
int lightLevel[SIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
int list[37] = {0,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12};

void setup() {
  Serial.begin(9600);
  myservoA.attach(22);  
  myservoB.attach(23);
  myservoC.attach(24);
  Direction(STOP);
  for (int i = 1; i < SIZE; i++) {
    pinMode(lightLevel[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = 1; i < 4; i++) {
    digitalWrite(ledPins[1], HIGH);
    delay (200);
    digitalWrite(ledPins[1], LOW);
    delay (200);
  }
  digitalWrite(ledPins[1], HIGH);
  delay (3000);
  scan();
  time = millis();
  Serial.println(" ");
  Serial.println ("Point 0 - start");
  Serial.print("time = ");
  Serial.println(time);
  sensors ();
  //
  // find start point
  //
  find = 0;
  time0 = millis();
  do {
    Direction(4);
    if (analogRead(CENTER) > CUTOFF && find == 0) {
      find = 1;
    }
    else if (analogRead(CENTER) < CUTOFF && find == 1) {
      find = 2;
      i = 1;
    }
  }
  while (find != 2 && millis() - time0 < 3000);
  if (find !=2){
    find = 0;
    do {
      Direction(10);
      if (analogRead(CENTER) > CUTOFF && find == 0) {
        find = 1;
      }
      else if (analogRead(CENTER) < CUTOFF && find == 1) {
        find = 2;
        i = 7;
      }
    }
    while (find != 2);
  }
  Direction(STOP);
  delay(5);
  Serial.println (" ");
  Serial.println("Point 1 - moved into position, find initial inside outside");
  scan();
  sensors();
  
//
// find inside
//
  quit = FALSE;
  do {
    if (lightLevel[list[19-i]] < CUTOFF) {
      inside = list[19-i];
      i = i + 1;
    }
    else {
      quit = TRUE;
    }    
  }
  while (quit == FALSE);
  outside = list[inside+9];
  Serial.print("inside = ");
  Serial.println(inside);
  Serial.print("outside = ");
  Serial.println(outside);
}
//---------------------------------end of Void Setup----------------------------------

void loop () {
  //
  // Move inside direction
  //
  loops =  0;
  if (analogRead(outside) < CUTOFF && analogRead(CENTER) < CUTOFF) {
    Direction(inside);
    lightLevel[outside] = analogRead(outside);
    lightLevel[CENTER] = analogRead(CENTER);
    while (lightLevel[outside] < CUTOFF && lightLevel[CENTER] < CUTOFF) {
      lightLevel[outside] = analogRead(outside);
      lightLevel[CENTER] = analogRead(CENTER);
      loops = loops + 1;
    }
  }
  Direction(STOP);
  Serial.println(" ");
  Serial.print("lightLevel[outside] = ");
  Serial.println(lightLevel[outside]);
  Serial.print("lightLevel[CENTER] = ");
  Serial.println(lightLevel[CENTER]);
  Serial.println("Point 2 - moved inside direction - normal move");
  Serial.print("loops = ");
  Serial.println(loops);
  //
  // Move outside direction
  //
  loops = 0;
  if (analogRead(CENTER) < CUTOFF) {
    Direction(outside);
    while (analogRead(CENTER) < CUTOFF) {
      loops = loops + 1;
    }
  }
  Direction(STOP);
  Serial.println(" ");
  Serial.println ("Point 3 - moved outside direction - normal move");
  Serial.print("loops = ");
  Serial.println(loops);
  scan();
  sensors();
  //
  // find new inside and outside
  //
  findInsideOutside();
  loops = 0;
  if (analogRead(CENTER) >= CUTOFF) {
    Direction(list[inside+1]);
    while (analogRead(CENTER) >= CUTOFF) {
      loops = loops + 1;
    }
    Serial.println(" ");
    Serial.println ("Point 4 - moved CENTER off line");
    Serial.print("loops = ");
    Serial.println(loops);
    scan();
    sensors();
  }
}
//---------------------------------end of void loop----------------------------------

    
void Direction (int x) {
  switch (x) {
  case 1:
    digitalWrite(ledPins[1], HIGH);
    myservoA.write(82.98);     
    myservoB.write(97);
    myservoC.write(90);
    break;
    
  case 2:
    digitalWrite(ledPins[2], HIGH);
    myservoA.write(87);     
    myservoB.write(97);
    myservoC.write(86.6);
    break;
  
  case 3:
    digitalWrite(ledPins[3], HIGH);
    myservoA.write(90);     
    myservoB.write(97);
    myservoC.write(83.2);
    break;
  
  case 4:
    digitalWrite(ledPins[4], HIGH);
    myservoA.write(93.4);     
    myservoB.write(93.7);
    myservoC.write(83.2);
    break;
  
  case 5:
    digitalWrite(ledPins[5], HIGH);
    myservoA.write(97.02);     
    myservoB.write(90);
    myservoC.write(83.2);
    break;
  
  case 6:
    digitalWrite(ledPins[6], HIGH);
    myservoA.write(97.02);     
    myservoB.write(87.2);
    myservoC.write(87.2);
    break;
  
  case 7:
    digitalWrite(ledPins[7], HIGH);
    myservoA.write(97.02);     
    myservoB.write(83);
    myservoC.write(90);
    break;
  
  case 8:
    digitalWrite(ledPins[8], HIGH);
    myservoA.write(93);     
    myservoB.write(83);
    myservoC.write(93.4);
    break;
  
  case 9:
    digitalWrite(ledPins[9], HIGH);
    myservoA.write(90);     
    myservoB.write(83);
    myservoC.write(96.8);
    break; 
  
  case 10:
    digitalWrite(ledPins[10], HIGH);
    myservoA.write(87);     
    myservoB.write(86.9);
    myservoC.write(97.2);
    break; 
  
  case 11:
    digitalWrite(ledPins[11], HIGH);
    myservoA.write(82.98);     
    myservoB.write(90);
    myservoC.write(96.8);
    break;
  
  case 12:
    digitalWrite(ledPins[12], HIGH);
    myservoA.write(82.98);     
    myservoB.write(93.5);
    myservoC.write(93.5);
    break;
    
  case 15:
    myservoA.write(90);     
    myservoB.write(90);
    myservoC.write(90);
    break;
 
  default:
    Serial.println ("No Case Found In Direction");
  }
} 

//---------------------------------end of Direction----------------------------------

void findInsideOutside() {
  //
  // FIND NEAREST blacks
  //
  if (lightLevel[inside] >= CUTOFF) {
    black = inside;
  }
  else if (lightLevel[list[inside+1]] >= CUTOFF){
    black = list[inside+1];
  }
  else if (lightLevel[list[inside+11]] >= CUTOFF){
    black = list[inside+11];
  }
  else if (lightLevel[list[inside+2]] >= CUTOFF){
    black = list[inside+2];
  }
  else if (lightLevel[list[inside+10]] >= CUTOFF){
    black = list[inside+10]; 
  }
  else if (lightLevel[list[inside+3]] >= CUTOFF){
    black = list[inside+3];
  }
  else if (lightLevel[list[inside+9]] >= CUTOFF){
    black = list[inside+9];
  }
  else if (lightLevel[list[inside+4]] >= CUTOFF){
    black = list[inside+4];
  }
  else if (lightLevel[list[inside+8]] >= CUTOFF){
    black = list[inside+8];
  }
  else if (lightLevel[list[inside+5]] >= CUTOFF){
    black = list[inside+5];
  }
  else if (lightLevel[list[inside+7]] >= CUTOFF){
    black = list[inside+7];
  }
  else if (lightLevel[list[inside+6]] >= CUTOFF){
    black = list[inside+6];
  }
  else {
    Direction(STOP);
  }
  for (i = 1; i < 12; i++){
    if (lightLevel[list[black + i]] < CUTOFF){
      inside = list[black + i];
      break;
    }  
  }
  outside = list[inside+9];
  Serial.println(" ");
  Serial.print("inside = ");
  Serial.println(inside);
  Serial.print("outside = ");
  Serial.println(outside);
}
//---------------------------------end of findInsideOutside-------------------------

void scan () {
  for (int i = 1; i < SIZE; i++) {
    digitalWrite(ledPins[i], LOW);
    lightLevel[i] = analogRead(i);
  }
}

//---------------------------------end of Scan---------------------------------------

void sensors () {
  blacks = 0;
  for (int i = 1; i < SIZE; i++) {
    if (lightLevel[i] > CUTOFF) {
      blacks = blacks + 1;
    }
  Serial.print(lightLevel[i]);
  Serial.print(", ");
  }
  Serial.println(" ");
  Serial.print("Number of blacks = ");
  Serial.println(blacks);
  for (int i = 1; i < SIZE; i++) {
    if (lightLevel[i] > CUTOFF) {
      Serial.print(i);
      Serial.print(", ");
    }
  }
  Serial.println(" ");
}
//---------------------------------end of sensors------------------------------------
