from cube import *
from gui import *

if __name__ == '__main__':
    cube = pieces.CubePieces()
    altered_cube = cube.move("U F R B D2 L U' B2")
    app.run_app(translator.pieces_to_faces(altered_cube))