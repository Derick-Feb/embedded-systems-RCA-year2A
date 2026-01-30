from vpython import sphere, cylinder, vector, color, rate

head = sphere(pos=vector(0,1.8,0), radius=0.3, color=color.yellow)
body = cylinder(pos=vector(0,0.8,0), axis=vector(0,1,0), radius=0.2, color=color.blue)

left_arm = cylinder(pos=vector(-0.4,1.5,0), axis=vector(-0.4,-0.2,0), radius=0.08, color=color.red)
right_arm = cylinder(pos=vector(0.4,1.5,0), axis=vector(0.4,-0.2,0), radius=0.08, color=color.red)

left_leg = cylinder(pos=vector(-0.1,0,0), axis=vector(0,-0.8,0), radius=0.1, color=color.green)
right_leg = cylinder(pos=vector(0.1,0,0), axis=vector(0,-0.8,0), radius=0.1, color=color.green)

enRotation = False
while enRotation:
    rate(50)
    head.rotate(angle=0.02, axis=vector(0,1,0))
    body.rotate(angle=0.02, axis=vector(0,1,0))
    left_arm.rotate(angle=0.02, axis=vector(0,1,0))
    right_arm.rotate(angle=0.02, axis=vector(0,1,0))
    left_leg.rotate(angle=0.02, axis=vector(0,1,0))
    right_leg.rotate(angle=0.02, axis=vector(0,1,0))
