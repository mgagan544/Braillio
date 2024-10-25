int buttonPin1 = 2;  // Dot 1
int buttonPin2 = 3;  // Dot 2
int buttonPin3 = 4;  // Dot 3
int buttonPin4 = 5;  // Dot 4
int buttonPin5 = 6;  // Dot 5
int buttonPin6 = 7;  // Dot 6

int buttonState1;
int buttonState2;
int buttonState3;
int buttonState4;
int buttonState5;
int buttonState6;

bool capsMode = false;  // Flag for uppercase mode

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 bps
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);  // Set the button pins as input
}

void loop() {
  // Read the state of the buttons
  buttonState1 = digitalRead(buttonPin1);  
  buttonState2 = digitalRead(buttonPin2);  
  buttonState3 = digitalRead(buttonPin3);  
  buttonState4 = digitalRead(buttonPin4);  
  buttonState5 = digitalRead(buttonPin5);  
  buttonState6 = digitalRead(buttonPin6);

  // Check for CAPS mode (only button 6 is pressed)
  if (buttonState1 == LOW && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == HIGH) {
    capsMode = !capsMode;  // Toggle caps mode
    Serial.println(capsMode ? "CAPS ON" : "CAPS OFF");
    delay(500);  // Prevent rapid toggling
  }

  // Check for space (all buttons are pressed)
  if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == HIGH) {
    Serial.println(" ");  // Space bar
    delay(500);  // Prevent multiple spaces from being sent too quickly
  } 
  else {
    // Braille combinations for A-Z with optional CAPS
    char outputChar = '\0';  // Variable to store the character to be printed

    if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'A';
    } 
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'B';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'C';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'D';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'E';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'F';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'G';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'H';
    }
    else if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'I';
    }
    else if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'J';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'K';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'L';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'M';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'N';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'O';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'P';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'Q';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'R';
    }
    else if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == LOW && buttonState6 == LOW) {
      outputChar = 'S';
    }
    else if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == LOW) {
      outputChar = 'T';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == HIGH) {
      outputChar = 'U';
    }
    else if (buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == HIGH) {
      outputChar = 'V';
    }
    else if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == LOW && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == HIGH) {
      outputChar = 'W';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == LOW && buttonState6 == HIGH) {
      outputChar = 'X';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == HIGH) {
      outputChar = 'Y';
    }
    else if (buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH && buttonState4 == LOW && buttonState5 == HIGH && buttonState6 == HIGH) {
      outputChar = 'Z';
    }

    // Print the character with or without caps
    if (outputChar != '\0') {
      if (capsMode) {
        Serial.println(outputChar);  // Print uppercase
      } else {
        Serial.println((char)tolower(outputChar));  // Print lowercase
      }
    }
  }

  delay(300);  // Add delay to prevent multiple letters from being sent too quickly
}
