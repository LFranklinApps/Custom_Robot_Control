# Custom Robot Control

Library for communicating with the Custom Robot Control app over Bluetooth® Low Energy (BLE).

## Description

No knowledge of Bluetooth® is necessary. This library provides an array of integers that is shared between the Arduino board and the Custom Robot Control app. Other third-party software can be used with this library as well. Supports the following boards: Arduino MKR WiFi 1010, Arduino UNO WiFi Rev2, Arduino Nano 33 IoT, Arduino Nano 33 BLE, Nicla Sense ME, and UNO R4 WiFi. Other boards may compile, but they will not function correctly with this library. 

## Minimal Example

```
#include "Custom_Robot_Control.h"

Custom_Robot_Control controller;

void setup() {
  controller.begin(); // Start the Bluetooth® Low Energy controller
}

void loop() {
  controller.loop(); // Must be called as often as possible; does essential background work
}
```

## Complete Example

```
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
```


