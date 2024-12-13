# Sound-Activated-LED
Clap twice to turn the LED light on/off. This project uses arduino code to program an ESP32 board, with a sound sensor.


# Double Clap Controlled LED Project

## Overview
This project demonstrates a simple sound-controlled system using an ESP32 microcontroller and a sound sensor. The objective is to detect two claps in quick succession and toggle the state of an LED (turn it ON or OFF).

---

## Logic
The system works as follows:
1. **Sound Detection**:
   - A sound sensor detects a noise (clap) and outputs a signal (LOW).
2. **Clap Counting**:
   - The ESP32 increments a counter each time a valid clap (transition from HIGH to LOW) is detected.
3. **Toggle LED**:
   - When two claps are detected, the system toggles the LED's state (ON or OFF).
4. **Reset Counter**:
   - After toggling the LED, the counter resets to zero, awaiting the next detection cycle.

---

## Components Used
- **ESP32 Microcontroller**: Handles the logic and controls the LED.
   - ELEGOO ESP32 2pcs ESP-WROOM-32 Development Board, USB Type-C [https://www.amazon.ca/dp/B0D8T7Z1P5?ref=ppx_pop_mob_ap_share&th=1].
- **Sound Sensor**: Detects sound and outputs a digital signal (LOW for noise).
   - DAOKI 5-Pack High Sensitivity Sound Microphone Sensor Detection Module for Arduino AVR PIC [https://www.amazon.ca/dp/B00XT0PH10?ref=ppx_pop_mob_ap_share].   
- **LED**: A visual indicator toggled by the clap detection logic.
- **Resistor**: 220Ω for limiting current to the LED.
- **10kΩ Pull-Down Resistor**: Ensures stable sensor output.
- **Breadboard**: For prototyping connections.
- **Jumper Wires**: For connecting components.

---

## Wiring
- **Sound Sensor**:
  - `VCC` → ESP32 `VIN` (It could go to `3.3V` instead, but since the sound sensor requires an input of 5V, we used `VIN`).
  - `GND` → ESP32 `GND`
  - `OUT` → ESP32 `GPIO34` or `D34`
- **LED**:
  - Anode (long leg) → ESP32 `GPIO2` or `D2` (via 220Ω resistor)
  - Cathode (short leg) → ESP32 `GND`
- **Pull-Down Resistor**:
  - Connected between `OUT` and `GND` of the sound sensor.

### Schematic
```plaintext
Sound Sensor:
+---------+
| VCC ---+--------- VIN
| GND ---+--------- GND
| OUT ---+-------- GPIO34
|         |
|      10kΩ
|         |
+---------+--------- GND

LED:
+---[220Ω]---+
|            |
GPIO2       GND
```

---

## Code Explanation
The code performs the following tasks:
1. Initializes the sensor pin (`GPIO34`) and LED pin (`GPIO2`).
2. Detects falling edges (HIGH to LOW transitions) from the sound sensor.
3. Increments a counter (`count`) on each valid detection.
4. Toggles the LED state when the counter reaches two.
5. Resets the counter for the next cycle.

### Full Code
```cpp
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
```

---

## Testing and Observations
1. **Sound Sensor Testing**:
   - The sensor outputs `0` when detecting noise and `1` otherwise.
   - The built-in LED on the sensor blinks when noise is detected.

2. **Logic Verification**:
   - The counter increments only on valid transitions from `1` to `0`.
   - The LED toggles correctly after two valid claps.

3. **Challenges Faced**:
   - Initial signal instability was resolved using a 10kΩ pull-down resistor and logic refinements.

---

## Improvements for Future Work
1. **Time-Based Detection**:
   - Add timing constraints to ensure detected sounds are within a specific interval (e.g., to differentiate claps from other noises).
2. **Sensitivity Adjustment**:
   - Optimize the potentiometer settings on the sound sensor for better noise rejection.
3. **Clap Recognition**:
   - Implement advanced algorithms to distinguish claps from other sounds based on amplitude or frequency.

---

## Conclusion
This project successfully demonstrates a double-clap detection system using an ESP32 and a sound sensor. The LED toggling logic is stable and provides a foundation for further enhancements like advanced sound processing and timing constraints.
