#include <LiquidCrystal.h>         // Include the LiquidCrystal library for the LCD display
#include "max6675.h"               // Include the MAX6675 library for interfacing with the thermocouple

// LCD setup (pins connected to Arduino Mega)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);       
int key = analogRead(A0);            // Variable for reading the keypress from the keypad

// Timer setup (countdown time in seconds)
int countdownTime = 300;  // Initial countdown time set to 5 minutes (300 seconds)
int countdownState = 0;   // 0: Stopped, 1: Running
unsigned long previousMillis = 0;  // Used to track the elapsed time
unsigned long myTime;                // Placeholder for time updates

// Thermostat and heating setup (pins for thermocouple and heating control)
int thermoDO = 21;
int thermoCS = 20;
int thermoCLK = 19;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);  // Initialize thermocouple object
int temp = 25;                        // Initial target temperature for heating (25°C)
int e_control = 20;                   // Digital output pin for controlling the electric heater
float readTemp;                       // Variable for reading the current temperature from thermocouple

void setup() {
  Serial.begin(9600);                 // Start serial communication for debugging
  lcd.begin(16, 2);                   // Initialize the LCD display (16 columns, 2 rows)
  pinMode(e_control, OUTPUT);         // Set heater control pin as output

  lcd.print(" Bio-Gel Maker");        // Display the initial message
  delay(5000);                        // Wait for 5 seconds before proceeding

  // Loop to change the countdown time
  while (key != 732){  // Keypad input check to change time
    lcd.clear();
    lcd.print("  change time");
    lcd.print("                               ");
    lcd.print(countdownTime / 3600);      // Display hours
    lcd.print(":");
    if (((countdownTime % 3600) / 60) < 10){
      lcd.print("0");
    }
    lcd.print((countdownTime % 3600) / 60);  // Display minutes
    lcd.print(":");
    lcd.print("00");                        // Display seconds
    delay(200);
    getTime();                             // Call function to get time input
  }

  lcd.clear();
  lcd.print("    time set");
  delay(1500);                           // Wait for a short time before asking for temperature
  key = analogRead(A0);

  // Loop to change the target temperature
  while (key != 732){    // Keypad input check to change temperature
    lcd.clear();
    lcd.print("  change temp");
    lcd.print("                                 ");
    lcd.print(temp);           // Display the current temperature
    lcd.print("'C");
    delay(200);
    getTemp();  // Call function to get temperature input
  }

  lcd.clear();
  lcd.print(" tempreture set");
  delay(1500);  // Wait for a short time before starting the process
  key = analogRead(A0);
}

void loop() {
  key = analogRead(A0);  // Continuously read keypress from the keypad
  if (key == 732 && countdownState == 0) {
    startTimer();          // Start the timer if button pressed and timer is stopped
  } else if (key == 732 && countdownState == 1) {
    stopTimer();           // Stop the timer if button pressed and timer is running
  }

  // If timer is running, control temperature
  if (countdownState != 0 ){
    changetemp();          // Adjust the temperature based on the thermocouple reading
  }

  // Update the timer when countdown is running
  if (countdownState == 1 && countdownTime > 0) {
    updateTimer();         // Call function to update timer every second
  }
  else{
    return;
  }
}

// Function to start the timer
void startTimer() {
  lcd.clear();
  lcd.print(" Timer Started");
  countdownState = 1;  // Set countdown state to running
  delay(500);
  delay(500);
}

// Function to stop the timer and heater
void stopTimer() {
  digitalWrite(e_control, LOW);  // Turn off the heater
  lcd.clear();
  lcd.print(" Timer Stopped                           rst to restart");
}

