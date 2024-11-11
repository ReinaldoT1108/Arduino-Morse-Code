const int morsePin = 2;            // Pin for the Morse key
const unsigned long threshold = 300; // Threshold in ms to differentiate dot and dash
const unsigned long debounceTime = 200; // Debounce delay to prevent multiple detections
const unsigned long releaseDebounce = 150; // Extra debounce after key release to stabilize

unsigned long pressStart = 0;
unsigned long lastPressTime = 0;  // Track the time of the last key press
bool isPressed = false;  // Track if the key is currently pressed
bool isReleased = true;  // Track if the key has been released

void setup() {
  pinMode(morsePin, INPUT_PULLUP);   // Set the key pin as input
  Serial.begin(9600);  // Begin Serial communication at 9600 baud
  Serial.println("Ready to detect Morse code!"); // Confirm serial is working
}

void loop() {
  int state = digitalRead(morsePin); // Read the current state of the key

  // Detect key press (circuit closed)
  if (state == LOW && !isPressed && (millis() - lastPressTime) > debounceTime) {
    isPressed = true;  // Mark as pressed
    pressStart = millis();  // Record the time when the key was pressed
    Serial.println("Closed");  // Print "Closed" when key is pressed
    lastPressTime = millis();  // Update last press time to prevent bouncing
    isReleased = false;  // The key is now pressed, not released
  }

  // Detect key release (circuit opened)
  if (state == HIGH && !isReleased && isPressed && (millis() - pressStart) > releaseDebounce) {
    unsigned long pressDuration = millis() - pressStart; // Measure press duration
    isPressed = false;  // Reset pressed state
    isReleased = true;  // The key is now released

    // Output based on the press duration
    if (pressDuration < threshold) {
      Serial.print(".");   // Send dot for short press
      Serial.println(" - Detected as Dot (short press)");
    } else {
      Serial.print("-");   // Send dash for long press
      Serial.println(" - Detected as Dash (long press)");
    }

    delay(50);  // Small delay to prevent overlap between characters
  }
}


