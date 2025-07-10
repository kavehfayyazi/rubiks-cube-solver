from .utils import switch_pieces, orient_corners, orient_edges
from .tables import SWITCH_CORNERS_TABLE, SWITCH_EDGES_TABLE, FLIP_CORNERS_TABLE, FLIP_EDGES_TABLE

class CubePieces:
    def __init__(self, corners = None, edges = None):
        if corners is not None and edges is not None:
            self.corners = corners
            self.edges = edges
        else:
            CubePieces.defaultCube(self)
    
    def defaultCube(self):
        self.corners = [(i, 0) for i in range(8)]
        self.edges = [(i, 0) for i in range(12)]

    def serialize(self) -> tuple:
        flat_list = []
        for piece in self.corners + self.edges:
            for x in piece:
                flat_list.append(x)
        return tuple(flat_list)
        
    def move(self, move) -> "CubePieces":
        new_corners = self.corners.copy()
        new_edges = self.edges.copy()

        # Permute pieces
        switch_pieces(SWITCH_CORNERS_TABLE, new_corners, move)
        switch_pieces(SWITCH_EDGES_TABLE, new_edges, move)

        # Update orientations
        orient_corners(FLIP_CORNERS_TABLE, new_corners, move)
        orient_edges(FLIP_EDGES_TABLE, new_edges, move)

        return CubePieces(new_corners, new_edges)

    def print(self):
        print(self.corners)
        print(self.edges)