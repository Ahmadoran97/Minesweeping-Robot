
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
float timeStep = 0.01;
float yaw = 0;

int out = 0;// these variables to avoid unwanted signals 
int data;
int i;
int distance =0;
volatile signed long counter1 = 0;  //This variable will increase or decrease depending on the rotation of encoder
volatile signed long counter2 = 0;  //This variable will increase or decrease depending on the rotation of encoder

int IR1=4,IR2=5,IR3=6;// IR pins 
// connect Encoder 1 to 2,3 pins ,, encoder 2 to 20,21 pins ,, metal detector to 8 pin
void setup() {
Serial.begin(9600);
 while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);  
  }
    mpu.calibrateGyro();
    mpu.setThreshold(5);
    
 pinMode(8,INPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
  pinMode(2, INPUT);         // set pin to input
  pinMode(3, INPUT);        // set pin to input// encoder number 1
 
  pinMode(21, INPUT);         // set pin to input
  pinMode(20, INPUT);         // set pin to input// encoder number 2 
 
  digitalWrite(2, HIGH);    // turn on pullup resistors
  digitalWrite(3, HIGH);    // turn on pullup resistors
  digitalWrite(21, HIGH);     // turn on pullup resistors
  digitalWrite(20, HIGH);     // turn on pullup resistors
 
  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(2, ai2, RISING);
 
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
  attachInterrupt(3, ai3, RISING);

}

void loop() {

  
  Vector norm = mpu.readNormalizeGyro();
  yaw = yaw + norm.ZAxis * timeStep;
 
  Serial.println(yaw);


  
int x = detectorVoid(8);
Serial.print ("Metal detector value =");
Serial.println(x);
distance=0.13083333333*counter1/2;
  Serial.print ("counter1:");
  Serial.print (counter1);
  Serial.print ("-----------");
  Serial.print ("counter2:");
  Serial.println (counter2);
   int irVal1= digitalRead(IR1);
   int irVal2= digitalRead(IR2);
   int irVal3= digitalRead(IR3);
   Serial.print ("IR Values");
   Serial.print (irVal1);
   Serial.print ("---");
   Serial.print (irVal2);
   Serial.print ("---");
   Serial.println (irVal3);

}

int detectorVoid(int pin){
    data = digitalRead(pin);

  // put your main code here, to run repeatedly:
if ( data == 1){
  for (i=0;i<200;i++)
  {delay(1);
  data=digitalRead(pin);
  if(data==0)
  break;}
  if(i==200){
  out = 1;}
  
}
else
{
  out = 0;
}
return(out);
}

void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(3)==LOW) {
  counter1++;
  }else{
  counter1--;
  }
}
void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
  counter1--;
  }else{
  counter1++;
  }
}

void ai2() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(20)==LOW) {
  counter2++;
  }else{
  counter2--;
  }
}

void ai3() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(21)==LOW) {
  counter2--;
  }else{
  counter2++;
  }
}
