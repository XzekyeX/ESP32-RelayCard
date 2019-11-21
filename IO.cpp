#include "IO.h"
IO::IO(int pin, bool output, bool state)
{
    this->pin = pin;
    this->output = output;
    this->state = state;
    pinMode(this->pin, this->output ? OUTPUT : INPUT);
    digitalWrite(this->pin, this->state ? HIGH : LOW);
}

IO::IO(int pin, bool output)
{
    this->pin = pin;
    this->output = output;
    this->state = false;
    pinMode(this->pin, this->output ? OUTPUT : INPUT);
    digitalWrite(this->pin, this->state ? HIGH : LOW);
}

void IO::changeState()
{
    this->state = !this->state;
    digitalWrite(this->pin, this->state ? HIGH : LOW);
}

String IO::toStr()
{
    String value;
    value += "io[";
    value += this->pin;
    value += ",";
    value += this->state;
    value += ",";
    value += this->output;
    value += "]";
    return value;
}