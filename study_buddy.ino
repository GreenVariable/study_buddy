#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128   // OLED display width, in pixels
#define SCREEN_HEIGHT 64   // OLED display height, in pixels
#define OLED_RESET    -1   // Reset pin for OLED (no reset in this configuration)
#define SCREEN_ADDRESS 0x3C // I2C address for the OLED display

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the analog pin for reading light level
int ReadPin = A0;
// Variable to store the light level reading from the photoresistor
int lightLevel = 0;

// Function to draw neutral (open) eyes on the OLED display
void drawNeutralEyes() {
  display.clearDisplay();
  
  // Draw left eye (outer circle and pupil)
  display.drawCircle(40, 32, 10, SSD1306_WHITE);  // Outer circle
  display.fillCircle(40, 32, 5, SSD1306_WHITE);   // Pupil
  
  // Draw right eye (outer circle and pupil)
  display.drawCircle(88, 32, 10, SSD1306_WHITE);  // Outer circle
  display.fillCircle(88, 32, 5, SSD1306_WHITE);   // Pupil
  
  display.display();  // Update the display to show the eyes
}

// Function to draw closed eyes (used for both blinking and sleep mode)
void drawClosedEyes() {
  display.clearDisplay();
  
  // Draw left closed eye (horizontal line)
  display.drawLine(30, 32, 50, 32, SSD1306_WHITE);
  
  // Draw right closed eye (horizontal line)
  display.drawLine(78, 32, 98, 32, SSD1306_WHITE);
  
  display.display();  // Update the display to show closed eyes
}

// Function to simulate a blinking effect
void blink() {
  drawClosedEyes();   // Show closed eyes to mimic blinking
  delay(200);         // Brief delay to mimic blink duration
  drawNeutralEyes();  // Return to open (neutral) eyes
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed")); // Error message if display initialization fails
    for(;;);  // Halt program if initialization fails
  }

  // Set up the analog pin for input from the photoresistor
  pinMode(ReadPin, INPUT);
  
}

void loop() {
  // Read the light level from the photoresistor
  lightLevel = analogRead(ReadPin);
  
  // Check if the light level is above the threshold for study lighting
  if (lightLevel > 650) {
    blink();           // Show open and blinking eyes if lighting is adequate
    delay(1500);       // Delay between blinks
  } else {
    drawClosedEyes();  // Show closed eyes if lighting is too low
  }
}

