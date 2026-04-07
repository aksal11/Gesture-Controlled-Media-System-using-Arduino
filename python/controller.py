import serial
import time
import pyautogui

PORT = 'COM3'
BAUD = 9600

try:
    arduino = serial.Serial(PORT, BAUD)
    time.sleep(2)
    print("Connected")
except:
    print("Connection failed")
    exit()

while True:
    try:
        incoming = arduino.readline().decode().strip()
        print("Received:", incoming)

        if incoming == "PLAY_PAUSE":
            pyautogui.press('space')

        elif incoming == "NEXT":
            pyautogui.press('right')

        elif incoming == "VOLUME_UP":
            pyautogui.press('volumeup')

        elif incoming == "VOLUME_DOWN":
            pyautogui.press('volumedown')

    except Exception as e:
        print("Error:", e)