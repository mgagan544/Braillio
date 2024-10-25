import pyautogui
import pytesseract
from PIL import Image, ImageGrab
import serial
import time
import keyboard
import win32gui
import win32con
import win32clipboard
from pywinauto import Application
from threading import Thread
import queue
import re
import tkinter as tk
from tkinter import ttk
import numpy as np
import cv2
from collections import namedtuple
import pyperclip  # To handle clipboard

TextBlock = namedtuple('TextBlock', ['text', 'x', 'y', 'width', 'height'])

class HighlightOverlay(tk.Tk):
    def __init__(self):
        super().__init__()

        # Make window transparent and always on top
        self.attributes('-alpha', 0.3)
        self.attributes('-topmost', True)
        self.overrideredirect(True)
        
        # Create highlight rectangle
        self.highlight = tk.Label(self, bg='yellow')
        self.highlight.pack(fill='both', expand=True)
        
        # Hide initially
        self.withdraw()

    def show_highlight(self, x, y, width, height):
        self.geometry(f'{width}x{height}+{x}+{y}')
        self.deiconify()

    def hide_highlight(self):
        self.withdraw()

class ScreenReader:
    def __init__(self, com_port='COM4'):
        self.arduino = serial.Serial(com_port, 9600)
        time.sleep(2)
        self.text_queue = queue.Queue()
        self.running = True
        
        # Initialize highlighting
        self.highlight_window = HighlightOverlay()
        self.current_blocks = []
        self.current_block_index = 0
        
        # Set up Tesseract
        pytesseract.pytesseract.tesseract_cmd = r'C:\Users\Comp\AppData\Local\Programs\Tesseract-OCR/tesseract.exe'
        
        # Start the processing thread
        self.process_thread = Thread(target=self._process_queue)
        self.process_thread.start()
        
        # Set up hotkeys
        self.setup_hotkeys()

    def setup_hotkeys(self):
        keyboard.add_hotkey('ctrl+alt+s', self.read_selected_text)
        keyboard.add_hotkey('ctrl+alt+w', self.read_active_window)
        keyboard.add_hotkey('ctrl+alt+c', self.read_clipboard)
        keyboard.add_hotkey('ctrl+alt+q', self.stop)
        keyboard.add_hotkey('ctrl+alt+p', self.pause_resume)
        keyboard.add_hotkey('ctrl+alt+right', self.next_block)
        keyboard.add_hotkey('ctrl+alt+left', self.previous_block)

    def get_text_blocks_from_image(self, image):
        """Extract text blocks with their positions from image"""
        blocks = []
        
        # Get detailed OCR data
        data = pytesseract.image_to_data(image, output_type=pytesseract.Output.DICT)
        n_boxes = len(data['text'])
        
        for i in range(n_boxes):
            if int(data['conf'][i]) > 60:  # Filter by confidence
                if data['text'][i].strip():
                    x, y = data['left'][i], data['top'][i]
                    w, h = data['width'][i], data['height'][i]
                    text = data['text'][i]
                    blocks.append(TextBlock(text, x, y, w, h))
        
        return blocks

    def get_active_window_text(self):
        """Get text from active window with position information"""
        try:
            hwnd = win32gui.GetForegroundWindow()
            bbox = win32gui.GetWindowRect(hwnd)
            screenshot = ImageGrab.grab(bbox)
            
            # Convert to OpenCV format for processing
            screenshot_np = np.array(screenshot)
            screenshot_cv = cv2.cvtColor(screenshot_np, cv2.COLOR_RGB2BGR)
            
            # Get text blocks with positions
            self.current_blocks = self.get_text_blocks_from_image(screenshot)
            self.current_block_index = 0
            
            # Return concatenated text for processing
            return ' '.join(block.text for block in self.current_blocks)
            
        except Exception as e:
            print(f"Error getting active window text: {e}")
            return ""

    def highlight_current_block(self):
        """Highlight the current text block"""
        if 0 <= self.current_block_index < len(self.current_blocks):
            block = self.current_blocks[self.current_block_index]
            hwnd = win32gui.GetForegroundWindow()
            window_x, window_y, _, _ = win32gui.GetWindowRect(hwnd)
            
            # Adjust coordinates relative to window position
            x = window_x + block.x
            y = window_y + block.y
            
            # Highlight block by showing an overlay
            self.highlight_window.show_highlight(x, y, block.width, block.height)
        else:
            self.highlight_window.hide_highlight()

    def next_block(self):
        """Move to next text block"""
        if self.current_blocks:
            self.current_block_index = min(self.current_block_index + 1, len(self.current_blocks) - 1)
            self.highlight_current_block()
            if self.current_block_index < len(self.current_blocks):
                self.process_text(self.current_blocks[self.current_block_index].text)

    def previous_block(self):
        """Move to previous text block"""
        if self.current_blocks:
            self.current_block_index = max(0, self.current_block_index - 1)
            self.highlight_current_block()
            if self.current_block_index >= 0:
                self.process_text(self.current_blocks[self.current_block_index].text)

    def pause_resume(self):
        """Pause or resume reading"""
        if not self.text_queue.empty():
            # Clear the queue to stop current reading
            while not self.text_queue.empty():
                self.text_queue.get()
        self.highlight_window.hide_highlight()

    def process_text(self, text):
        """Clean and process text before sending"""
        if not text:
            return
            
        # Clean the text
        text = re.sub(r'\s+', ' ', text)
        text = text.strip()
        
        # Split into sentences
        sentences = re.split(r'([.!?]+)', text)
        
        for sentence in sentences:
            if sentence.strip():
                self.text_queue.put(sentence)

    def _process_queue(self):
        """Process the text queue and send to Arduino"""
        while self.running:
            try:
                text = self.text_queue.get(timeout=1)
                self._send_to_arduino(text)
                self.highlight_current_block()
            except queue.Empty:
                continue

    def _send_to_arduino(self, text):
        """Send text to Arduino with proper timing"""
        try:
            for char in text:
                if not self.running:
                    break
                if char.isalnum() or char.isspace() or char in ".,!?-":
                    self.arduino.write(char.lower().encode())
                    time.sleep(0.5)
            
            self.arduino.write(b'\n')
            time.sleep(1)
            
        except Exception as e:
            print(f"Error sending to Arduino: {e}")

    def get_selected_text(self):
        """Fetch currently selected text by simulating a copy action"""
        pyautogui.hotkey('ctrl', 'c')  # Simulate copy action
        time.sleep(0.1)  # Wait a moment to ensure clipboard updates
        
        try:
            # Fetch the clipboard content
            return pyperclip.paste()
        except Exception as e:
            print(f"Error getting selected text: {e}")
            return ""

    def read_selected_text(self):
        """Read currently selected text"""
        text = self.get_selected_text()
        self.process_text(text)

    def read_active_window(self):
        """Read text from active window"""
        text = self.get_active_window_text()
        self.process_text(text)

    def read_clipboard(self):
        """Read text from clipboard"""
        try:
            win32clipboard.OpenClipboard()
            text = win32clipboard.GetClipboardData(win32con.CF_TEXT)
            if isinstance(text, bytes):
                text = text.decode('utf-8')
            win32clipboard.CloseClipboard()
            self.process_text(text)
        except Exception as e:
            print(f"Error reading clipboard: {e}")

    def stop(self):
        """Stop the screen reader"""
        self.running = False
        self.highlight_window.destroy()
        self.process_thread.join()
        self.arduino.close()

def main():
    print("Installing required packages...")
    import subprocess
    required_packages = [
        'pyautogui',
        'pytesseract',
        'pillow',
        'pyserial',
        'keyboard',
        'pywin32',
        'pywinauto',
        'opencv-python',
        'numpy',
        'pyperclip'
    ]
    
    for package in required_packages:
        try:
            subprocess.run(['pip', 'install', package], check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error installing {package}: {e}")
            return
    
    print("\nStarting screen reader...")
    reader = ScreenReader()
    print("\nScreen reader started. Use the following hotkeys:")
    print("Ctrl+Alt+S: Read selected text")
    print("Ctrl+Alt+W: Read text from active window")
    print("Ctrl+Alt+C: Read clipboard content")
    print("Ctrl+Alt+Right/Left: Navigate between text blocks")
    print("Ctrl+Alt+P: Pause/Resume")
    print("Ctrl+Alt+Q: Quit")

    reader.highlight_window.mainloop()

if __name__ == '__main__':
    main()
