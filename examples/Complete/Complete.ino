// This library is designed to accompany the Custom Robot Control app.
// Alternative third-party software for advanced users includes LightBlue® for mobile devices.
// Advanced users are also encouraged to develop their own mobile applications to use with this library.

#include "Custom_Robot_Control.h"

Custom_Robot_Control controller;

void setup() {
  Serial.begin(9600);
  
  // Start the Bluetooth® Low Energy controller
  controller.begin();
}

void loop() {

  // Must be called as often as possible; does essential background work
  controller.loop();

  // Only updates values if the app is connected
  if(controller.isConnected()){
    
    // Checks if index 0 of the Bluetooth® array is updated; prints the updated value
    if(controller.isUpdated(0))
      Serial.println("New Value: " + String(controller.read(0)));
    
    // Writes the number of uptime seconds to index 127 (the highest index) of the Bluetooth® array
    controller.write(127, (int)(millis() / 1000UL));
  
  }

}
