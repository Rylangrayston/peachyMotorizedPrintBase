#include "Arduino.h"

    /*
       BYJ48 Stepper motor code
       Connect :
       IN1 >> D8
       IN2 >> D9
       IN3 >> D10
       IN4 >> D11
       VCC ... 5V Prefer to use external 5V Source
       Gnd
       written By :Mohannad Rawashdeh
      http://www.instructables.com/member/Mohannad+Rawashdeh/
         28/9/2013
      */

    #define IN1  2
    #define IN2  3
    #define IN3  4
    #define IN4  5

int microSecondsBetweenSteps = 800;
unsigned long currentMicros = micros();
unsigned long timeOfLastStep;
unsigned long timeOfNextStep;
boolean stepperBusy = false;
int updateStepperCallsPerStepCount = 0;
int updateStepperCallsPerStep = 0;
boolean Direction = true;
unsigned long resinStartHeight = 3000;


// pins
#define upperLimitPin 12
#define DOWN  true
#define UP  false 

unsigned long stepperHomePos = 5000000;    
unsigned long stepperCurrentStepPos = 5000000; 
unsigned long stepperTargetStepPos = 5000000;
unsigned long homePos = stepperCurrentStepPos;
int Steps = 0;
int pos = 0;
boolean startUp = true;
int moveAwayFromLimitSwitchSteps = 300;
int setHeightPotFactor = 1;
int upperLimitOffset = (analogRead(A0) * setHeightPotFactor) + moveAwayFromLimitSwitchSteps;

boolean getStartHeight = false;



void setStartHeight()
{ 
    int oldUpperLimitOffset = upperLimitOffset;
    upperLimitOffset = (analogRead(A0) * setHeightPotFactor) + moveAwayFromLimitSwitchSteps;
    stepperTargetStepPos +=   upperLimitOffset - oldUpperLimitOffset  ;
}
     
 
void resetHomePos()
{
  stepperHomePos = 5000000;    
  stepperCurrentStepPos = 5000000; 
  stepperTargetStepPos = 5000000;  
}
     
void findUpperLimit()
{
  //Serial.println(digitalRead(12));
  if (digitalRead(12) == HIGH ){
  
  if (!stepperBusy) {stepperTargetStepPos -= 1;}
  }
  else
  {
    resetHomePos();
    setStartHeight();
    stepperTargetStepPos += upperLimitOffset;
    startUp = false;
    //while(true){}
  }
}
  
  
//  }
//  updateStepperCallsPerStepCount++; 

////////////////////////////////////////////////////////////// 
    
//void updateStepper(){
//  if (steps_left > 0)
//  {
//    stepper(1); 
//    steps_left--;
//    stepperBusy = true;
//  }
//  else{stepperBusy = false;}
//}
    
    void SetDirection(){
    if(Direction==true){ Steps++; pos++;}
    if(Direction==false){ Steps--; pos--;}
    if(Steps>7){Steps=0;}
    if(Steps<0){Steps=7; }
    } 
    

    void stepper(int xw){
      for (int x=0;x<xw;x++){
    switch(Steps){
       case 0:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       case 1:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, HIGH);
       break; 
       case 2:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 3:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 4:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 5:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
         case 6:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 7:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       default:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
    }
    
    
    SetDirection();
    }
    } 
    
    

    
    
    void updateStepper(){
    if (stepperCurrentStepPos < stepperTargetStepPos)
    {
      Direction = DOWN;
      stepperBusy = true;
      stepper(1);
      stepperCurrentStepPos += 1;
    }
    
    else if (stepperCurrentStepPos > stepperTargetStepPos)
    {
      Direction = UP;
      stepperBusy = true;
      stepper(1);
      stepperCurrentStepPos -= 1;
      
    }
    
    else 
    {
      stepperBusy = false;
    }    
    }

