from cube import *
from gui import *

if __name__ == '__main__':
    test_faces = {
        'U': ['Y', 'B', 'Y', 'O', 'Y', 'R', 'B', 'G', 'W'],
        'D': ['W', 'R', 'G', 'W', 'W', 'Y', 'O', 'W', 'Y'],
        'L': ['G', 'Y', 'Y', 'R', 'B', 'G', 'W', 'O', 'R'],
        'R': ['B', 'G', 'G', 'B', 'G', 'O', 'Y', 'R', 'R'],
        'F': ['O', 'Y', 'R', 'W', 'R', 'O', 'G', 'B', 'R'],
        'B': ['O', 'Y', 'O', 'G', 'O', 'W', 'B', 'B', 'B']
    }
    app.run_app(faces.CubeFaces(test_faces))
    # app.run_app(faces.CubeFaces())

# if __name__ == '__main__':
#     cube1 = faces.CubeFaces()
#     cube1.print()
#     cube2 = pieces.CubePieces()
#     cube2.print()