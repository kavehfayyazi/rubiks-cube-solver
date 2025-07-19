from .utils import switch_pieces, orient_corners, orient_edges
from .tables import CORNER_PERMUTATIONS, EDGE_PERMUTATIONS

def tuple_to_cube(tuple):
    return CubePieces(tuple[0], tuple[1])

class CubePieces:
    """A 3x3 Rubik's Cube state as a tuple of corner positions and a tuple of orientations respectively. 
    
    Each corner has a corner_id and an orientation at the same index where 'orientation' ∈ {0,1,2}.
    Each edge has an edge_id and an orientation where 'orientation' ∈ {0,1}.

    Attributes:
        corners (Tuple[Tuple[int], Tuple[int]]): 8 corner pieces with their current positions and orientations. 
        edges (Tuple[Tuple[int], Tuple[int]]): 12 edge pieces with their current positions and orientations.
    """

    def __init__(self, corners = None, edges = None):
        """Initialize either to a solved cube or from passed piece lists
        
        Args:
            corners (Optional[(Tuple[Tuple[int], Tuple[int]])]):
                A tuple containing a tuple of corner positions and a tuple of orientations. If 'None', will be set to a solved state.
            corners (Optional[(Tuple[Tuple[int], Tuple[int]])]):
                A tuple containing a tuple of edge positions and a tuple of orientations. If 'None', will be set to a solved state.
        """
        if corners is not None and edges is not None:
            self.corners = corners
            self.edges = edges
        else:
            CubePieces.default_cube(self)
    
    def default_cube(self):
        """Reset self to the solved-cube state"""
        self.corners = tuple(range(8)), (0,) * 8
        self.edges = tuple(range(12)), (0,) * 12
    
    def apply_move_inplace(self, move: str) -> None:
        """Apply exactly one face move (e.g. "U" or "R'" or "F2") to self.
        
        This mutates self.corners and self.edges without making a new object.

        Args:
            move (str): A single face-turn string.
                - "U"  = 90° clockwise
                - "U'" = 90° counterclockwise
                - "U2" = 180° turn
        """
        corner_pos, corner_ori = list(self.corners[0]), list(self.corners[1])
        edge_pos, edge_ori = list(self.edges[0]), list(self.edges[1])

        # 1) permutate pieces
        switch_pieces(CORNER_PERMUTATIONS, corner_pos, move)
        switch_pieces(EDGE_PERMUTATIONS,   edge_pos,   move)
        switch_pieces(CORNER_PERMUTATIONS, corner_ori, move)
        switch_pieces(EDGE_PERMUTATIONS,   edge_ori,   move)

        # 2) update orientations
        orient_corners(corner_ori, move)
        orient_edges(  edge_ori,   move)

        self.corners = (tuple(corner_pos), tuple(corner_ori))
        self.edges = (tuple(edge_pos), tuple(edge_ori))

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
        new_corners = (self.corners[0], self.corners[1])
        new_edges = (self.edges[0], self.edges[1])

        cube = CubePieces(new_corners, new_edges)
        for m in moves.strip().split():
            cube.apply_move_inplace(m)
        return cube
    
    def is_solved(self):
        print(self.corners)
        print((tuple(range(8)), (0,) * 8))
        return (
            self.corners == (tuple(range(8)), (0,) * 8)
            and 
            self.edges == (tuple(range(12)), (0,) * 12)
        )

    def return_pieces(self):
        return (self.corners, self.edges)
    
    def __repr__(self):
        """Unambiguous representation for debugging"""
        return f"<CubePieces corners={self.corners} edges={self.edges}>"