
////////////////
//Assignment 9//
////////////////
//22546448@sun.ac.za
//22546448
//Michiel Christiaan van der Berg


#define SupplyVoltagePin   A0
#define LightSensorPin     A1
#define BatteryVoltagePin  A2
#define BatteryCurrentPin  A10
#define PWMpin              9
#define ChargeOnPin        11



//global variables
String readFromSerial;
String turnOn = "OV1";
String turnOff = "OV0";
String request = "data";

bool charge ;
float  PWM;
float BatteryVoltage ;
float SupplyVoltage ;
float BatteryCurrent;
float LightSensor ;



//timer variables
unsigned int prevTime = 0;


void setup() {
  Serial.begin(115200);
  pinMode(ChargeOnPin, OUTPUT);
  pinMode(PWMpin,OUTPUT);
  pinMode(SupplyVoltagePin, INPUT);
  pinMode(LightSensorPin, INPUT);
  pinMode(BatteryVoltagePin, INPUT);
  pinMode(BatteryCurrentPin, INPUT);
  
}


void loop() {
  int currentTime = millis();
  //Run every 1 second
  if (currentTime - prevTime >= 1000)
  {
    SerialString();
    prevTime = currentTime;
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
    charge = HIGH;
    digitalWrite(ChargeOnPin, charge);
    
    
  }
  else if(readFromSerial.equals(turnOff))
  {
    charge = LOW;
    digitalWrite(ChargeOnPin, charge);
  }
  else
  {
    PWM = (int)(255*((float)((readFromSerial[0] - 48 - 1)*100 + (readFromSerial[1] - 48)*10 + (readFromSerial[2] - 48)))/100);
  }
  if(!(BatteryVoltage < 7.2)&&(digitalRead(ChargeOnPin) != LOW) )
  {
    digitalWrite(ChargeOnPin, LOW);
  }
}

void SerialString()
{
charge = digitalRead(ChargeOnPin);
BatteryVoltage = analogRead(BatteryVoltagePin)*5/(float)1023 + 4.3;
SupplyVoltage = analogRead(SupplyVoltagePin)*22/(float)1023 + 0.3;
BatteryCurrent = 0.5865*analogRead(BatteryCurrentPin)-150;
LightSensor = ((analogRead(LightSensorPin)*5/(float)1023 -0.5)/3.5)*100 ;
if (LightSensor <= 0){
  LightSensor = 0;
}
else if (LightSensor >= 100){
  LightSensor = 100;
}
analogWrite(PWMpin,PWM);


String output = "";
output += charge;
output += ',';
output += BatteryVoltage;
output += ',';
output += SupplyVoltage;
output += ',';
output += BatteryCurrent;
output += ',';
output += LightSensor;
output += ',';
output += PWM;

Serial.println(output); 
}
