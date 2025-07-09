from ursina import *
from cube.faces import CubeFaces

# Constants
ONE_THIRD = 1/3
ONE_HALF = 1/2

# Global state
cube = None
dragging = False
prev_mouse_pos = Vec2(0,0)

def my_update():
    global dragging, prev_mouse_pos, cube
    if held_keys['left mouse']:
        # Start dragging
        if not dragging:
            dragging = True
            prev_mouse_pos = mouse.position
        else:
            dx = mouse.position[0] - prev_mouse_pos[0]
            dy = mouse.position[1] - prev_mouse_pos[1]
            sensitivity = 100
            cube.rotation_y -= dx * sensitivity
            cube.rotation_x += dy * sensitivity
            prev_mouse_pos = mouse.position
    else:
        dragging = False

def run_app(rubiks_cube: CubeFaces):
    global cube
    app = Ursina()

    # Transparent cube container
    cube = Entity(model="cube", update=my_update, scale=4, color=(0,0,0,0))

    # Cube face entities
    face_list = {
        'U': Entity(parent=cube), 
        'D': Entity(parent=cube), 
        'L': Entity(parent=cube), 
        'R': Entity(parent=cube), 
        'F': Entity(parent=cube), 
        'B': Entity(parent=cube)
    }
    
    # Sticker positions for each face 
    # Faces front at z = -0.5
    sticker_pos = [
        (-ONE_THIRD,ONE_THIRD,-ONE_HALF),
        (0,ONE_THIRD,-ONE_HALF),
        (ONE_THIRD,ONE_THIRD,-ONE_HALF),
        (-ONE_THIRD,0,-ONE_HALF),
        (0,0,-ONE_HALF),
        (ONE_THIRD,0,-ONE_HALF),
        (-ONE_THIRD,-ONE_THIRD,-ONE_HALF),
        (0,-ONE_THIRD,-ONE_HALF),
        (ONE_THIRD,-ONE_THIRD,-ONE_HALF),
    ]
    
    color_map = {
        'Y': color.yellow,
        'W': color.white,
        'B': color.blue,
        'G': color.green,
        'R': color.red,
        'O': color.orange
    }

    # Create stickers on each face
    for key, value in rubiks_cube.faces.items():
        face = face_list.get(key)
        for i, sticker_color in enumerate(value):
            Entity(
                parent=face, 
                model="quad", 
                position=sticker_pos[i], 
                scale=ONE_THIRD, 
                color=color_map.get(sticker_color, color.black)
            )

    # Rotate faces into position
    face_list['U'].rotation_x = 90
    face_list['D'].rotation_x = -90
    face_list['L'].rotation_y = 90
    face_list['R'].rotation_y = -90
    face_list['B'].rotation_y = 180

    # Wireframe lines for cube outlines
    Entity(parent=cube, model="wireframe_cube", scale=1.001, color=color.black)

    for pos, rotation in [
        ((0, 0, ONE_HALF + -ONE_THIRD), (0, 0, 0)),
        ((0, 0, -ONE_HALF + ONE_THIRD), (0, 0, 0)),
        ((ONE_HALF + -ONE_THIRD, 0, 0), (0, 90, 0)),
        ((-ONE_HALF + ONE_THIRD, 0, 0), (0, 90, 0)),
        ((0, ONE_HALF + -ONE_THIRD, 0), (90, 0, 0)),
        ((0, -ONE_HALF + ONE_THIRD, 0), (90, 0, 0))
    ]:
        outline = Entity(
            parent=cube,
            model="wireframe_quad", 
            position=pos,
            scale=1.002,
            color=color.black
        )
        outline.rotation = rotation

    app.run()

if __name__ == '__main__':
    run_app(CubeFaces())