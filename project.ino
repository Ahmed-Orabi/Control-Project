#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/************** Macros for Pins ************/
#define echo 3
#define trig 4
#define in1 5
#define in2 6
#define in3 7
#define in4 8
#define ena 9
#define enb 10
#define buzzer 11
//////////////////////////////////////////////////

uint32_t distance,time;

/************ Functions for directions of Robot ************/

void forward() //Moving Forward
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}
void backward() //Moving Bacward
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}
void right() //Moving Right
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}
void left() //Moving Left
{
  digitalWrite(IN1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}
void stop() //Stop
{
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}
//////////////////////////////////////////////////
void hold() //if distance less than 20 cm
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 0);
  analogWrite(enb, 255); 
  delay(700);
}
//////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
for(int i = 4;i<=11;i++)
{
  pinMode(i, OUTPUT);
}
  pinMode(echo, INPUT);

  Serial.begin(9600); //Start Connection with Bluetooth
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Distance = ");
  lcd.setCursor(0, 1);
  lcd.print("Mode = ");
}
void loop() {
  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  time = pulseIn(echo, HIGH);
  distance = (time/2) * 0.0343;
  lcd.setCursor(11, 0);
  lcd.print(distance);
  lcd.print(" cm = ");
  if(distance <= 20)
     {
      stop();
      hold();
      stop();
     }

  if(Serial.available() > 0)
  {
    char option = Serial.read();
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    time = pulseIn(echo, HIGH);
    distance = (time/2) * 0.0343;
    lcd.setCursor(11, 0);
    lcd.print(distance);
    lcd.print(" cm = ");
    if(option == 'F')
    {
     forward();
     lcd.setCursor(7, 1);
     lcd.print("Forward  ");
     lcd.setCursor(11, 0);
     lcd.print(distance);
     lcd.print(" cm = ");
     if(distance <= 20){
      stop();
      hold();
      option = 'S';
     }
    }
    else if(option == 'B'){
     backward();
     lcd.setCursor(7, 1);
     lcd.print("Backward  ");
     lcd.setCursor(11, 0);
     lcd.print(distance);
     lcd.print(" cm = ");
      if(distance <= 20)
      {
      stop();
      hold();
      option = 'S';
      }
    }
    else if(option == 'R'){
    right();
    lcd.setCursor(7, 1);
    lcd.print("Right    ");
    lcd.setCursor(11, 0);
    lcd.print(distance);
    lcd.print(" cm = ");
     if(distance <= 20)
     {
      stop();
      hold();
      option = 'S';
     }
    }
    else if(option == 'L'){
    left();
    lcd.setCursor(7, 1);
    lcd.print("Left    ");
    lcd.setCursor(11, 0);
    lcd.print(distance);
    lcd.print(" cm = ");
     if(distance <= 20)
     {
      stop();
      hold();
      option = 'S';
     }
    }
    else if(option == 'S'){
    stop();
    lcd.setCursor(7, 1);
    lcd.print("Stop    ");
    lcd.setCursor(11, 0);
    lcd.print(distance);
    lcd.print(" cm = ");
    }
  }
}
