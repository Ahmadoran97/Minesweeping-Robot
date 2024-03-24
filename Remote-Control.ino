//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
int ton;
int ts;
int mag;
int x, y, x1, y1;
//bool s1=0,s2=0;

typedef struct {
  char mov;
  char magnatic;
  int spee;
  int spee1;

} data;
data data1;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  //pinMode(5, INPUT);
  //pinMode(6, INPUT);

  Serial.begin(9600);

  radio.begin();

  //set the address
  radio.openWritingPipe(address);

  //Set module as transmitter
  radio.stopListening();
}

void MOVE() {
  if (y > 140) {
    data1.mov = 'b';
    Serial.println('b');
  }
  else if (y < 100) {
    data1.mov = 'f';
    Serial.println('f');

  }
  else if (x > 140) {
    data1.mov = 'l';
    Serial.println('l');

  }
  else if (x < 100) {
    data1.mov = 'r';
    Serial.println('r');

  }
  else {
    data1.mov = ' ';
    Serial.println('s');
  }


}

void ARM() {
  if (y > 140) {
    data1.mov = 'Q';
    Serial.println('Q');
  }
  else if (y < 100) {
    data1.mov = 'A';
    Serial.println('A');
  }
  else if (x > 140) {
    data1.mov = 'Z';
    Serial.println('Z');
  }
  else if (x < 100) {
    data1.mov = 'W';
   Serial.println('W');
  }
  else if (y1 > 140) {
    data1.mov = 'S';
   Serial.println('S');
  }
  else if (y1 < 100) {
    data1.mov = 'X';
   Serial.println('X');
  }
  else if (x1 > 140) {
    data1.mov = 'E';
    Serial.println('E');
  }
  else if (x1 < 100) {
    data1.mov = 'D';
    Serial.println('D');
  }
 /* else if (s1==1){

 data1.mov = ']';
//    Serial.println(']');}
   
     else if (s2==1){

 data1.mov = '[';
   // Serial.println('[');}

   */ 
  else {
    data1.mov = ' ';
   Serial.println(' ');
  }
  ton = digitalRead(2);


  if (ton == 1)
  {
    data1.magnatic = '1';
    //Serial.println('1');

  }
  else if (ton == 0) {
    data1.magnatic = '0';
    //Serial.println('0');
  }


}

void loop() {
  x = map(analogRead(A1), 0, 800, 0, 255);
  y = map(analogRead(A0), 0, 800, 0, 255);
  x1 = map(analogRead(A6), 0, 800, 0, 255);
  y1 = map(analogRead(A7), 0, 800, 0, 255);
data1.spee=map(analogRead(A4), 0, 800, 0, 255);
data1.spee1=map(analogRead(A5), 0, 800, 0, 255);
//s1=digitalRead(5);
//s2=digitalRead(6);
  //on off

  ts = digitalRead(3);
  //toggle switch for robot moving
  if (ts == 1) {
    MOVE();
  }

  //toggle switch for arm robot
  else if (ts == 0) {
    ARM();

  }
//Serial.print("      ");
//Serial.print(data1.spee);
//Serial.print("      ");
//Serial.print(data1.spee1);

  radio.write(&data1, sizeof(data1));



}
