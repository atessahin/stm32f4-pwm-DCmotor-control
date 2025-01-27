# stm32f4-pwm-DCmotor-control
# STM32F4 PWM Motor Control  A simple and efficient DC motor control implementation using STM32F4 microcontroller with PWM output. The project demonstrates speed control of a DC motor using a BC547 transistor and protection diode (1N4001).

## Features
- PWM signal generation using Timer2
- Variable speed control with different duty cycles
- Smooth acceleration and deceleration
- Hardware protection with flyback diode
- Uses PA1 pin for PWM output

## Hardware Components
- STM32F4 microcontroller
- BC547 NPN transistor
- 1N4001 protection diode
- 220Ω resistor
- DC motor
- Breadboard and connecting wires

## Software Implementation
- Timer2 configured for 20 kHz PWM generation
- PWM frequency optimized for motor control

## Connections
- BC547 Transistor Connections:
- Emitter Pin (E): Connected to GND
- Base Pin (B): Connected to GPIO through 220Ω resistor
- Collector Pin (C): Connected to motor and diode
  
- 1N4001 Diode:
- Cathode: Connected to motor's positive terminal
- Anode: Connected to transistor's collector pin

- DC Motor:
- Negative terminal: Connected to transistor's collector
- Positive terminal: Connected to power supply through diode

  
- The 1N4001 diode acts as a flyback diode to protect the transistor from voltage spikes when the motor turns off. The BC547 transistor acts as a switch, controlled by the GPIO signal through the 220Ω current-limiting resistor.
