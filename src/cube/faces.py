class CubeFaces:
    """A 3x3 Rubik's Cube state as length9 lists of sticker colors in row-major order"""

    def __init__(self, faces = None):
        if faces is not None:
            self.faces = faces
        else:
            self.faces = {
              'U': ['Y' for _ in range(3)] * 3,
              'D': ['W' for _ in range(3)] * 3,
              'L': ['B' for _ in range(3)] * 3,
              'R': ['G' for _ in range(3)] * 3,
              'F': ['R' for _ in range(3)] * 3,
              'B': ['O' for _ in range(3)] * 3,
            }
            
    def __repr__(self):
        return f"<CubeFaces faces={self.faces}>"