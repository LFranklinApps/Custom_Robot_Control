/*
  Custom_Robot_Control.h - Library for communicating with the Custom Robot Control app over Bluetooth.
  Created by L. Franklin, July 15, 2025.
  Updated by L. Franklin, July 15, 2025.
*/

#ifndef Custom_Robot_Control_h
#define Custom_Robot_Control_h

#include "Arduino.h"
#include "ArduinoBLE.h"


class Custom_Robot_Control
{
  public:
    Custom_Robot_Control();
    bool begin();
    bool loop();
    bool isConnected();
    bool write(int index, int value);
    int read(int index);
    bool isUpdated(int index);
  private:
      bool readBuffer();
      bool writeBuffer();
      int _pin;
      String _name;
      int intArray[128];
      int intArrayWritten[128];




};

#endif

