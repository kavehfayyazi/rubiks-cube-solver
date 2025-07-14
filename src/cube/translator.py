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

def pieces_to_faces(cp: CubePieces) -> CubeFaces:
    """Lays out all stickers from a piece-oriented cube into 3x3 (length-9) face arrays.

    Args:
        cp (CubePieces): (position + orientation tuple lists)
    Returns:
        CubeFaces: lists of length-9 sticker colors in row-major order
    """

    faces = {face: ['' for _ in range(3)] * 3 for face in FACE_COLORS}

    # center stickers
    for face in FACE_COLORS:
        faces[face][4] = FACE_COLORS[face]

    # corner stickers
    for corner_num, (pos, orientation) in enumerate(cp.corners):
        mapping = CORNER_FACE_MAPPINGS[corner_num]
        colors = list(CORNER_COLORS[pos])
        # Rotate the color tuple 'orientation' times
        oriented = colors[orientation:] + colors[:orientation]
        for (face, loc), sticker in zip(mapping.items(), oriented):
            faces[face][loc] = sticker

    # edge stickers
    for edge_num, (pos, orientation) in enumerate(cp.edges):
        mapping = EDGE_FACE_MAPPINGS[edge_num]
        colors = list(EDGE_COLORS[pos])
        # Rotate the color tuple if orientation == 1
        oriented = colors[orientation:] + colors[:orientation]
        for (face, loc), sticker in zip(mapping.items(), oriented):
            faces[face][loc] = sticker

    return CubeFaces(faces)