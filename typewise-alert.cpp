#include "typewise-alert.h"

// Alert function mappings
static const AlertMapping alertMappings[] = {
  {TO_CONTROLLER, sendToController},
  {TO_EMAIL, sendToEmail}
};

// Check and alert based on target and battery character
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  for (int i = 0; i < sizeof(alertMappings) / sizeof(alertMappings[0]); ++i) {
    if (alertMappings[i].target == alertTarget) {
      alertMappings[i].alertFunc(breachType);
      break;
    }
  }
}
