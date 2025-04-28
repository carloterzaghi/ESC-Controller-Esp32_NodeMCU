# ESC Controller Using ESP32-NodeMCU

## Overview
This project implements an Electronic Speed Controller (ESC) for a BLDC motor using an ESP32-NodeMCU. The controller utilizes Hall effect sensors to detect rotor position and MOSFETs for motor phase switching. The provided code (`main.cpp`) handles motor control through hardware timers and interrupts, ensuring efficient and precise operation.

## Features
- Controls a BLDC motor with Hall effect sensors.
- Uses ESP32 hardware timers for precise motor phase switching.
- Drives motor phases using MOSFETs (TC4427A drivers).
- Supports 36V input with step-down to 15V and 5V for ESP32 operation.
- PCB design included (Gerber files available in the project directory).

## Hardware Requirements
- **ESP32-NodeMCU**: Main microcontroller for motor control.
- **BLDC Motor with Hall Sensors**: For rotor position feedback.
- **TC4427A MOSFET Drivers**: To drive the MOSFETs (IRFP3055 and MUR460).
- **LM2596 Modules**: For stepping down 36V to 15V and 5V.
- **Power Supply**: 36V input for motor operation.
- **Connectors**: For motor phases (A, B, C) and Hall sensors (H1, H2, H3).

## Pin Configuration
- **Hall Sensors**:
  - HALL1: GPIO 32
  - HALL2: GPIO 33
  - HALL3: GPIO 25
- **MOSFET Outputs**:
  - MOSFET1: GPIO 26
  - MOSFET2: GPIO 27
  - MOSFET3: GPIO 14
  - MOSFET4: GPIO 12
  - MOSFET5: GPIO 13
  - MOSFET6: GPIO 15

## Schematic and PCB
- **Schematic**: The schematic diagram is provided below. It includes the ESP32-NodeMCU, MOSFET drivers, Hall sensor connections, and power supply circuits.

  <div style="text-align: center;">
    <img src="schematic.png" alt="Schematic Diagram">
    </br></br>
  </div>

- **PCB Layout**: The PCB layout is shown below, matching the schematic with labeled connections for easy assembly. Gerber files are also available in the project directory for manufacturing.

  <div style="text-align: center;">
    <img src="pcb_layout.png" alt="PCB Layout">
  </div>


## Usage
1. Assemble the circuit as per the schematic or use the provided PCB.
2. Connect the BLDC motor and Hall sensors to the appropriate pins.
3. Power the circuit with a 36V supply.
4. The ESP32 will automatically start controlling the motor based on Hall sensor feedback.

## Notes
- Ensure proper grounding (GND_36V, GND_15V, GND_5V, GND_ESP32) to avoid noise issues.
- The code uses interrupts for Hall sensor readings and timers for MOSFET switching, ensuring real-time performance.
- Adjust the timer interval (`timerAlarmWrite`) in the code if you need to change the motor control frequency.