#include "FPSController.h"

double   FPSController::mDeltaTime = 0;
double   FPSController::mTargetFPS = 0;
double   FPSController::mLastTime{};
uint8_t FPSController::mDefaultFPS = 60;