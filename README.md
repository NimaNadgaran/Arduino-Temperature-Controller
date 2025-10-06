# Arduino Temperature Controller 

## Overview

This project is an **automated temperature control system** using **Arduino**. It allows users to set a target temperature and time, then automatically regulates the temperature using a heating and cooling process. The system uses a **MAX6675** thermocouple sensor for temperature measurement and an **LCD display** for user interaction.

## Features

- Set and control **target temperature**
- Set a **countdown timer** for heating/cooling cycles
- **LCD Display** interface for user interaction
- **Push-button navigation** for setting values
- **Temperature sensing** using MAX6675 & DS18B20 sensors
- **Relay control** for heating and cooling elements
- **State-based process** for better efficiency

## Components Required

- **Arduino Board** (e.g., Uno, Mega, etc.)
- **16x2 LCD Display** (with I2C or parallel connection)
- **MAX6675 Thermocouple Sensor**
- **DS18B20 Temperature Sensor**
- **Push Buttons** for navigation
- **Relay Module** for switching heating/cooling elements
- **Power Supply** for the relay and Arduino

## Circuit Diagram

(Include an image of the circuit diagram if available)

## How It Works

1. **Power on** the system.
2. Use the **buttons** to set the desired temperature and time.
3. The **heating element** activates until the target temperature is reached.
4. The system **maintains** the temperature for the set duration.
5. After heating, the **cooling process** begins (if needed).
6. The system **displays** the countdown timer and updates the temperature live.
7. When the countdown reaches zero, the system **turns off** the heating/cooling element.

## Code Breakdown

The code consists of:

- **Setup**: Initializes LCD, sensors, and relay pins.
- **User Input Handling**: Reads button presses to configure settings.
- **Temperature Reading**: Continuously reads data from MAX6675.
- **State Machine**:
  - **Heating Process**: Activates heating if the temperature is below the set value.
  - **Cooling Process**: Turns off heating and allows cooling when required.
- **Countdown Timer**: Updates and displays the remaining time.

## Installation & Usage

1. Clone the repository:
   ```sh
   git clone https://github.com/NimaNadgaran/Arduino-Temperature-Controller.git
   ```
2. Open the code in **Arduino IDE**.
3. Connect the Arduino to your computer via USB.
4. Select the correct **Board** and **Port**.
5. Upload the code to the Arduino.
6. Connect the components as per the circuit diagram.
7. Power up the system and start using it.

## License

This project is open-source under the **MIT License**.

## Author

Nima Nadgaran - https://github.com/NimaNadgaran
www.linkedin.com/in/nima-nadgaran


