// Pin definitions
#define SENSOR_PIN 34 // Pin connected to the noise sensor signal output
#define LED_PIN 2     // Pin connected to the external LED on the breadboard

// Clap detection timing
#define CLAP_WINDOW 600 // Time window for double-clap in milliseconds

// Variables to track clap detection
int count = 0;                   // Tracks the number of detected sounds
bool ledState = false;           // State of the real LED
int previousSensorValue = 1;     // Last stable state of the sensor
unsigned long clapTimeout = 0;   // Timer to track the end of the clap window

void setup() {
    Serial.begin(115200);       // Initialize Serial Monitor
    pinMode(SENSOR_PIN, INPUT); // Set the sensor pin as input
    pinMode(LED_PIN, OUTPUT);   // Set the LED pin as output

    // Ensure the LED is off initially
    digitalWrite(LED_PIN, LOW);

    // Debugging info
    Serial.println("LED control with sound detection started.");
    Serial.print("Clap Window: ");
    Serial.print(CLAP_WINDOW);
    Serial.println("ms");
}

void loop() {
    // Read the noise sensor's output
    int currentSensorValue = digitalRead(SENSOR_PIN);

    // Check for a falling edge (sound detected)
    if (previousSensorValue == 1 && currentSensorValue == 0) {
        
        // If this is the first clap, start the timer.
        if (count == 0) {
            clapTimeout = millis() + CLAP_WINDOW;
            count++;
            Serial.println("First clap detected. Timer started.");
        }
        // If this is the second clap, check if it's within the time window.
        else if (count == 1 && millis() < clapTimeout) {
            // Success! Double-clap detected within the window.
            ledState = !ledState;
            digitalWrite(LED_PIN, ledState);
            Serial.print("DOUBLE-CLAP! LED State: ");
            Serial.println(ledState ? "ON" : "OFF");
            count = 0; // Reset for the next command
        }

        // Debugging: Print the current count
        Serial.print("Count: ");
        Serial.println(count);
    }

    // Check if the clap window has expired
    if (count == 1 && millis() >= clapTimeout) {
        Serial.println("Clap window expired. Resetting.");
        count = 0; // Reset the counter
    }

    // Update the previous sensor value
    previousSensorValue = currentSensorValue;

    // Small delay to prevent excessive polling
    delay(50);
}
