// Pin definitions
#define SENSOR_PIN 34 // Pin connected to the noise sensor signal output

// Variables to track clap detection
int count = 0;               // Tracks the number of detected sounds
bool virtualLEDState = false; // Virtual state of the sensor LED (for logic)
int previousSensorValue = 1;  // Last stable state of the sensor

void setup() {
    Serial.begin(115200);       // Initialize Serial Monitor
    pinMode(SENSOR_PIN, INPUT); // Set the sensor pin as input

    // Debugging info
    Serial.println("Basic sound detection logic started.");
}

void loop() {
    // Read the noise sensor's output
    int currentSensorValue = digitalRead(SENSOR_PIN);

    // Check for a falling edge (sound detected)
    if (previousSensorValue == 1 && currentSensorValue == 0) {
        count++; // Increment sound count

        // If two sounds are detected, toggle the virtual LED state
        if (count == 2) {
            virtualLEDState = !virtualLEDState; // Toggle virtual LED state
            Serial.print("Virtual Sensor LED State: ");
            Serial.println(virtualLEDState ? "ON" : "OFF");
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
