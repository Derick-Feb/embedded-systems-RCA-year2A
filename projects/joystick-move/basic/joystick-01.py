import pygame
import serial
import serial.tools.list_ports
import time

pygame.init()

# Window setup
win_width, win_height = 800, 600
win = pygame.display.set_mode((win_width, win_height))
pygame.display.set_caption("Joystick Game")

# Character setup
character_size = 50
character_color = (0, 255, 0)  # Initial color (green)
character_x, character_y = win_width // 2, win_height // 2
character_speed = 5

# Serial communication setup
arduino_port = "COM5"  # Replace with your Arduino port
baud_rate = 9600

# Attempt to connect to Arduino
try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    time.sleep(2)  # Wait for Arduino to initialize
except serial.SerialException:
    print(f"Could not open port {arduino_port}. Make sure no other program is using it.")
    exit()

running = True

# Store the character's previous position
prev_x, prev_y = character_x, character_y

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Read serial data safely
    if ser.in_waiting > 0:
        raw_line = ser.readline().decode(errors='ignore').strip()
        if raw_line:  # Skip empty lines
            data = raw_line.split(',')
            if len(data) == 3:
                try:
                    joy_x, joy_y, button_state = map(int, data)
                    print(f"X: {joy_x}, Y: {joy_y}, Button: {button_state}")
                except ValueError:
                    continue  # Skip malformed lines
            else:
                continue  # Skip if data is not 3 values
        else:
            continue

        # Calculate new character position based on joystick input
        dx = int((joy_x - 512) / 512 * character_speed)
        dy = int((joy_y - 512) / 512 * character_speed)

        new_x = character_x + dx
        new_y = character_y + dy

        # Ensure the character stays within the screen boundaries
        new_x = max(character_size // 2, min(win_width - character_size // 2, new_x))
        new_y = max(character_size // 2, min(win_height - character_size // 2, new_y))

        # Update character position only if it has moved
        if (new_x, new_y) != (prev_x, prev_y):
            character_x, character_y = new_x, new_y
            prev_x, prev_y = character_x, character_y

        # Change character color based on buttonState
        # Arduino button: 0 = pressed, 1 = not pressed
        character_color = (255, 0, 0) if button_state == 0 else (0, 0, 255)

    win.fill((255, 255, 255))
    pygame.draw.circle(win, character_color, (character_x, character_y), character_size // 2)
    pygame.display.flip()

# Clean up
ser.close()
pygame.quit()