# Braille Assistant Project

## Overview
Braille Assistant is a device that translates digital text to Braille code,it allows them to feel due to tactile interface which is implemented using push pull solenoids which pop up on curent and go back to original state upon withdrawal of current. Braillio designed to aid visually impaired users by converting text input into Braille patterns. Users can input text via six push buttons, each representing one of the Braille cell combinations. The project is aimed to be compatible with Windows Narrator for seamless text-to-Braille integration.

## Features
- **Digital Text to Braille Conversion**: Translates input text into Braille code, displayed on an LCD.
- **Braille Code Input**: Allows visually impaired users to input text using combinations of six push buttons.
- **Windows Narrator Integration**: Reads out text in Braille format for easy comprehension.

## Project Setup
### Hardware Requirements
- Arduino microcontroller
- Push Pull Solenoids
- Six push buttons for Braille cell combinations
- N-channel MOSFET or L293D motor driver
- rectifier diode
- External power supply


### Software Requirements
- Arduino IDE
- Python 3.x (for Raspberry Pi-based TTS)
- Libraries: `pyautogui
pytesseract
PIL (Python Imaging Library)
pyserial
keyboard
win32
pywinauto
Application
tkinter
numpy 
OpenCV
pyperclip

### Wiring Diagram
- Digital Pins of the Arduino is connected to a push button with a pull-down resistor.
-   ![image](https://github.com/user-attachments/assets/b717e89e-f006-41e3-88d9-fefc400a25ae)

- Solenoid controlled via an N-channel MOSFET and powered by an external power supply. 
    ![image](https://github.com/user-attachments/assets/58495b37-75bb-47fa-b881-3e7f5e88e775)

  Can also try using motor driver (3 way solenoid) where connected to output 1 and 2 and external power supply.
    ![image](https://github.com/user-attachments/assets/e2bb3e8b-6257-410d-973f-272c1e99fe1d)


## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/Braille-Assistant.git
   cd Braille-Assistant
