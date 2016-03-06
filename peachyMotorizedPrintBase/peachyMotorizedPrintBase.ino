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
  currentMicros = micros();
  if (currentMicros - timeOfLastStep >= timeOfNextStep)
  {
    timeOfLastStep = currentMicros;
    timeOfNextStep = timeOfLastStep + microSecondsBetweenSteps;
    updateStepperCallsPerStep = updateStepperCallsPerStepCount;
    updateStepperCallsPerStepCount = 0;
    
  
    if (stepperCurrentStepPos < stepperTargetStepPos)
    {
      stepperDirection = DOWN;
      stepperBusy = true;
      
    }
    
    if (stepperCurrentStepPos > stepperTargetStepPos)
    {
      stepperDirection = UP;
      stepperBusy = true;
      
    }
    
    if (stepperCurrentStepPos == stepperTargetStepPos)
    {
      stepperBusy = false;
    }    
  
  
  }
  updateStepperCallsPerStepCount++; 
}

void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  
}
  
  
  
  
  
  
