from .utils import switch_pieces, orient_corners, orient_edges
from .tables import (
    SWITCH_CORNERS_TABLE, 
    SWITCH_EDGES_TABLE, 
    FLIP_CORNERS_TABLE, 
    FLIP_EDGES_TABLE
)

class CubePieces:
    """A 3x3 Rubik's Cube state as lists of (piece_index, orientation) tuples"""

    def __init__(self, corners = None, edges = None):
        """Initialize either to a solved cube or from passed piece lists"""
        if corners is not None and edges is not None:
            self.corners = corners
            self.edges = edges
        else:
            CubePieces.default_cube(self)
    
    def default_cube(self):
        self.corners = [(i, 0) for i in range(8)]
        self.edges = [(i, 0) for i in range(12)]

    def serialize(self) -> tuple:
        flat_list = []
        for piece in self.corners + self.edges:
            for x in piece:
                flat_list.append(x)
        return tuple(flat_list)
    
    def apply_move_inplace(self, move) -> "CubePieces":
        """
        Apply exactly one face move (e.g. "U" or "R'" or "F2") to self.
        Does NOT return a new CubePieces
        """
        # 1) permutate pieces
        switch_pieces(SWITCH_CORNERS_TABLE, self.corners, move)
        switch_pieces(SWITCH_EDGES_TABLE,   self.edges,   move)

        # 2) update orientations
        orient_corners(self.corners, move)
        orient_edges(  self.edges,   move)

    def move(self, moves: str) -> "CubePieces":
        """
        Return a new CubePieces that results from applying each move
        in a space-separated string 'moves'
        """
        new_corners = self.corners.copy()
        new_edges   = self.edges.copy()

        cube = CubePieces(new_corners, new_edges)

        for m in moves.strip().split():
            cube.apply_move_inplace(m)
        
        return cube

    def __repr__(self):
        return f"<CubePieces corners={self.corners} edges={self.edges}>"