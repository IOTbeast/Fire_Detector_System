#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define SPEAKER_PIN 12  // Digital pin connected to the speaker
#define LED_PIN 6       // Digital pin connected to the LED
#define BUTTON_PIN 13   // Digital pin connected to the push button

//#define DHTTYPE DHT11
//#define DHTTYPE DHT21
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4); // Adjusted for a larger display: 20 columns, 4 rows

bool speakerActive = true;  // Flag to track if the speaker is active

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();       // LCD
  lcd.backlight();  // LCD
  pinMode(SPEAKER_PIN, OUTPUT); // Set the speaker pin as an output
  pinMode(LED_PIN, OUTPUT);      // Set the LED pin as an output
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set the push button pin as an input with an internal pull-up resistor
}

void loop() {
  delay(1000); // Wait a few seconds between measurements.

  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Check if the push button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Button is pressed, toggle the speaker state
    speakerActive = !speakerActive;

    // Wait for the button release to avoid rapid toggling
    while (digitalRead(BUTTON_PIN) == LOW) {
      // This loop ensures that the speaker is toggled only once when the button is pressed
    }

    // Turn off the siren immediately
    noTone(SPEAKER_PIN);
    digitalWrite(LED_PIN, LOW); // Turn off the LED when the button is pressed
  }

  // If the button is not pressed, continue with normal operations

  lcd.clear(); // Clear the LCD before updating

  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(t);
  lcd.print(" C");

  Serial.print("%  Temperature: ");
  Serial.print(t, 1);
  Serial.print(" C & ");
  Serial.print(f, 1);
  Serial.println(" F");

  // Check if the temperature is within the specified range for fire detection
  if (t >= 70 && t <= 80) {
    lcd.setCursor(0, 1);
    lcd.print("W:FIRE DETECTED!");
    lcd.setCursor(0, 2);

    // Check if the speaker is active
    if (speakerActive) {
      // Activate the siren sound
      tone(SPEAKER_PIN, 1000);  // Adjust the frequency as needed
      digitalWrite(LED_PIN, HIGH); // Turn on the LED when the speaker is active
      delay(5);
      digitalWrite(LED_PIN, LOW);  
    } else {
      // Turn off the siren and LED
      noTone(SPEAKER_PIN);
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    // Turn off the siren and LED if no fire is detected
    noTone(SPEAKER_PIN);
    digitalWrite(LED_PIN, LOW);
  }
}