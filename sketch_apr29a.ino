//For BUZZER put this code in Arduino IDE
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 4, TXPin = 3;
const int irSensorPin = 5;
int sensorValue = 0;
SoftwareSerial mySerial(9, 10);
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
int LED = 12;
int BUZZER = 11;
int ALCOHOL_sensor = 2;// MQ-3 SENSOR
int ALCOHOL_detected;
#define Motor 8
void setup()
{
  ss.begin(9600);
  mySerial.begin(9600);
  
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(Motor, OUTPUT);
  pinMode(ALCOHOL_sensor, INPUT);
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT);    // Set the IR sensor pin as input   
}
void loop()
{

  sensorValue = digitalRead(irSensorPin);  // Read the sensor value
//  Serial.println(sensorValue);
  if (sensorValue == HIGH) {
    // If an object is detected, activate the BUZZER
    digitalWrite(BUZZER, LOW);
    Serial.println("No Drowsiness detected");
  } else {
    // If no object is detected, turn off the BUZZER
    digitalWrite(BUZZER, HIGH);
    Serial.println("Drowsiness detected");
  }

  delay(500);  // Delay for 500 milliseconds
  ALCOHOL_detected = digitalRead(ALCOHOL_sensor);
//  Serial.println(ALCOHOL_detected);
  if (ALCOHOL_detected == 0)
  {
    Serial.println("ALCOHOL detected...");
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    digitalWrite(Motor, LOW);
    calling();
       
      
    delay(500);

    
    SendMessage();
    
  }
  else
  {
    Serial.println("No ALCOHOL detected.");
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
    digitalWrite(Motor, HIGH);
  }

}

void SendMessage()
{
  Serial.println("sending message.....");
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+919561350729\"\r");
  delay(1000);



  mySerial.println("Alcohol has been consumed \n REACH AS SOON AS POSSIBLE \n ");
  
  mySerial.print("Latitude: ");
  mySerial.print(gps.location.lat(),6);
  mySerial.print("\n Longitude: ");
  mySerial.println(gps.location.lng(),6);
  


  mySerial.print("https://www.google.com/maps/@");
  mySerial.print(gps.location.lat(),6);
  mySerial.print(',');
  mySerial.print(gps.location.lng(),6);
  mySerial.print(",14z");



  delay(100);
  mySerial.println((char)26);
  delay(1000);

}
void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}

void calling(){
  Serial.println("calling........");
    delay(500);

    mySerial.println("AT");
    updateSerial();

    mySerial.println("ATD+ +919561350729;");
    updateSerial();
    delay(10000);
    mySerial.println("ATH"); 
    updateSerial();

  }
