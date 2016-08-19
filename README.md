Airconditioning Remote Control
==============================

Based on the ESP8266 Board

IR LED connected to Pin 14 (D5 on NodeMcu)

Uses MQTT to receive a JSON command on the aircon/set MQTT topic.
All parameters need to be in the JSON message.

Currently nearly no abstraction of the data. So you need to send binary values for some fields instead of Strings.

```
{
    "on": true, 
    "temperature": "24" 
    "mode": 8, 
    "fan": 2,
    "timer": false, 
    "timer_value": "0", 
    "unitF": false, 
}
```

Data in the JSON Message
------------------------

on: Enable the unit

temperature: Setpoint of Airconditioning

fan: 1=high, 2=medium, 4=low

mode: 8=A/C, 2=Dehumidify, 1=Fan only

timer: Enables the timer. When unit is off it serves as the switch-on timer, if the unit is on it switches off after the interval

timer_value: Hours until the timer action (on/off) will be executed