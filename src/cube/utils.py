"""
cube.utils

Utility functions to help with permutations and orientations that
utilize CORNER_ORIENTATION_CYCLES and EDGE_ORIENTATION_CYCLES from tables.py

Public API:
- rotate_sublist(list, list, int) -> list
- switch_pieces(list, list, str) -> None
- orient_corners(list, str) -> None
- orient_edges(list, str) -> None
"""

from .tables import (
    CORNER_ORIENTATION_CYCLES,
    EDGE_ORIENTATION_CYCLES,
    EDGE_PERMUTATIONS,
)

def rotate_sublist(big_list: list, indices: list, n: int) -> list:
    """Rotates the indices sublist of big_list by n in a forward direction and returns a copy

    Args: 
        big_list (list): The original list.
        indices (list): Positions to rotate within 'big_list'.
        n (int): Number of forward rotations.
    Returns:
        list: A copy of big_list with the specified rotations applied.
    """
    result = big_list.copy()
    sub_list = [big_list[i] for i in indices]
    n = n % len(indices)
    rotated = sub_list[-n:] + sub_list[:-n]
    for idx, val in zip(indices, rotated):
        result[idx] = val
    return result

def switch_pieces(move_table: dict[str, tuple[int, ...]], piece_list: list, move: str):
    """Utilizes rotate_sublist to rotate the piece_list indices according to the move performed

    Args:
        move_table (dict[str, tuple[int, ...]]): Maps face-turns to index tuples.
        piece_list (list): The list with pieces to permute.
        move (str): A face-turn string.
    """
    if move in move_table:
        n = 2 if move.endswith('2') else 3 if move.endswith('\'') else 1
        piece_list[:] = rotate_sublist(piece_list, move_table[move], n)

def orient_corners(corner_list: list, move: str):
    """Updates orientation of corners in corner_list inplace according to move

    Args:
        corner_list (list): The list of '(corner_id, orientation)' corner tuples
        move (str): A face-turn string.
    """
    if move in CORNER_ORIENTATION_CYCLES:
        for idx, corner_idx in enumerate(CORNER_ORIENTATION_CYCLES[move]):
            pos, orientation = corner_list[corner_idx]
            corner_list[corner_idx] = (pos, (orientation + 1) % 3) if idx % 2 == 0 else (pos, (orientation + 2) % 3)

def orient_edges(edge_list: list, move: str):
    """Updates orientation of edges in edge_list inplace according to move

    Args:
        edge_list (list): The list of '(edge_id, orientation)' edge tuples
        move (str): A face-turn string.
    """
    if move in EDGE_ORIENTATION_CYCLES:
        for edge_idx, (pos, orientation) in enumerate(edge_list):
            if edge_idx in EDGE_PERMUTATIONS[move] and edge_idx in EDGE_ORIENTATION_CYCLES[move]:
                edge_list[edge_idx] = (pos, 0 if orientation == 1 else 1)