// Function to update the countdown timer display
void updateTimer() {
  unsigned long currentMillis = millis();  // Get the current time in milliseconds

  if (currentMillis - previousMillis >= 1000) {  // Update every 1 second
    previousMillis = currentMillis;  // Reset the previousMillis timer

    countdownTime--;  // Decrease countdown time by 1 second

    lcd.clear();
    lcd.print("  ");
    lcd.print(countdownTime / 3600);  // Display hours
    lcd.print(":");
    if ((countdownTime % 3600) / 60 < 10){
      lcd.print("0");
    }
    lcd.print((countdownTime % 3600) / 60);  // Display minutes
    lcd.print(":");
    if (countdownTime % 60 < 10) {
      lcd.print("0");
    }
    lcd.print(countdownTime % 60);  // Display seconds
    lcd.print("   ");
    lcd.print(temp);  // Display the target temperature
    lcd.print("'C");

    // Stop the timer when countdown reaches zero
    if (countdownTime == 0) {
      stopTimer();
      delay(1000);
    }
  }
}

// Function to handle time changes (hour and minute adjustment)
void getTime(){
  key = analogRead(A0);
  while (key == 0){  // Increase the hour of the timer
    countdownTime = countdownTime + 3600;
    if ((countdownTime / 3600) > 99){
      countdownTime = countdownTime - (100 * 3600);
    }
    lcd.clear();
    lcd.print("timer is -> ");
    lcd.print(countdownTime / 3600);
    lcd.print(":");
    lcd.print((countdownTime % 3600) / 60);
    delay(500);
    key = analogRead(A0);
  }

  key = analogRead(A0);
  while (key == 513){  // Decrease the hour of the timer
    countdownTime = countdownTime - 3600;
    if ((countdownTime / 3600) <= 0){
      countdownTime = 0;  // Ensure countdown time doesn't go negative
    }
    lcd.clear();
    lcd.print("timer is -> ");
    lcd.print(countdownTime / 3600);
    lcd.print(":");
    lcd.print((countdownTime % 3600) / 60);
    delay(800);
    key = analogRead(A0);
  }

  key = analogRead(A0);
  while (key == 143){  // Increase the minute of the timer
    countdownTime = countdownTime + 60;
    if (((countdownTime % 3600) / 60) > 59){
      countdownTime = countdownTime - 60 * 60;
    }
    lcd.clear();
    lcd.print("timer is -> ");
    lcd.print(countdownTime / 3600);
    lcd.print(":");
    lcd.print((countdownTime % 3600) / 60);
    delay(400);
    key = analogRead(A0);
  }

  key = analogRead(A0);
  while (key == 343){  // Decrease the minute of the timer
    countdownTime = countdownTime - 60;
    if (((countdownTime % 3600) / 60) < 0){
      countdownTime = countdownTime + 60 * 60;
    }
    lcd.clear();
    lcd.print("timer is -> ");
    lcd.print(countdownTime / 3600);
    lcd.print(":");
    lcd.print((countdownTime % 3600) / 60);
    delay(400);
    key = analogRead(A0);
  }
}

// Function to handle temperature changes
void getTemp(){
  key = analogRead(A0);  // Read the keypad input to increase temperature
  while (key == 0){
    temp = temp + 1;
    lcd.clear();
    lcd.print("the temp is:");
    lcd.print(temp);
    lcd.print("'C");
    delay(600);
    key = analogRead(A0);
  }

  key = analogRead(A0);
  while (key == 513){  // Read the keypad input to decrease temperature
    temp = temp - 1;
    lcd.clear();
    lcd.print("the temp is:");
    lcd.print(temp);
    lcd.print("'C");
    delay(600);
    key = analogRead(A0);
  }
}

// Function to control the heating element based on the thermocouple reading
void changetemp(){
  readTemp = thermocouple.readCelsius();  // Read the temperature from the thermocouple
  if (readTemp > temp){
    digitalWrite(e_control, LOW);  // Turn off the heater if temperature is too high
  }
  else if (readTemp < temp){
    digitalWrite(e_control, HIGH);  // Turn on the heater if temperature is too low
  }
  else if (readTemp == temp){
    digitalWrite(e_control, LOW);  // Turn off the heater if temperature is correct
  }
}
