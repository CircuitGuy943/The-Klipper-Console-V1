#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define ENCODER_CLK 2
#define ENCODER_DT  3
#define LED_PIN 6        // Data pin
#define NUM_LEDS 16      // Number of SK6812 MINI-E LEDs
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1  // Not used
#define SCREEN_ADDRESS 0x3C  // Common I2C address, needs testing and changing to correct one

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile int encoderPos = 0;  // Counter
int lastCLK = LOW;

// Matrix size
const uint8_t ROW_COUNT = 3;
const uint8_t COL_COUNT = 3;

// Pin assignments
const uint8_t ROW_PINS[ROW_COUNT] = {0, 1, 7};
const uint8_t COL_PINS[COL_COUNT] = {8, 9, 10};

// Matrix data to be transferred
//                R1------- R2------ R3------
uint8_t data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//                C1 C2 C3 C1 C2 C3 C1 C2 C3

// Setup
void setup() {
  Serial.begin(115200);

  // Rows: inputs with internal pull-downs
  for (uint8_t row = 0; row < ROW_COUNT; row++) {
    pinMode(ROW_PINS[row], INPUT_PULLDOWN);
  }

  // Columns: outputs, idle LOW
  for (uint8_t col = 0; col < COL_COUNT; col++) {
    pinMode(COL_PINS[col], OUTPUT);
    digitalWrite(COL_PINS[col], LOW);
  }

  Wire.begin();  // Initialize I2C

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Hello RP2040");
  display.display();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  for(int i=0; i<NUM_LEDS; i++){
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red
  }
  strip.show();

  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);

  lastCLK = digitalRead(ENCODER_CLK);
}

// Main loop
void loop() {

  //Read matrix
  scanMatrix();

  // Read encoder
  int clkState = digitalRead(ENCODER_CLK);
  if(clkState != lastCLK) { // rotation detected
    if(digitalRead(ENCODER_DT) != clkState) {
      encoderPos++;  // clockwise
    } else {
      encoderPos--;  // counter-clockwise
    }
    Serial.print("Position: "); Serial.println(encoderPos);
  }
  lastCLK = clkState;

  // Send Array over serial
  void sendArray() {
    Serial.write(0xAA);                 // start byte
    Serial.write(sizeof(data));         // length
    Serial.write(data, sizeof(data));   // payload
    Serial.write(0x55);                 // end byte
  }

  delay(5); // debounce window
}

// Matrix scan
void scanMatrix() {

  for (uint8_t col = 0; col < COL_COUNT; col++) {

    // Drive one column HIGH
    digitalWrite(COL_PINS[col], HIGH);
    delayMicroseconds(3); // signal settle time

    // Read all rows
    for (uint8_t row = 0; row < ROW_COUNT; row++) {

      bool pressed = (digitalRead(ROW_PINS[row]) == HIGH);

      if (pressed) {
        data[row*3 + col ] = pressed
      }
    }

    // Return column to idle LOW
    digitalWrite(COL_PINS[col], LOW);
  }

  return data
}
