//Include Libraries

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//create an RF24 object
RF24 radio(49, 48);  // CE, CSN

//address thr5ough which two modules communicate.
const byte address[6] = "00001";



int motor1_r = 5;
int motor1_l = 4;

int motor2_r = 11;
int motor2_l = 12;
int i;
int j;

typedef struct {
  char mov;
  char magnatic;
  int spee;
  int spee1;

} data;
data data1;

void setup()
{
  while (!Serial);
  Serial.begin(9600);

  radio.begin();

  //set the address
  radio.openReadingPipe(0, address);


  //Set module as receiver
  radio.startListening();
  pinMode(motor1_r, OUTPUT);
  pinMode(motor1_l, OUTPUT);
  pinMode(motor2_r, OUTPUT);
  pinMode(motor2_l, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(motor1_r, 0);
  digitalWrite(motor1_l, 0);
  digitalWrite(motor2_r, 0);
  digitalWrite(motor2_l, 0);
  digitalWrite(3, 0);

}
void forword()
{
  analogWrite(motor1_r, i);
  analogWrite(motor1_l, 0);

  analogWrite(motor2_r, i);
  analogWrite(motor2_l, 0);



}

void backword()
{
  analogWrite(motor1_r, 0);
  analogWrite(motor1_l, i);

  analogWrite(motor2_r, 0);
  analogWrite(motor2_l, i);
}
void right()
{
  analogWrite(motor1_r, 0);
  analogWrite(motor1_l, j);

  analogWrite(motor2_r, j);
  analogWrite(motor2_l, 0);
}

void left()
{
  analogWrite(motor1_r, j);
  analogWrite(motor1_l, 0);

  analogWrite(motor2_r, 0);
  analogWrite(motor2_l, j);
}
void st()
{
  analogWrite(motor1_r, 0);
  analogWrite(motor1_l, 0);

  analogWrite(motor2_r, 0);
  analogWrite(motor2_l, 0);
}



void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    radio.read(&data1, sizeof(data1));
    Serial.print("mov: ");
    Serial.print(data1.mov);
    Serial.print("  magnatic: ");
    if (data1.magnatic == '1') {
      digitalWrite(22, HIGH);
    }
    else digitalWrite(22, LOW);
    Serial.print("   speed: ");
    Serial.println(data1.spee);
    i = data1.spee;
    j = data1.spee1;

    if (data1.mov == 'f')forword();
    else if (data1.mov == 'b')backword();
    else if (data1.mov == 'r') {
      right();
      digitalWrite(3, 1);
    }
    else if (data1.mov == 'l') {
      left();
      digitalWrite(3, 1);

    }
    else if (data1.mov == ' ') {
      st();
      digitalWrite(3, 0);

    }



    delay(5);
  }
}
