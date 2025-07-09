from ursina import *

cube = None

def run_app():
    global cube
    app = Ursina()

    cube = Entity(model="cube", update=my_update, scale=4, color=color.gold)
    line_1 = Entity(parent=cube, model="wireframe_cube", update=my_update, scale=1.001, color=color.black)
    line_UL1 = Entity(parent=cube, model="wireframe_quad", update=my_update, position=(0,0,0.5 + -1/3), scale=1.002, color=color.black)
    line_UL2 = Entity(parent=cube, model="wireframe_quad", update=my_update, position=(0,0,-0.5 + 1/3), scale=1.002, color=color.black)
    line_UF1 = Entity(parent=cube, model="wireframe_quad", update=my_update, position=(0.5 + -1/3,0,0), scale=1.002, color=color.black)
    line_UF2 = Entity(parent=cube, model="wireframe_quad", update=my_update, position=(-0.5 + 1/3,0,0), scale=1.002, color=color.black)
    line_UF1.rotation_y = 90
    line_UF2.rotation_y = 90
    line_LF1 = Entity(parent=cube, model="wireframe_quad", update=my_update, position=(0,0.5 + -1/3,0), scale=1.002, color=color.black)
    line_LF2 = Entity(parent=cube, model="wireframe_quad", update=my_update, position=(0,-0.5 + 1/3,0), scale=1.002, color=color.black)
    line_LF1.rotation_x = 90
    line_LF2.rotation_x = 90
    
    app.run()
    
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

if __name__ == '__main__':
    run_app()