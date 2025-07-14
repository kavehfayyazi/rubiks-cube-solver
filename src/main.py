from cube import *
from gui import *

if __name__ == '__main__':
    test_faces = {
        'U': ['R', 'Y', 'G', 'B', 'W', 'R', 'Y', 'G', 'B'],
        'D': ['R', 'Y', 'G', 'B', 'W', 'R', 'Y', 'G', 'B'],
        'L': ['R', 'Y', 'G', 'B', 'W', 'R', 'Y', 'G', 'B'],
        'R': ['R', 'Y', 'G', 'B', 'W', 'R', 'Y', 'G', 'B'],
        'F': ['R', 'Y', 'G', 'B', 'W', 'R', 'Y', 'G', 'B'],
        'B': ['R', 'Y', 'G', 'B', 'W', 'R', 'Y', 'G', 'B']
    }

    cube = pieces.CubePieces()
    altered_cube = cube.move("U F R B D2 L U' B2")
    app.run_app(translator.pieces_to_faces(altered_cube))