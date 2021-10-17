
////////////////
//Assignment 8//
////////////////
//22546448@sun.ac.za
//22546448
//Michiel Christiaan van der Berg


#define SupplyVoltagePin   A0
#define LightSensorPin     A1
#define BatteryVoltagePin  A2
#define BatteryCurrentPin  A9
#define ChargeOnPin        9


//global variables
String readFromSerial;
String turnOn = "OV1";
String turnOff = "OV0";
String request = "data";

bool OCproc ;
float BatteryVoltage ;
float SupplyVoltage ;
float BatteryCurrent;
float LightSensor ;

//timer variables
const int timerInterval = 1000;
unsigned int lastTime = 0;


void setup() {
  Serial.begin(115200);
  pinMode(ChargeOnPin, OUTPUT);
  pinMode(SupplyVoltagePin, INPUT);
  pinMode(LightSensorPin, INPUT);
  pinMode(BatteryVoltagePin, INPUT);
  pinMode(BatteryCurrentPin, INPUT);
}


void loop() {
  int timeNow = millis();
  //Run every 1 second
  if (timeNow - lastTime >= timerInterval)
  {
    SerialString();
    lastTime = timeNow;
  }
  if(Serial.available() > 0)
  {
    SerialFunction();
  }
}

void SerialFunction()
{
  readFromSerial = Serial.readStringUntil('\n');
  readFromSerial.trim();
  if(readFromSerial.equals(turnOn))
  {
    if(BatteryVoltage < 7.2)
    {
    digitalWrite(ChargeOnPin, HIGH);
    }
  }
  else if(readFromSerial.equals(turnOff))
  {
    digitalWrite(ChargeOnPin, LOW);
  }
  else if(readFromSerial.equals(request))
  {
    void SerialString();
  }
  else
  {
    Serial.println("Input Error");
  }
  if(!(BatteryVoltage < 7.2)&&(digitalRead(ChargeOnPin) != LOW) )
  {
    digitalWrite(ChargeOnPin, LOW);
  }
}

void SerialString()
{
OCproc = digitalRead(ChargeOnPin);
BatteryVoltage = analogRead(BatteryVoltagePin)*5/(float)1023 + 5.3;
SupplyVoltage = analogRead(SupplyVoltagePin)*22/(float)1023 + 0.3;
BatteryCurrent = 0.5865*analogRead(BatteryCurrentPin)-150;
LightSensor = (analogRead(LightSensorPin)*5/(float)1023 - 1)*100/3.8;


String output = "";
output += OCproc;
output += ',';
output += BatteryVoltage;
output += ',';
output += SupplyVoltage;
output += ',';
output += BatteryCurrent;
output += ',';
output += LightSensor;

Serial.println(output); 
}
