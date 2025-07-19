"""
cube.tables

Lookup tables for Rubik's Cube 3x3 Model:
- piece-permutation tables (CORNER_PERMUTATIONS, EDGE_PERMUTATIONS)
- orientation cycles (CORNER_ORIENTATION_CYCLES, EDGE_ORIENTATION_CYCLES)
- color mappings (FACE_COLORS, CORNER_COLORS, EDGE_COLORS)
- piece-to-face index maps (CORNER_FACE_MAPPINGS, EDGE_FACE_MAPPINGS)

Note:
    See the numbering diagrams in 'docs/visualization/' (e.g. 'corner_indices.png',
    'edge_indices.png', 'cube_numbering.png) for how each piece index is laid 
    out on the cube.
    See the notes in 'docs/orientation_details.md/' for logic behind edge 
    orientation and face priority.
"""

# CORNER_PERMUTATIONS
# 
# Mapping from face-turn notation to the four corner positions that cycle
# in clockwise order around the given face.
# 
# Keys:
# - "U", "U'", "U2"
# - "D", "D'", "D2"
# - "L", "L'", "L2"
# - "R", "R'", "R2"
# - "F", "F'", "F2"
# - "B", "B'", "B2"
# 
# Values:
# - A 4-tuple of corner positions (0-7), ordered clockwise as you look
# directly at the face
CORNER_PERMUTATIONS = {
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

# EDGE_PERMUTATIONS
# 
# Mapping from face-turn notation to the four edge positions that cycle in
# clockwise order around the given face.
# 
# Keys:
# - "U", "U'", "U2"
# - "D", "D'", "D2"
# - "L", "L'", "L2"
# - "R", "R'", "R2"
# - "F", "F'", "F2"
# - "B", "B'", "B2"
# 
# Values:
# - A 4-tuple of edge positions (0-11), ordered clockwise as you look
# directly at the face
EDGE_PERMUTATIONS = {
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

# CORNER_ORIENTATION_CYCLES
# 
# Mapping from face-turn notation to the oriented corner positions around 
# the given face.
# 
# See the details in 'docs/orientation_details.md/' for logic behind 
# corner orientation.
#
# Keys:
# - "U", "U'", "U2"
# - "D", "D'", "D2"
# - "L", "L'", "L2"
# - "R", "R'", "R2"
# - "F", "F'", "F2"
# - "B", "B'", "B2"
# 
# Values:
# - A 4-tuple of corner positions (0-7)
CORNER_ORIENTATION_CYCLES = {
    'L': (1, 0, 4, 7),
    'L\'': (1, 0, 4, 7),
    'R': (3, 2, 6, 5),
    'R\'': (3, 2, 6, 5),
    'F': (0, 3, 5, 4),
    'F\'': (0, 3, 5, 4),
    'B': (2, 1, 7, 6),
    'B\'': (2, 1, 7, 6),
}

# EDGE_ORIENTATION_CYCLES
# 
# Mapping from face-turn notation to the oriented edge positions that cycle
# in clockwise order around the given face.
# 
# See the details in 'docs/orientation_details.md/' for logic behind 
# edge orientation.
#
# Keys:
# - "L", "L'", "R", "R'"
# 
# Values:
# - A 12-tuple of edge positions (0-11)
EDGE_ORIENTATION_CYCLES = {
    'L': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    'L\'': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    'R': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
    'R\'': (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11),
}

# FACE_COLORS
# 
# Mapping from the face to the center-sticker color (color of the face when
# the cube is in a solved state)
#
# Keys:
# - "U", "D", "L", "R", "F", "B"
# 
# Values:
# - 'Y' (yellow), 'W' (white), 'B' (blue), 'G' (green), 'R' (red), 'O' (orange),
FACE_COLORS = {
    'U': 'Y',
    'D': 'W',
    'L': 'B',
    'R': 'G',
    'F': 'R',
    'B': 'O'
}

# CORNER_COLORS
# 
# Mapping from each corner index to the sticker colors of the corner
# itself, in clockwise order.
#
# See 'docs/visualization/corner_indices.png' for the numbering of corners.
#
# Keys:
# - int: corner index (0-7)
# 
# Values:
# - A 3-tuple of sticker colors from {'Y','W','B','G','R','O'},
# ordered clockwise as you look directly at that corner.
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

# EDGE_COLORS
# 
# Mapping from each edge-piece index to the sticker colors of the edge
# itself, starting with higher priority face.
#
# See 'docs/visualization/edge_indices.png' for the numbering of edges.
# See 'docs/orientation_details.md/' for logic behind edge orientation
# and face priority.
#
# Keys:
# - int: edge index (0-11)
# 
# Values:
# - A 2-tuple of sticker colors from {'Y','W','B','G','R','O'},
#   ordered by face priority.
EDGE_COLORS = {
    0: ('Y', 'R'),
    1: ('Y', 'B'),
    2: ('Y', 'O'),
    3: ('Y', 'G'),
    4: ('W', 'R'),
    5: ('W', 'G'),
    6: ('W', 'O'),
    7: ('W', 'B'),
    8: ('B', 'R'),
    9: ('G', 'R'),
    10: ('G', 'O'),
    11: ('B', 'O'),
}

# CORNER_FACE_MAPPINGS
# 
# Mapping from each corner index to the face locations of the corner stickers in 
# clockwise order.
#
# See 'docs/visualization/corner_indices.png' for the numbering of corners.
# See 'docs/visualization/cube_numbering.png' for the sticker-position numbering
#
# Keys:
# - int: corner index (0-7)
# 
# Values:
# - A length-3 mapping of each face letter face {'U','D','L','R','F','B'} to 
# a sticker position index (0-8), order clockwise as you look directly at 
# that corner.
CORNER_FACE_MAPPINGS = {
    0: {'U': 6, 'F': 0, 'L': 2},
    1: {'U': 0, 'L': 0, 'B': 2},
    2: {'U': 2, 'B': 0, 'R': 2},
    3: {'U': 8, 'R': 0, 'F': 2},
    4: {'D': 0, 'L': 8, 'F': 6},
    5: {'D': 2, 'F': 8, 'R': 6},
    6: {'D': 8, 'R': 8, 'B': 6},
    7: {'D': 6, 'B': 8, 'L': 6},
}

# EDGE_FACE_MAPPINGS
# 
# Mapping from each edge-piece index to the face locations of the edge stickers starting with
# highest priority face.
#
# See 'docs/visualization/edge_indices.png' for the numbering of edges.
# See 'docs/visualization/cube_numbering.png' for the sticker-position numbering
#
# Keys:
# - int: edge index (0-11)
# 
# Values:
# - A length-2 mapping of each face letter face {'U','D','L','R','F','B'} to 
# a sticker position index (0-8), ordered by face priority.
EDGE_FACE_MAPPINGS = {
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