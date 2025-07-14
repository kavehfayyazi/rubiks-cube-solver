from .utils import switch_pieces, orient_corners, orient_edges
from .tables import CORNER_PERMUTATIONS, EDGE_PERMUTATIONS

class CubePieces:
    """A 3x3 Rubik's Cube state as lists of (piece_index, orientation) tuples
    
    Each corner is a tuple '(corner_id, orientation)' where 'orientation' ∈ {0,1,2}.
    Each edge is tuple '(edge_id, orientation)' where 'orientation' ∈ {0,1}.

    Attributes:
        corners (List[Tuple[int, int]]): 8 corner pieces with their current positions and orientations. 
        edges (List[Tuple[int, int]]): 12 edge pieces with their current positions and orientations.
    """

    def __init__(self, corners = None, edges = None):
        """Initialize either to a solved cube or from passed piece lists
        
        Args:
            corners (Optional[(List[Tuple[int, int]])]):
                A list of 8 corner tuples. If 'None', will be set to a solved state.
            edges (Optional[(List[Tuple[int, int]])]):
                A list of 12 edge tuples. If 'None', will be set to a solved state.
        """
        if corners is not None and edges is not None:
            self.corners = corners
            self.edges = edges
        else:
            CubePieces.default_cube(self)
    
    def default_cube(self):
        """Reset self to the solved-cube state"""
        self.corners = [(i, 0) for i in range(8)]
        self.edges = [(i, 0) for i in range(12)]

    def serialize(self) -> tuple:
        """Flatten the cube's state to a tuple of integers for hashing or comparisons.
        
        Returns:
            A tuple of length 40: the first 16 values are corner IDS/orientation
            followed by 24 edge IDS/orientations."""
        flat_list = []
        for piece in self.corners + self.edges:
            for x in piece:
                flat_list.append(x)
        return tuple(flat_list)
    
    def apply_move_inplace(self, move: str) -> "CubePieces":
        """Apply exactly one face move (e.g. "U" or "R'" or "F2") to self.
        
        This mutates self.corners and self.edges without making a new object.

        Args:
            move (str): A single face-turn string.
                - "U"  = 90° clockwise
                - "U'" = 90° counterclockwise
                - "U2" = 180° turn
        """
        # 1) permutate pieces
        switch_pieces(CORNER_PERMUTATIONS, self.corners, move)
        switch_pieces(EDGE_PERMUTATIONS,   self.edges,   move)

        # 2) update orientations
        orient_corners(self.corners, move)
        orient_edges(  self.edges,   move)

    def move(self, moves: str) -> "CubePieces":
        """Return a new CubePieces after applying a sequence of moves.

        Edge-case note: an empty string returns an identical cube:
        >>> cube.move("") == cube
        True
        
        Args:
            moves (str): A space-separated string of face-turns (e.g. "U R' F2").
                         Extra whitespace is ignored.

        Returns:
            A new CubePieces instance with all moves applied in left-to-right order. 
        """
        # copy the pieces-lists of self
        new_corners = self.corners.copy()
        new_edges   = self.edges.copy()

        cube = CubePieces(new_corners, new_edges)
        for m in moves.strip().split():
            cube.apply_move_inplace(m)
        return cube

    def __repr__(self):
        """Unambiguous representation for debugging"""
        return f"<CubePieces corners={self.corners} edges={self.edges}>"