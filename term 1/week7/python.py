import serial
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import matplotlib.animation as animation

# === CONFIGURATION ===
bt_port = 'COM4'       # Change to your Bluetooth COM port
baud_rate = 38400      # Keep the same baud rate as your HC-05
timeout = 1

try:
    ser = serial.Serial(bt_port, baud_rate, timeout=timeout)
    print(f"✅ Connected to {bt_port} at {baud_rate} baud.")
except Exception as e:
    print("❌ Failed to connect:", e)
    exit()

# === 3D CUBE SETUP ===
# Define cube vertices
vertices = np.array([
    [-1, -1, -1], [1, -1, -1], [1, 1, -1], [-1, 1, -1],  # bottom face
    [-1, -1, 1], [1, -1, 1], [1, 1, 1], [-1, 1, 1]       # top face
])

# Define cube faces (each face is defined by 4 vertex indices)
faces = [
    [0, 1, 2, 3],  # bottom
    [4, 5, 6, 7],  # top
    [0, 1, 5, 4],  # front
    [2, 3, 7, 6],  # back
    [1, 2, 6, 5],  # right
    [0, 3, 7, 4]   # left
]

# Initialize rotation angles
rotation_x, rotation_y, rotation_z = 0, 0, 0
speed = 0.0001  # Sensitivity multiplier for direct mapping

# Create matplotlib figure and 3D axis
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim([-2, 2])
ax.set_ylim([-2, 2])
ax.set_zlim([-2, 2])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('MPU6050 3D Cube Visualization')

def rotate_point(point, rx, ry, rz):
    """Rotate a 3D point around x, y, z axes"""
    # Rotation matrix for X axis
    Rx = np.array([
        [1, 0, 0],
        [0, np.cos(rx), -np.sin(rx)],
        [0, np.sin(rx), np.cos(rx)]
    ])
    
    # Rotation matrix for Y axis
    Ry = np.array([
        [np.cos(ry), 0, np.sin(ry)],
        [0, 1, 0],
        [-np.sin(ry), 0, np.cos(ry)]
    ])
    
    # Rotation matrix for Z axis
    Rz = np.array([
        [np.cos(rz), -np.sin(rz), 0],
        [np.sin(rz), np.cos(rz), 0],
        [0, 0, 1]
    ])
    
    # Apply rotations
    return Rz @ Ry @ Rx @ point

def update_cube(frame):
    global rotation_x, rotation_y, rotation_z
    
    # Read accelerometer data
    if ser.in_waiting > 0:
        try:
            raw = ser.readline().decode('utf-8', errors='ignore').strip()
            
            if raw.count(',') == 2:
                parts = raw.split(',')
                if all(p.strip().lstrip('-').isdigit() for p in parts):
                    accel_x, accel_y, accel_z = map(int, parts)
                    
                    # Map accelerometer data directly to rotation angles (no accumulation)
                    rotation_x = accel_y * speed  # Pitch
                    rotation_y = accel_x * speed  # Roll
                    rotation_z = accel_z * speed  # Yaw
                    
                    print(f"Accel: ax={accel_x}, ay={accel_y}, az={accel_z} | Rotation: x={rotation_x:.2f}, y={rotation_y:.2f}, z={rotation_z:.2f}")
                else:
                    print(f"⚠️ Non-numeric data skipped: {raw}")
            else:
                print(f"⚠️ Bad line skipped: {raw}")
                
        except Exception as e:
            print("⚠️ Error reading data:", e)
    
    # Clear the axis
    ax.clear()
    ax.set_xlim([-2, 2])
    ax.set_ylim([-2, 2])
    ax.set_zlim([-2, 2])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title('MPU6050 3D Cube Visualization')
    
    # Rotate vertices
    rotated_vertices = np.array([rotate_point(vertex, rotation_x, rotation_y, rotation_z) for vertex in vertices])
    
    # Create cube faces
    cube_faces = []
    colors = ['red', 'green', 'blue', 'yellow', 'orange', 'purple']
    
    for i, face in enumerate(faces):
        face_vertices = [rotated_vertices[j] for j in face]
        cube_faces.append(face_vertices)
    
    # Add faces to the plot
    cube_collection = Poly3DCollection(cube_faces, alpha=0.7, facecolors=colors, edgecolors='black')
    ax.add_collection3d(cube_collection)
    
    return ax,

# Start animation
print("🎮 Starting 3D cube visualization. Move your MPU6050 to rotate the cube!")
ani = animation.FuncAnimation(fig, update_cube, interval=50, blit=False, cache_frame_data=False)

try:
    plt.show()
except KeyboardInterrupt:
    print("\n🛑 Stopping visualization...")

ser.close()
print("Disconnected.")