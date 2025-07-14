class CubeFaces:
    """A 3x3 Rubik's Cube state as length9 lists of sticker colors in row-major order.
    
    Attributes:
        faces (Dict[str, List[str]]): All 6 faces with 9 sticker colors each.
    """

    def __init__(self, faces = None):
        """Initialize either to a solved cube or from existing row-major sticker lists.

        Args:
            faces (Optional[Dict[str, List[str]]]):
                A mapping from face names to their 3x3 sticker arrays in row-major order. 
                Keys must be each of 'U', 'D', 'L', 'R', 'F', 'B', and each value a list 
                of exactly 9 color codes (e.g. ['Y','Y','Y','Y','Y','Y','Y','Y','Y',]). 
                If 'None', sets up a solved cube with standard face colors:
                    U=Y (up: yellow), D=W (down: white), L=B (left: blue),
                    R=G (red: green), F=R (face: red), B=O (back: orange)
        """
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
        """Unambiguous representation for debugging"""
        return f"<CubeFaces faces={self.faces}>"