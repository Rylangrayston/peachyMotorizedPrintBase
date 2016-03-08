//#include "Arduino.h"
boolean runPrint = false;
int dripCount = 0; 
int dripsPerSecond = 10;


unsigned long  delayPerDrip = 1000000 * 1/dripsPerSecond;
#include "Flager.h"
#include "stepper.h"


int pulsesPerDrip = 20;

int dripPin = 9;

float microMetersPerDrip = 10; 
float microMetersPerStep = 12.7;

unsigned long calculateHeigthFromDrips()
{
  float currentHeight = dripCount * microMetersPerDrip;
  float currentStepPos = currentHeight/microMetersPerStep + stepperHomePos + upperLimitOffset;
  return currentStepPos; 
}
  


////////////////////////////////////////////////////////////////////////////

void printStatus()
{
 Serial.print("current Position: ");
 Serial.println(stepperCurrentStepPos);
 
 Serial.print("target Position: ");
 Serial.println(stepperTargetStepPos);
 
 Serial.print("steps left to do: ");
 Serial.println( stepperCurrentStepPos - stepperTargetStepPos);
 
 Serial.print("startUp state: ");
 Serial.println(startUp); 
 
 Serial.print("upper limit offset: ");
 Serial.println(upperLimitOffset);
 
 Serial.print("analog read: ");
 Serial.println(analogRead(A0)); 
 
 Serial.print("drip count: ");
 Serial.println(dripCount);
 
 Serial.print("drips Per Second");
 Serial.println(dripsPerSecond);
 
Serial.println("stuff");
Serial.println("stuff");
Serial.println("stuff");
Serial.println("stuff");
Serial.println("stuff");
Serial.println("stuff");
Serial.println("stuff");
Serial.println("stuff");


}

void backAndForth()
{
  
  //if (stepperBusy == false )
//{
//  
//  if (lastDirection)
//{ stepperTargetStepPos -=1000;
//lastDirection = !lastDirection;
//}
//
//  else 
//{ stepperTargetStepPos +=1000;
//lastDirection = !lastDirection;
//}
//}

}

void serialEvent() {
while (Serial.available()) {
// get the new byte:
char inChar = (char)Serial.read();
if (inChar == 'd'){
//dSPIN_Move(FWD, 200.0 * microStepsPerStep);
Serial.println(inChar);
inChar = '`';
}
if (inChar == 'u'){
//dSPIN_Move(REV, 10000.0 * microStepsPerStep);
Serial.println(inChar);
inChar = '`';
}
if (inChar == 't'){
//sendDrip();
Serial.println(inChar);
inChar = '`';
}
if (inChar == 'f'){
//dripDelay -= 100;
//if (dripDelay < 1){
//dripDelay = 100;
//}
Serial.println(inChar);
inChar = '`';
}
if (inChar == 's'){
//dripDelay += 100;
Serial.println(inChar);
inChar = '`';
}
if (inChar == 'r'){
startUp = true;
Serial.println(inChar);
inChar = '`';
}
if (inChar == 'p'){
//pause = 1;
Serial.println(inChar);
inChar = '`';
}
if (inChar == 'g'){
runPrint = true;
Serial.println(inChar);
inChar = '`';
}
if (inChar == 'z'){
getStartHeight = !getStartHeight;
Serial.println(inChar);
inChar = '`';
//stir();
}
}
}






///// flags ////

FlagAtFrequency stepperMotorFlager(0.0, microSecondsBetweenSteps);
boolean stepperMotorFlag = false;

FlagAtFrequency lowPriorityFlager(0.0, 200000);
boolean lowPriorityFlag = false;
boolean lastDirection = false;

FlagAtFrequency dripFlager(0.0, delayPerDrip);
boolean dripFlag = false;



void sendDrip()
{

  for (int i=0; i < pulsesPerDrip; i++)
  {
    digitalWrite(dripPin, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(0); // wait for a second
    digitalWrite(dripPin, LOW); // turn the LED off by making the voltage LOW
    delay(1); // wait for a second
  }
dripFlag = false;
dripCount++; 

stepperTargetStepPos = calculateHeigthFromDrips();
}

void setDripsPerSecond()
{
  dripsPerSecond = analogRead(A1)/ 100;
  delayPerDrip = 1000000 * 1/dripsPerSecond;  
  FlagAtFrequency dripFlager(0.0, delayPerDrip);
}


void updateHighPriorityFlags()
{
  lowPriorityFlag = lowPriorityFlager.flag();
  stepperMotorFlag = stepperMotorFlager.flag();
  dripFlag = dripFlager.flag();
}

void updateLowPriorityFlags()
{
    
}

void doHighPriorityWork()
{
  if (stepperMotorFlag){ updateStepper();}
  if (getStartHeight) {setStartHeight();}
  if (dripFlag && runPrint && !stepperBusy) { sendDrip(); } 

}

void doLowPriorityWork()
{
   
  

  serialEvent();
  printStatus();
}

void setup()
{
  Serial.begin(115200);
  pinMode(12,INPUT_PULLUP); 
}





void loop()
{
  if (startUp) 
  {
   findUpperLimit(); 
  }
  
  updateHighPriorityFlags();
  doHighPriorityWork();

  if (lowPriorityFlag && !stepperBusy)
  {
    updateLowPriorityFlags();
    doLowPriorityWork();
    setDripsPerSecond();
    lowPriorityFlag = false;
  } 
}
  
  
  



  
  
  

  
  
  
  
  
