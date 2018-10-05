#include <DHT.h>
#include <Wire.h> 
#include <LCD.h>
#include <LiquidCrystal.h>

///Constants///

//Temp. sensor
#define DHTPIN 13           // Temp. sensor's pin
#define DHTTYPE DHT11       // Temp. sensor model
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor for normal 16mhz Arduino

//LCD screen
#define E_pin 7     //Enable
#define Rs_pin 5    //Register select
#define D4_pin 8    //4th Data pin's pin
#define D5_pin 9    //5th Data pin's pin
#define D6_pin 10   //6th Data pin's pin
#define D7_pin 11   //7th Data pin's pin
LiquidCrystal lcd(Rs_pin, E_pin, D4_pin, D5_pin, D6_pin, D7_pin);   // Initialize LCD screen

//Components
#define buzzer 2
#define LED 3
#define flame_sensor 4

///Variables///
int flame;   //stores flame detecting statuses
float temp;           //stores temp. values

//Code starts

//Run once
void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);
  dht.begin();
  lcd.begin(16,2);
}

//Run repeatly
void loop() {
  
  //Read data and store it to variable temp
  temp = dht.readTemperature();
  
  //Print temp. values to serial monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  //Print temp. values to the LCD screen
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C");

  //Read flame detection data and store it to variable flame
  flame = digitalRead(flame_sensor);

  //Run buzzer, LED light and print to LCD when flame detected
  if (flame == 1)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
    delay(250);
    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
    delay(250);
    digitalWrite(LED, HIGH);
    delay(5);
    digitalWrite(LED, LOW);
    delay(5);

    lcd.setCursor(0,1);
    lcd.print("FLAME DETECTED!");

  }
  //Turn off buzzer and LED when flame is not detected
  else
  {
    Serial.println("No flame detected. stay cool");
    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);

    lcd.setCursor(0,1);
    lcd.print("               ");
  }
  
  delay(1000); //delay for 1 second
}
