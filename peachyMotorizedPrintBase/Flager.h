#include "Arduino.h"

/*
  Flager.h lets you creat flager objecst which will return true as
  often as you set them to, its a nice way keep the variabls 
  used in the blink without delay example hiden. It basicaly lets you 
  multi task with a bit more ease.
 */

class FlagAtFrequency
{
  float flagFrequency;
  unsigned long microSecondsBetweenFlags; 
  //unsigned long timeOfLastFlag;
  unsigned long timeOfNextFlag;
  unsigned long timesCalledSinceLastFlag;
  unsigned long timesCalledBetweenFlags;
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
      //Serial.println(timeOfNextFlag);
      
      return true;
    }
    else
    {
      timesCalledSinceLastFlag += 1;
      return false; 
    }
      
  }
 unsigned long callsPerFlag()
 {
   return timesCalledBetweenFlags;
 }
 
 unsigned long totalFlags()
 {
   return totalFlagsSet;
 }
 
};


