#include <dht.h>
#include <LiquidCrystal.h>

#define DHT11_PIN 6

dht DHT;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int trigPin = A2; 
int echoPin = A3;

int isDoorClosed() {
  long distance;
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  distance = pulseIn(echoPin, HIGH)*(0.17) ; // en millimetres
  Serial.println(distance);
  if (distance > 130) {
    return 0;
  }
  return 1;
}
 
void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Loading");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  while (isDoorClosed() == 0 ) {
    digitalWrite(13, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Door: Open");
    delay(100);
  }
  digitalWrite(13, LOW);

  
  lcd.clear();
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0);
  lcd.print("Hum = ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.print(DHT.temperature);
  lcd.print( (char)223);
  lcd.print("C");
  delay(2000);

  if (DHT.temperature > 5) {
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("Warning !");
    lcd.setCursor(0,1);
    lcd.print("Temp too high");
    delay(2000);
  }

  if (DHT.temperature == 0) {
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("Warning !");
    lcd.setCursor(0,1);
    lcd.print("Temp too low");
    delay(2000);
  }

  if (DHT.humidity < 25) {
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("Warning !");
    lcd.setCursor(0,1);
    lcd.print("Hum too low");
    delay(2000);
  }

  if (DHT.humidity > 40) {
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("Warning !");
    lcd.setCursor(0,1);
    lcd.print("Hum too High");
    delay(2000);
  }

  
}
