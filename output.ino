const int solenoids[6] = {2, 3, 4, 5, 6, 7};  // Pins for the solenoids

void setup() {
  Serial.begin(9600);  // Start serial communication
  for (int i = 0; i < 6; i++) {
    pinMode(solenoids[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    char incomingChar = Serial.read();  // Read a character from the serial port
    
    // Convert the character to a braille pattern
    byte braillePattern = charToBraille(incomingChar);
    
    // Activate solenoids based on the braille pattern
    for (int i = 0; i < 6; i++) {
      digitalWrite(solenoids[i], (braillePattern & (1 << i)) ? HIGH : LOW);
    }
    
    delay(500);  // Keep the pattern for 500ms
    
    // Reset all solenoids
    for (int i = 0; i < 6; i++) {
      digitalWrite(solenoids[i], LOW);
    }
  }
}

// Function to map characters to braille patterns
byte charToBraille(char c) {
  if (c >= 'a' && c <= 'z') {
    // Lowercase letters
    static const byte letterPatterns[] = {
      B000001, B000011, B001001, B011001, B010001, B001011,  // a-f
      B011011, B010011, B001010, B011010, B000101, B000111,  // g-l
      B001101, B011101, B010101, B001111, B011111, B010111,  // m-r
      B001110, B011110, B100101, B100111, B011010, B101101,  // s-x
      B111101, B110101                                       // y-z
    };
    return letterPatterns[c - 'a'];
  } else if (c >= '0' && c <= '9') {
    // Numbers (using number sign)
    static const byte numberPatterns[] = {
      B001111, B000001, B000011, B001001, B011001,  // 0-4
      B010001, B001011, B011011, B010011, B001010   // 5-9
    };
    return numberPatterns[c - '0'];
  } else {
    // Punctuation and special characters
    switch (c) {
      case ' ': return B000000;  // Space
      case '.': return B001000;  // Period
      case ',': return B000010;  // Comma
      case '-': return B001001;  // Hyphen
      case '!': return B011010;  // Exclamation mark
      case '?': return B011001;  // Question mark
      default: return B000000;   // Unknown character (blank cell)
    }
  }
}