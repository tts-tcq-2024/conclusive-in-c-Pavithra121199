#include "typewise-alert.h"
#include <stdio.h>

// Send alert to controller
void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

// Send alert via email
void sendToEmail(BreachType breachType) {
  const char* recipient = "a.b@c.com";
  printf("To: %s\n", recipient);

  const char* messages[] = {
    "Hi, the temperature is too low\n",
    "Hi, the temperature is too high\n"
  };

  if (breachType != NORMAL) {
    printf("%s", messages[breachType - 1]);
  }
}
