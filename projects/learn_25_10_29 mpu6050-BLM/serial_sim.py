import serial
import time

# === CONFIGURATION ===
bt_port = 'COM3'      # Replace with your Bluetooth COM port
baud_rate = 38400     # Default baud rate for HC-05 in normal mode or AT mode
timeout = 1           # seconds

# === CONNECT TO BLUETOOTH ===
try:
    ser = serial.Serial(bt_port, baud_rate, timeout=timeout)
    print(f"Connected to {bt_port} at {baud_rate} baud.")
except Exception as e:
    print("Failed to connect:", e)
    exit()

print("Type your commands below. Type 'exit' to quit.")

# === MAIN LOOP ===
while True:
    # Read incoming data
    if ser.in_waiting > 0:
        data = ser.readline().decode('utf-8', errors='ignore').strip()
        if data:
            print(f"< {data}")

    # Send user input
    user_input = input("> ")
    if user_input.lower() == 'exit':
        break

    # Send command to Bluetooth
    ser.write((user_input + '\r\n').encode())  # Add CRLF like Serial Monitor

ser.close()
print("Disconnected.")
