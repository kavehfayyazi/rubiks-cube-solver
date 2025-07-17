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
        cp (CubePieces): (position + orientation tuple lists).
    Returns:
        CubeFaces: lists of length-9 sticker colors in row-major order.
    """

    faces = {face: ['' for _ in range(3)] * 3 for face in FACE_COLORS}

    # Center stickers
    for face in FACE_COLORS:
        faces[face][4] = FACE_COLORS[face]

    # Corner stickers
    for corner_num, (pos, orientation) in enumerate(cp.corners):
        mapping = CORNER_FACE_MAPPINGS[corner_num]
        colors = list(CORNER_COLORS[pos])
        # Rotate the color tuple 'orientation' times
        oriented = colors[-orientation:] + colors[:-orientation]
        for (face, loc), sticker in zip(mapping.items(), oriented):
            faces[face][loc] = sticker

    # Edge stickers
    for edge_num, (pos, orientation) in enumerate(cp.edges):
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
        cf (CubeFaces): lists of length-9 sticker colors in row-major order.
    Returns:
        CubePieces: Position + Orientation tuple lists.
    """

    corners = [(-1,0)] * 8
    edges = [(-1,0)] * 12

    # Corner stickers
    for corner_pos_on_cube, corner in CORNER_FACE_MAPPINGS.items():
        corner_colors = []
        for face_mapping, index in corner.items():
            corner_colors.append(cf.faces[face_mapping][index])
        corner_piece_index = -1
        for corner_num, colors in CORNER_COLORS.items():
            if set(corner_colors) == set(colors):
                corner_piece_index = corner_num
        orientation = find_rotation_offset(tuple(corner_colors), CORNER_COLORS[corner_piece_index])
        corners[corner_pos_on_cube] = (corner_piece_index, orientation)

    # Edge stickers
    for edge_pos_on_cube, edge in EDGE_FACE_MAPPINGS.items():
        edge_colors = []
        for face_mapping, index in edge.items():
            edge_colors.append(cf.faces[face_mapping][index])
        edge_piece_index = -1
        for edge_num, colors in EDGE_COLORS.items():
            if set(edge_colors) == set(colors):
                edge_piece_index = edge_num
        orientation = find_rotation_offset(tuple(edge_colors), EDGE_COLORS[edge_piece_index])
        edges[edge_pos_on_cube] = (edge_piece_index, orientation)

    return CubePieces(corners, edges)