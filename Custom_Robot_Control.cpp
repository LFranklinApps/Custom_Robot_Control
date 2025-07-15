/*
  Custom_Robot_Control.cpp - Library for communicating with the Custom Robot Control app over Bluetooth.
  Created by L. Franklin, July 15, 2025.
  Updated by L. Franklin, July 15, 2025.
*/

#include "Arduino.h"
#include "ArduinoBLE.h"
#include "Custom_Robot_Control.h"

BLEService mainService("F84ECD8E-FC73-434E-907D-61E3C3F063A4");
BLECharacteristic mainCharacteristic("E03B819E-3A13-405D-A6BA-2F4D6523AC28", BLERead | BLEWrite | BLEIndicate | BLENotify, 512, true);


Custom_Robot_Control::Custom_Robot_Control()
{
}

bool Custom_Robot_Control::begin()
{
  pinMode(_pin, OUTPUT);

  if (!BLE.begin()) {
      return false;
  }
  BLE.setLocalName("Custom Robot Control");
  BLE.setAdvertisedService(mainService);
  mainService.addCharacteristic(mainCharacteristic);
  BLE.addService(mainService);
  if(!mainCharacteristic.writeValue((const byte*)intArray, 512)) return false;
  if(!BLE.advertise()) return false;
  delay(800);
  return true;
}

bool Custom_Robot_Control::loop()
{
    BLE.poll();
    if (!BLE.advertise()) return false;
    return true;
}

bool Custom_Robot_Control::isConnected() {
    return BLE.connected();
}

bool Custom_Robot_Control::readBuffer()
{
    if (mainCharacteristic.readValue((void*)(const byte*)intArray, 512) != 512) return false;
    return true;
}

bool Custom_Robot_Control::writeBuffer()
{
    if (!mainCharacteristic.writeValue((const byte*)intArray, 512)) return false;
    return true;
}

bool Custom_Robot_Control::write(int index, int value)
{
    if (index < 0) return false;
    if (index >= 128) return false;
    if (!readBuffer()) return false;
    intArray[index] = value;
    if (!writeBuffer()) return false;
    return true;
}

// reads from a location (index) and returns -1 for errors (note that -1 can be written to the location, so it does not always signal an error)
int Custom_Robot_Control::read(int index)
{
    if (index < 0) return -1;
    if (index >= 128) return -1;
    if (!readBuffer()) return -1;
    return intArray[index];
}

// Returns whether a new value has been written (by either client or server) since the last call to this function.
// Writing the same value again is not considered a write. Errors return false. 
bool Custom_Robot_Control::isUpdated(int index)
{
    if (index < 0) return false;
    if (index >= 128) return false;
    if (!readBuffer()) return false;
    bool written = (intArray[index] != intArrayWritten[index]);
    intArrayWritten[index] = intArray[index];
    return written;
}
