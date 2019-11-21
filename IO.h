#pragma once
#include "Arduino.h"
#include <esp_system.h>

/**
 * 
 * @author Mikko Tekoniemi 
 * 
 */
class IO {
public:
    int pin;
    bool output;
    bool state;
    IO(int pin, bool output);
    IO(int pin, bool output, bool state);
    void changeState();
    String toStr();
};