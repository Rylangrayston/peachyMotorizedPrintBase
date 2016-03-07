//#include "Arduino.h"
#include "Flager.h"
#include "stepper.h"

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
//pause = 0;
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



void updateHighPriorityFlags()
{
  lowPriorityFlag = lowPriorityFlager.flag();
  stepperMotorFlag = stepperMotorFlager.flag();
}

void updateLowPriorityFlags()
{
  
}

void doHighPriorityWork()
{
  if (stepperMotorFlag){ updateStepper();}
  if (getStartHeight) {setStartHeight();}

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
    
    lowPriorityFlag = false;
  } 
}
  
  
  



  
  
  

  
  
  
  
  
