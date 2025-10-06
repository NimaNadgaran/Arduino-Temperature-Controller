# Bio-Gel Maker Arduino Project
Overview
This Arduino project is designed to control a Bio-Gel Maker, a device that maintains a specific temperature for a set duration to facilitate the creation of bio-gel. The system uses an Arduino Mega, a 16x2 LCD display, a keypad for user input, a MAX6675 thermocouple for temperature sensing, and a relay or transistor to control an electric heater. The user can set a countdown timer and a target temperature via the keypad, and the system will maintain the temperature while displaying the remaining time and target temperature on the LCD.
Features

Countdown Timer: Allows the user to set a timer (in hours and minutes) for the bio-gel process.
Temperature Control: Uses a MAX6675 thermocouple to monitor and maintain a user-defined temperature by controlling an electric heater.
LCD Display: Shows the current status, timer, and temperature settings on a 16x2 LCD.
Keypad Input: Enables the user to adjust the countdown time and target temperature interactively.
Start/Stop Functionality: The user can start or stop the process using a specific keypad button.

Hardware Requirements

Arduino Mega: The microcontroller used to run the program.
16x2 LCD Display: Connected to display the timer, temperature, and system status.
Keypad: A 4x4 or similar analog keypad for user input (connected to analog pin A0).
MAX6675 Thermocouple Module: Used to measure the temperature of the bio-gel.
Electric Heater: Controlled via a relay or transistor connected to a digital pin.
Connecting Wires and Breadboard: For assembling the circuit.
Power Supply: Suitable for the Arduino and heater (ensure compatibility with your heater's power requirements).

Pin Configuration
```
LCD Pins:
RS: Pin 8
EN: Pin 9
D4: Pin 4
D5: Pin 5
D6: Pin 6
D7: Pin 7
```

Thermocouple (MAX6675):
```
DO (Data Out): Pin 21
CS (Chip Select): Pin 20
CLK (Clock): Pin 19
```

Heater Control: Pin 20 (digital output for controlling the heater via a relay or transistor).
Keypad: Connected to analog pin A0 (reads analog values to detect key presses).

Libraries Required

LiquidCrystal: For controlling the 16x2 LCD display. Included in the Arduino IDE by default.
MAX6675: For interfacing with the MAX6675 thermocouple module. Install via the Arduino Library Manager or download from this GitHub repository.

To install the MAX6675 library:

Open the Arduino IDE.
Go to Sketch > Include Library > Manage Libraries.
Search for "MAX6675" and install the library by Adafruit.

Installation

Connect the Hardware:

Wire the LCD, keypad, MAX6675 thermocouple, and heater to the Arduino Mega as per the pin configuration.
Ensure the thermocouple is properly connected to the bio-gel container for accurate temperature readings.
Connect the heater to a relay or transistor controlled by the specified digital pin.


Upload the Code:

Copy the provided Arduino code into the Arduino IDE.
Connect the Arduino Mega to your computer via USB.
Select Arduino Mega or Mega 2560 from Tools > Board in the Arduino IDE.
Upload the code to the Arduino.


Verify Connections:

Ensure all connections are secure and the thermocouple is correctly positioned.
Power on the Arduino and verify that the LCD displays "Bio-Gel Maker" on startup.



How It Works

Startup:

The LCD displays "Bio-Gel Maker" for 5 seconds.
The system then prompts the user to set the countdown time.


Setting the Timer:

The user can adjust the countdown time (in hours and minutes) using the keypad.
Keypad inputs (analog values):
```
0: Increase hours.
513: Decrease hours.
143: Increase minutes.
343: Decrease minutes.
732: Confirm the timer setting and proceed to temperature setting.
```

The LCD shows the current time in the format HH:MM:SS.


Setting the Temperature:

After confirming the timer, the user can set the target temperature.
Keypad inputs:
```
0: Increase temperature by 1°C.
513: Decrease temperature by 1°C.
732: Confirm the temperature setting and proceed to the main process.
```

The LCD displays the current temperature setting.


Running the Process:

Press the keypad button (analog value 732) to start the timer.
The system maintains the target temperature by turning the heater on or off based on the thermocouple reading.
The LCD displays the remaining time (in HH:MM:SS format) and the target temperature.
If the temperature is below the target, the heater turns on; if above or equal, it turns off.


Stopping the Process:

Press the keypad button (analog value 732) again to stop the timer and heater.
The LCD displays "Timer Stopped" with a reset instruction.
When the countdown reaches zero, the heater turns off, and the process stops automatically.



Code Explanation

Libraries:

LiquidCrystal.h: Manages the LCD display.
max6675.h: Interfaces with the MAX6675 thermocouple for temperature readings.


Setup:

Initializes the LCD, serial communication, and heater control pin.
Displays the initial message and prompts for timer and temperature settings.


Main Loop:

Continuously reads keypad input to start/stop the timer.
Updates the timer and controls the heater when the countdown is running.


Functions:

startTimer(): Starts the countdown and displays "Timer Started".
stopTimer(): Stops the countdown, turns off the heater, and displays "Timer Stopped".
updateTimer(): Updates the countdown every second and refreshes the LCD display.
getTime(): Handles keypad inputs to adjust the countdown time (hours and minutes).
getTemp(): Handles keypad inputs to adjust the target temperature.
changetemp(): Reads the thermocouple and controls the heater to maintain the target temperature.



Keypad Analog Values
The keypad is connected to analog pin A0, and specific analog values correspond to key presses:

0: Increase hours/temperature.
513: Decrease hours/temperature.
143: Increase minutes.
343: Decrease minutes.
732: Confirm settings or start/stop the timer.

These values may vary depending on your keypad. Test the keypad by printing the analog values to the Serial Monitor (Serial.println(analogRead(A0))) and update the code if necessary.
Usage Instructions

Power on the Arduino and wait for the "Bio-Gel Maker" message.
Use the keypad to set the desired countdown time (hours and minutes).
Press the confirm key (analog value 732) to proceed to temperature setting.
Set the target temperature using the keypad.
Press the confirm key again to start the process.
The system will maintain the target temperature and display the remaining time.
Press the confirm key to stop the process manually, or wait for the timer to reach zero.

Troubleshooting

LCD Not Displaying:
Check the LCD connections and ensure the correct pins are used.
Adjust the contrast potentiometer on the LCD module.


Keypad Not Responding:
Verify the keypad is connected to analog pin A0.
Print analog values to the Serial Monitor to confirm the correct key values.


Temperature Not Accurate:
Ensure the thermocouple is properly connected and positioned.
Check the MAX6675 module wiring and library installation.


Heater Not Working:
Verify the relay or transistor connections.
Ensure the heater is compatible with the control circuit and power supply.



Future Improvements

Add hysteresis to the temperature control to prevent rapid heater switching.
Implement a buzzer to alert when the countdown reaches zero.
Add error handling for invalid thermocouple readings.
Support a wider range of keypad inputs or a more user-friendly interface.

License
This project is licensed under the MIT License. See the LICENSE file for details.
Contributing
Contributions are welcome! Please open an issue or submit a pull request on GitHub for any improvements or bug fixes.
