// Pin definitions
#define SENSOR_PIN 34 // Pin connected to the noise sensor signal output
#define LED_PIN 2     // Pin connected to the external LED on the breadboard

// Variables to track clap detection
int count = 0;               // Tracks the number of detected sounds
bool ledState = false;        // State of the real LED
int previousSensorValue = 1;  // Last stable state of the sensor

void setup() {
    Serial.begin(115200);       // Initialize Serial Monitor
    pinMode(SENSOR_PIN, INPUT); // Set the sensor pin as input
    pinMode(LED_PIN, OUTPUT);   // Set the LED pin as output

    // Ensure the LED is off initially
    digitalWrite(LED_PIN, LOW);

    // Debugging info
    Serial.println("LED control with sound detection started.");
}

void loop() {
    // Read the noise sensor's output
    int currentSensorValue = digitalRead(SENSOR_PIN);

    // Check for a falling edge (sound detected)
    if (previousSensorValue == 1 && currentSensorValue == 0) {
        count++; // Increment sound count

        // If two sounds are detected, toggle the LED state
        if (count == 2) {
            ledState = !ledState;             // Toggle the LED state
            digitalWrite(LED_PIN, ledState); // Update the real LED
            Serial.print("LED State: ");
            Serial.println(ledState ? "ON" : "OFF");
            count = 0; // Reset count
        }

        // Debugging: Print the current count
        Serial.print("Count: ");
        Serial.println(count);
    }

    // Update the previous sensor value
    previousSensorValue = currentSensorValue;

    // Debugging: Print the current sensor value
    Serial.print("Sensor Value: ");
    Serial.println(currentSensorValue);

    // Small delay to prevent excessive polling
    delay(50);
}
