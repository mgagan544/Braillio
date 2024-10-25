# Braille Assistant Project

## Overview
Braille Assistant is a device that translates digital text to Braille code, allowing visually impaired users to feel the text through a tactile interface. The tactile interface is implemented using push-pull solenoids that pop up when current is applied and return to their original state when the current is withdrawn. Braillio, the device, is designed to aid visually impaired users by converting text input into Braille patterns. Users can input text via six push buttons, each representing one of the Braille cell combinations. The project is aimed to be compatible with Windows Narrator for seamless text-to-Braille integration.

## Features
- **Digital Text to Braille Conversion**: Translates input text into Braille code, displayed on an LCD.
- **Braille Code Input**: Allows visually impaired users to input text using combinations of six push buttons.
- **Windows Narrator Integration**: Reads out text in Braille format for easy comprehension.

## Project Setup

### Hardware Requirements
- Arduino microcontroller
- Push-Pull Solenoids
- Six push buttons for Braille cell combinations
- N-channel MOSFET or L293D motor driver
- Rectifier diode
- External power supply

### Software Requirements
- Arduino IDE
- Python 3.x (for Raspberry Pi-based TTS)
- Libraries: 
   - `pyautogui`
   - `pytesseract`
   - `PIL (Python Imaging Library)`
   - `pyserial`
   - `keyboard`
   - `win32`
   - `pywinauto`
   - `tkinter`
   - `numpy`
   - `opencv-python`
   - `pyperclip`

### Wiring Diagram
- **Digital Pins of the Arduino**: Connected to a push button with a pull-down resistor.
  
  ![image](https://github.com/user-attachments/assets/b717e89e-f006-41e3-88d9-fefc400a25ae)

- **Solenoid Control**: Controlled via an N-channel MOSFET and powered by an external power supply.
  
  ![image](https://github.com/user-attachments/assets/58495b37-75bb-47fa-b881-3e7f5e88e775)

  Alternatively, you can use a motor driver (3-way solenoid) connected to output 1 and 2 and powered by an external power supply.

  ![image](https://github.com/user-attachments/assets/e2bb3e8b-6257-410d-973f-272c1e99fe1d)


## How to Run

### Output (Screen Text to Solenoids)

1. Upload the Arduino code to your Arduino microcontroller.
2. Run the Python script to read the text from the screen and convert it to Braille output.
   - The Python script sends data through the serial monitor, which is then reflected in the hardware setup, controlling the solenoids to display the Braille pattern.

### Input (Push Button Keyboard)

1. First, upload the Arduino code that captures input from the six push buttons and sends the data to the serial monitor.
2. Run the Python script to extract this data from the serial monitor and process it.
   - The script will convert the button presses into corresponding text or Braille patterns.

## Future Enhancements

- Integrate a refreshable Braille display for real-time Braille output.
- Improve accuracy and responsiveness of the Windows Narrator integration for Braille reading.
- Explore further compatibility with screen readers and expand voice input capabilities.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/Braille-Assistant.git
   cd Braille-Assistant
