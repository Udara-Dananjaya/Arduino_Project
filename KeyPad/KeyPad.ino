const byte ROWS = 4; // Number of rows
const byte COLS = 4; // Number of columns
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; // Row pin numbers
byte colPins[COLS] = {6, 5, 4, 3}; // Column pin numbers

void setup() {
  Serial.begin(9600);
  // Initialize row pins as INPUT_PULLUP
  for (byte i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }
  // Initialize column pins as OUTPUT and set them LOW
  for (byte i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
}

void loop() {
  char customKey = getKey();
  if (customKey != 0) {
    Serial.println(customKey);
    // Add your custom logic for key handling here
  }
}

char getKey() {
  for (byte col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW); // Activate the current column
    for (byte row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        // Key is pressed, return the corresponding character
        delay(50); // Debounce delay
        while (digitalRead(rowPins[row]) == LOW) {} // Wait for key release
        digitalWrite(colPins[col], HIGH); // Deactivate the column
        return hexaKeys[row][col];
      }
    }
    digitalWrite(colPins[col], HIGH); // Deactivate the column
  }
  return 0; // No key is pressed
}
