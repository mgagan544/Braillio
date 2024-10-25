import serial
import keyboard  # For controlling the keyboard
import time

# Set up the serial port (adjust the port name accordingly)
ser = serial.Serial('COM3', 9600)  # Replace 'COM3' with your correct port

# Variable to track caps lock state (default is off)
caps_on = False

while True:
    if ser.in_waiting > 0:
        # Read the serial data from the Arduino
        serial_data = ser.readline().decode('utf-8').strip()

        # Debugging: Show the received data
        print(f"Received: {serial_data}")
        
        # Handle CAPS lock toggle
        if serial_data == "CAPS":
            caps_on = not caps_on
            keyboard.press_and_release('caps lock')  # Simulate Caps Lock press
            print(f"Caps Lock toggled: {'ON' if caps_on else 'OFF'}")

        # Handle space
        elif serial_data == "SPACE":
            keyboard.write(' ')  # Simulate Space press
            print("Pressed: Space")

        # Handle alphabetic key presses
        elif len(serial_data) == 1 and serial_data.isalpha():
            if caps_on:
                keyboard.write(serial_data.upper())  # Type uppercase if caps is on
                print(f"Typing Uppercase: {serial_data.upper()}")
            else:
                keyboard.write(serial_data.lower())  # Type lowercase if caps is off
                print(f"Typing Lowercase: {serial_data.lower()}")

        # Add a small delay to avoid overwhelming the system with too many key presses at once
        time.sleep(0.2)
