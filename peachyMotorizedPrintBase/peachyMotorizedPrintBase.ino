class FlagAtFrequency
{
  float flagFrequency;
  unsigned long microSecondsBetweenFlags; 
  //unsigned long timeOfLastFlag;
  unsigned long timeOfNextFlag;
  int timesCalledSinceLastFlag;
  int timesCalledBetweenFlags;
  unsigned long totalFlagsSet;
  unsigned long currentMicroSeconds;

  public:
  FlagAtFrequency(float frequency, unsigned long microSeconds) 
  {
    flagFrequency = frequency;
    microSecondsBetweenFlags = microSeconds;
    currentMicroSeconds = micros(); 
    //timeOfLastFlag = currentMicroSeconds;
    timeOfNextFlag = 0;
    timesCalledSinceLastFlag = 0;
    timesCalledBetweenFlags = 0;
    totalFlagsSet = 0;
  }
  
  boolean flag()
  {
    unsigned long currentMicroSeconds = micros();
    if (currentMicroSeconds >= timeOfNextFlag)
    {
      timeOfNextFlag += microSecondsBetweenFlags;
      timesCalledBetweenFlags = timesCalledSinceLastFlag;
      timesCalledSinceLastFlag = 0;
      totalFlagsSet += 1;
      Serial.println(timeOfNextFlag);
      
      return true;
    }
    else{return false;}
      
  }
 int callsPerFlag()
 {
   return timesCalledBetweenFlags;
 }
 
 unsigned long totalFlags()
 {
   return totalFlagsSet;
 }
 
};





////////////////////////////////////////////////////////////////////////////
int microSecondsBetweenSteps = 4000;
unsigned long currentMicros = micros();
unsigned long timeOfLastStep;
unsigned long timeOfNextStep;
boolean stepperBusy = false;
int updateStepperCallsPerStepCount = 0;
int updateStepperCallsPerStep = 0;
boolean stepperDirection = true;

// pins
#define upperLimitPin 12
#define DOWN  true
#define UP  false 

#define stepperCoil1Pin  2
#define stepperCoil2Pin  3
#define stepperCoil3Pin  4
#define stepperCoil4Pin  5

unsigned long stepperCurrentStepPos = 0; 
unsigned long stepperTargetStepPos = 0;






void updateStepper(){
//  currentMicros = micros();
//  if (currentMicros - timeOfLastStep >= timeOfNextStep)
//  {
//    timeOfLastStep = currentMicros;
//    timeOfNextStep = timeOfLastStep + microSecondsBetweenSteps;
//    updateStepperCallsPerStep = updateStepperCallsPerStepCount;
//    updateStepperCallsPerStepCount = 0;
    
  
    if (stepperCurrentStepPos < stepperTargetStepPos)
    {
      stepperDirection = DOWN;
      stepperBusy = true;
      
    }
    
    else if (stepperCurrentStepPos > stepperTargetStepPos)
    {
      stepperDirection = UP;
      stepperBusy = true;
      
    }
    
    else 
    {
      stepperBusy = false;
    }    
  
  
//  }
//  updateStepperCallsPerStepCount++; 
}












///// flags ////

FlagAtFrequency stepperMotorFlager(0.0, microSecondsBetweenSteps);
boolean stepperMotorFlag = false;

FlagAtFrequency lowPriorityFlager(0.0, 1000000);
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
  } 
}
  
  
  



  
  
  

  
  
  
  
  
