//#include "Arduino.h"
#include "Flager.h"
#include "stepper.h"

////////////////////////////////////////////////////////////////////////////

void printStatus()
{
 Serial.println(stepperCurrentStepPos);
 Serial.println(stepperTargetStepPos);
 Serial.println(stepperCurrentStepPos - stepperTargetStepPos); 
}


///// flags ////

FlagAtFrequency stepperMotorFlager(0.0, microSecondsBetweenSteps);
boolean stepperMotorFlag = false;

FlagAtFrequency lowPriorityFlager(0.0, 200000);
boolean lowPriorityFlag = false;





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
  if (stepperBusy == false){ stepperTargetStepPos +=0;}
  printStatus();
}

void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  updateHighPriorityFlags();
  doHighPriorityWork();

  if (lowPriorityFlag)
  {
    updateLowPriorityFlags();
    doLowPriorityWork();
    
    lowPriorityFlag = false;
  } 
}
  
  
  



  
  
  

  
  
  
  
  
