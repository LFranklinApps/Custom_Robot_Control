#include "Custom_Robot_Control.h"

Custom_Robot_Control controller;

void setup() {
  controller.begin(); // Start the Bluetooth® Low Energy controller
}

void loop() {
  controller.loop(); // Must be called as often as possible; does essential background work
}
