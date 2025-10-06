// Arduino Temperature Controller
// This program allows the user to set a target temperature and time.
// It then controls a heating element to maintain the temperature for the set duration.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <max6675.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// LCD Setup (I2C Address: 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// MAX6675 Thermocouple Sensor Setup
int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// DS18B20 Temperature Sensor Setup
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Relay Control Pins
#define HEATER_RELAY 4

// Button Pins
#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_SET 5

// Global Variables
float targetTemperature = 30.0; // Default target temperature
unsigned long duration = 300;   // Default time in seconds (5 min)
bool isRunning = false;
unsigned long startTime;

void setup() {
    pinMode(HEATER_RELAY, OUTPUT);
    digitalWrite(HEATER_RELAY, LOW);
    
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_SET, INPUT_PULLUP);
    
    lcd.begin();
    lcd.backlight();
    
    sensors.begin();
    
    lcd.setCursor(0, 0);
    lcd.print("Temp Controller");
    delay(2000);
    lcd.clear();
}

void loop() {
    float currentTemp = thermocouple.readCelsius();
    lcd.setCursor(0, 0);
    lcd.print("Current: ");
    lcd.print(currentTemp);
    lcd.print("C  ");
    
    lcd.setCursor(0, 1);
    lcd.print("Set: ");
    lcd.print(targetTemperature);
    lcd.print("C");
    
    // Button Handling
    if (digitalRead(BUTTON_UP) == LOW) {
        targetTemperature += 0.5;
        delay(200);
    }
    if (digitalRead(BUTTON_DOWN) == LOW) {
        targetTemperature -= 0.5;
        delay(200);
    }
    if (digitalRead(BUTTON_SET) == LOW) {
        isRunning = !isRunning;
        startTime = millis();
        delay(500);
    }
    
    // Heating Logic
    if (isRunning) {
        unsigned long elapsedTime = (millis() - startTime) / 1000;
        lcd.setCursor(10, 1);
        lcd.print("Time:");
        lcd.print(duration - elapsedTime);
        lcd.print("s ");
        
        if (elapsedTime >= duration) {
            isRunning = false;
            digitalWrite(HEATER_RELAY, LOW);
        } else {
            if (currentTemp < targetTemperature) {
                digitalWrite(HEATER_RELAY, HIGH);
            } else {
                digitalWrite(HEATER_RELAY, LOW);
            }
        }
    } else {
        digitalWrite(HEATER_RELAY, LOW);
    }
    
    delay(500);
}
