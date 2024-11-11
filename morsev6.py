import serial
import time
import pyautogui

SERIAL_PORT = 'COM5'  # Update with your correct COM port
BAUD_RATE = 9600

def open_serial_connection():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
        time.sleep(2)  # Wait for the connection to establish
        return ser
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")
        return None

def handle_morse_input(data):
    # Extract the first character if it's a dot or dash
    if data.startswith('.') or data.startswith('-'):
        morse_char = data[0]  # Grab the first character
        print(f"Handling Morse input: {morse_char}")
        
        if morse_char == '.':
            pyautogui.write('.', interval=0.1)  # Simulate typing a dot with delay
        elif morse_char == '-':
            pyautogui.write('-', interval=0.1)  # Simulate typing a dash with delay
    else:
        print(f"Invalid input: {data}")  # Debugging line

def main():
    print("Starting Morse code receiver...")

    ser = open_serial_connection()
    if not ser:
        return

    print("Listening for Morse code...")

    while True:
        if ser.in_waiting > 0:
            # Read incoming data
            data = ser.readline().decode('utf-8').strip()
            print(f"Received: {data}")  # Print received data for debugging
            
            # Ignore unnecessary strings (like startup messages)
            if data in ["Ready to detect Morse code!", "Closed"]:
                continue

            if data:
                handle_morse_input(data)

        time.sleep(0.1)  # Small delay to reduce CPU usage

if __name__ == "__main__":
    main()
