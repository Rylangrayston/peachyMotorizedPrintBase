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

}

void doLowPriorityWork()
{
  Serial.println(stepperTargetStepPos);  
  
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
  
  
  



  
  
  

  
  
  
  
  
