"""
cube.translator

Convert from CubePieces (position + orientation)
to CubeFaces (3x3 sticker view)

Public API:
- pieces_to_faces(cp: CubePieces) -> CubeFaces
"""

from .pieces import CubePieces
from .faces import CubeFaces
from .tables import (
    FACE_COLORS, 
    CORNER_FACE_MAPPINGS, 
    CORNER_COLORS, 
    EDGE_FACE_MAPPINGS, 
    EDGE_COLORS,
)
from .utils import rotate_sublist, find_rotation_offset

def pieces_to_faces(cp: CubePieces) -> CubeFaces:
    """Lays out all stickers from a piece-oriented cube into 3x3 (length-9) face arrays.

    Args:
        cp (CubePieces): Tuple of position and orientation tuple lists.
    Returns:
        CubeFaces: Lists of length-9 sticker colors in row-major order.
    """

    faces = {face: ['' for _ in range(3)] * 3 for face in FACE_COLORS}

    # Center stickers
    for face in FACE_COLORS:
        faces[face][4] = FACE_COLORS[face]

    # Corner stickers
    corner_pos, corner_ori = cp.corners
    for corner_num, (pos, orientation) in enumerate(zip(corner_pos, corner_ori)):
        mapping = CORNER_FACE_MAPPINGS[corner_num]
        colors = list(CORNER_COLORS[pos])
        # Rotate the color tuple 'orientation' times
        oriented = colors[-orientation:] + colors[:-orientation]
        for (face, loc), sticker in zip(mapping.items(), oriented):
            faces[face][loc] = sticker

    # Edge stickers
    edge_pos, edge_ori = cp.edges
    for edge_num, (pos, orientation) in enumerate(zip(edge_pos, edge_ori)):
        mapping = EDGE_FACE_MAPPINGS[edge_num]
        colors = list(EDGE_COLORS[pos])
        # Rotate the color tuple if orientation == 1
        oriented = colors[-orientation:] + colors[:-orientation]
        for (face, loc), sticker in zip(mapping.items(), oriented):
            faces[face][loc] = sticker

    return CubeFaces(faces)

def faces_to_pieces(cf: CubeFaces) -> CubePieces:
    """Lays out all stickers from a face-oriented cube into position + orientation tuple lists.

    Args:
        cf (CubeFaces): Lists of length-9 sticker colors in row-major order.
    Returns:
        CubePieces: Tuple of position and orientation tuple lists.
    """
    # Corner stickers
    corner_pos, corner_ori = [-1] * 8, [0] * 8
    corner_edge, corner_edge = [-1] * 8, [0] * 8
    corners = ()
    for corner_pos_on_cube, corner in CORNER_FACE_MAPPINGS.items():
        corner_colors = []
        for face_mapping, index in corner.items():
            corner_colors.append(cf.faces[face_mapping][index])
        corner_piece_index = -1
        for corner_num, colors in CORNER_COLORS.items():
            if set(corner_colors) == set(colors):
                corner_piece_index = corner_num
        ori = find_rotation_offset(tuple(corner_colors), CORNER_COLORS[corner_piece_index])
        corner_pos[corner_pos_on_cube] = corner_piece_index
        corner_edge[corner_pos_on_cube] = ori
        corners = (tuple(corner_pos), tuple(corner_edge))

    # Edge stickers
    edge_pos, edge_ori = [-1] * 12, [0] * 12
    edge_edge, edge_edge = [-1] * 12, [0] * 12
    edges = ()
    for edge_pos_on_cube, edge in EDGE_FACE_MAPPINGS.items():
        edge_colors = []
        for face_mapping, index in edge.items():
            edge_colors.append(cf.faces[face_mapping][index])
        edge_piece_index = -1
        for edge_num, colors in EDGE_COLORS.items():
            if set(edge_colors) == set(colors):
                edge_piece_index = edge_num
        ori = find_rotation_offset(tuple(edge_colors), EDGE_COLORS[edge_piece_index])
        edge_pos[edge_pos_on_cube] = edge_piece_index
        edge_ori[edge_pos_on_cube] = ori
        edges = (tuple(edge_pos), tuple(edge_ori))

    return CubePieces(corners, edges)