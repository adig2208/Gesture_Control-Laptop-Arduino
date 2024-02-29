import serial
import time
import pyautogui

def init_serial_connection(port='COM5', baudrate=9600, timeout=3):
    try:
        ser = serial.Serial(port, baudrate)
        time.sleep(timeout)  
        return ser
    except serial.SerialException as e:
        print(f"Error opening serial port {port}: {e}")
        return None

gesture_actions = {
    'Scroll_Up': lambda: pyautogui.scroll(100),
    'Scroll_Down': lambda: pyautogui.scroll(-100),
    'Forward': lambda: pyautogui.hotkey('browserforward'),
    'Rewind': lambda: pyautogui.hotkey('browserback'),
    'Change_Tab': lambda: pyautogui.hotkey('ctrl', 'tab'),
    'Enter': lambda: pyautogui.press('enter'),
    'Drop_Down': lambda: pyautogui.click(1880, 69),
    'Volume_Up': lambda: pyautogui.press('volumeup'),
    'Volume_Down': lambda: pyautogui.press('volumedown')
}

def main_loop(serial_connection):
    if serial_connection is None:
        return
    try:
        while True:
            val = serial_connection.readline().decode().strip()
            for gesture, action in gesture_actions.items():
                if gesture in val:
                    action()
                    print(f"Executed action for gesture: {val}")
    except KeyboardInterrupt:
        print("Program exited by user.")
    except serial.SerialException as e:
        print(f"Serial communication error: {e}")

if __name__ == '__main__':
    ser = init_serial_connection()
    main_loop(ser)
