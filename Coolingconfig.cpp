#include "typewise-alert.h"

// Cooling configuration limits
#define PASSIVE_COOLING_LOWER_LIMIT 0
#define PASSIVE_COOLING_UPPER_LIMIT 35
#define HI_ACTIVE_COOLING_UPPER_LIMIT 45
#define MED_ACTIVE_COOLING_UPPER_LIMIT 40

// Static array of cooling configurations
static const CoolingConfig coolingConfigs[] = {
    {PASSIVE_COOLING, PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT},
    {HI_ACTIVE_COOLING, PASSIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT},
    {MED_ACTIVE_COOLING, PASSIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT},
};

// Infer the breach type based on limits
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if (value < lowerLimit) {
    return TOO_LOW;
  }
  if (value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

// Get cooling configuration based on cooling type
CoolingConfig getCoolingConfig(CoolingType coolingType) {
  for (int i = 0; i < sizeof(coolingConfigs) / sizeof(coolingConfigs[0]); ++i) {
    if (coolingConfigs[i].coolingType == coolingType) {
      return coolingConfigs[i];
    }
  }
  return coolingConfigs[0];  // Default to PASSIVE_COOLING if not found
}

// Classify temperature breach based on cooling type
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  CoolingConfig config = getCoolingConfig(coolingType);
  return inferBreach(temperatureInC, config.lowerLimit, config.upperLimit);
}
