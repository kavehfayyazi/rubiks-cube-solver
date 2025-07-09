class CubeFaces:
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
    
    def print(self):
        for key, value in self.faces.items():
            print(f"{key}: {value}")