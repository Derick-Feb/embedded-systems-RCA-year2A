import pygame
import serial
import time
import math

ser = serial.Serial('COM4', 9600, timeout=1)
time.sleep(2)

pygame.init()
screen = pygame.display.set_mode((600, 400))
pygame.display.set_caption("MPU6050 Controlled Sprite")
clock = pygame.time.Clock()

x, y = 300, 200
sprite_color = (255, 0, 0)
sprite_radius = 20

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    if ser.in_waiting:
        line = ser.readline().decode('utf-8').strip()
        if ',' in line:
            try:
                pitch, roll = map(float, line.split(','))
                if math.isnan(pitch) or math.isnan(roll):
                    continue
            except ValueError:
                continue

            x += int(-roll / 2)
            y += int(pitch / 2)

            x = max(0, min(600, x))
            y = max(0, min(400, y))

    screen.fill((0, 0, 0))
    pygame.draw.circle(screen, sprite_color, (x, y), sprite_radius)
    pygame.display.flip()
    clock.tick(30)

pygame.quit()
ser.close()
