"""
cube.tables

Lookup tables for Rubik's Cube 3x3 Model:
- piece-permutation tables (SWITCH_CORNERS_TABLE, SWITCH_EDGES_TABLE)
- orientation flip tables (FLIP_CORNERS_TABLE, FLIP_EDGES_TABLES)
- color mappings (FACE_COLORS, CORNER_COLORS, EDGE_COLORS)
- piece-to-face index maps (PIECES_TO_FACES_*)

Everything here is purely data; no logic.
"""

SWITCH_CORNERS_TABLE = {
    'U': (0, 1, 2, 3),
    'U\'': (0, 1, 2, 3),
    'U2': (0, 1, 2, 3),
    'D': (4, 5, 6, 7),
    'D\'': (4, 5, 6, 7),
    'D2': (4, 5, 6, 7),
    'L': (1, 0, 4, 7),
    'L\'': (1, 0, 4, 7),
    'L2': (1, 0, 4, 7),
    'R': (3, 2, 6, 5),
    'R\'': (3, 2, 6, 5),
    'R2': (3, 2, 6, 5),
    'F': (0, 3, 5, 4),
    'F\'': (0, 3, 5, 4),
    'F2': (0, 3, 5, 4),
    'B': (2, 1, 7, 6),
    'B\'': (2, 1, 7, 6),
    'B2': (2, 1, 7, 6),
}

FLIP_CORNERS_TABLE = {
    'L': (1, 0, 4, 7),
    'L\'': (1, 0, 4, 7),
    'R': (3, 2, 6, 5),
    'R\'': (2, 4, 8, 6),
    'F': (0, 3, 5, 4),
    'F\'': (0, 3, 5, 4),
    'B': (2, 1, 7, 6),
    'B\'': (2, 1, 7, 6),
}

SWITCH_EDGES_TABLE = {
    'U': (0, 1, 2, 3),
    'U\'': (0, 1, 2, 3),
    'U2': (0, 1, 2, 3),
    'D': (4, 5, 6, 7),
    'D\'': (4, 5, 6, 7),
    'D2': (4, 5, 6, 7),
    'L': (1, 8, 7, 11),
    'L\'': (1, 8, 7, 11),
    'L2': (1, 8, 7, 11),
    'R': (3, 10, 5, 9),
    'R\'': (3, 10, 5, 9),
    'R2': (3, 10, 5, 9),
    'F': (0, 9, 4, 8),
    'F\'': (0, 9, 4, 8),
    'F2': (0, 9, 4, 8),
    'B': (2, 11, 6, 10),
    'B\'': (2, 11, 6, 10),
    'B2': (2, 11, 6, 10),
}

FLIP_EDGES_TABLE = {
    'L': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    'L\'': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    'R': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    'R\'': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
}

FACE_COLORS = {
    'U': 'Y',
    'D': 'W',
    'L': 'B',
    'R': 'G',
    'F': 'R',
    'B': 'O'
}

FACES_CORNER_COLORS = {
    0: ('U', 'F', 'L'),  # ULF
    1: ('U', 'B', 'L'),  # ULB
    2: ('U', 'B', 'R'),  # URB
    3: ('U', 'F', 'R'),  # URF
    4: ('D', 'F', 'L'),  # DLF
    5: ('D', 'F', 'R'),  # DRF
    6: ('D', 'B', 'R'),  # DRB
    7: ('D', 'B', 'L'),  # DLB
}

FACES_EDGE_COLORS = {
    0: ('U', 'F'),  # UF
    1: ('U', 'L'),  # UL
    2: ('U', 'B'),  # UB
    3: ('U', 'R'),  # UR
    4: ('D', 'F'),  # DF
    5: ('D', 'R'),  # DR
    6: ('D', 'B'),  # DB
    7: ('D', 'L'),  # DL
    8: ('F', 'L'),  # LF
    9: ('F', 'R'),  # RF
    10: ('B', 'R'), # RB
    11: ('B', 'L'), # LB
}

CORNER_COLORS = {
    0: ('Y', 'R', 'B'),  # UFL
    1: ('Y', 'B', 'O'),  # UBL
    2: ('Y', 'O', 'G'),  # UBR
    3: ('Y', 'G', 'R'),  # UFR
    4: ('W', 'B', 'R'),  # DFL
    5: ('W', 'R', 'G'),  # DFR
    6: ('W', 'G', 'O'),  # DBR
    7: ('W', 'O', 'B'),  # DBL
}

EDGE_COLORS = {
    0: ('Y', 'R'),  # UF
    1: ('Y', 'B'),  # UL
    2: ('Y', 'O'),  # UB
    3: ('Y', 'G'),  # UR
    4: ('W', 'R'),  # DF
    5: ('W', 'G'),  # DR
    6: ('W', 'O'),  # DB
    7: ('W', 'B'),  # DL
    8: ('B', 'R'),  # FL
    9: ('G', 'R'),  # FR
    10: ('G', 'O'), # BR
    11: ('B', 'O'), # BL
}

PIECES_TO_FACES_CORNERS_LOCATIONS = {
    0: {'U': 6, 'F': 0, 'L': 2},
    1: {'U': 0, 'L': 0, 'B': 2},
    2: {'U': 2, 'B': 0, 'R': 2},
    3: {'U': 8, 'R': 0, 'F': 2},
    4: {'D': 0, 'L': 8, 'F': 6},
    5: {'D': 2, 'F': 8, 'R': 6},
    6: {'D': 8, 'R': 8, 'B': 6},
    7: {'D': 6, 'B': 8, 'L': 6},
}

PIECES_TO_FACES_EDGES_LOCATIONS = {
    0: {'U': 7, 'F': 1},
    1: {'U': 3, 'L': 1},
    2: {'U': 1, 'B': 1},
    3: {'U': 5, 'R': 1},
    4: {'D': 1, 'F': 7},
    5: {'D': 5, 'R': 7},
    6: {'D': 7, 'B': 7},
    7: {'D': 3, 'L': 7},
    8: {'L': 5, 'F': 3},
    9: {'R': 3, 'F': 5},
    10: {'R': 5, 'B': 3},
    11: {'L': 3, 'B': 5},
}