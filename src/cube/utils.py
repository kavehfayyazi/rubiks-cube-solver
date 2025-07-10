# Rotates the elements at indices in big_list forward by n.
# Returns a new list.

def rotate_sublist(big_list, indices, n):
    result = big_list.copy()
    sub_list = [big_list[i] for i in indices]
    n = n % len(indices)
    rotated = sub_list[-n:] + sub_list[:-n]
    for idx, val in zip(indices, rotated):
        result[idx] = val
    return result

def switch_pieces(move_table, piece_list, move):
        if move in move_table:
            n = 2 if move.endswith('2') else 3 if move.endswith('\'') else 1
            piece_list = rotate_sublist(piece_list, move_table.get(move), n)

def orient_corners(move_table, corner_list, move):
    if move in move_table:
        for idx, corner_idx in enumerate(move_table.get(move)):
            pos, orientation = corner_list[corner_idx]
            corner_list[corner_idx] = (pos, (orientation + 1) % 3) if idx % 2 == 0 else (pos, (orientation + 2) % 3)

def orient_edges(move_table, edge_list, move):
    if move in move_table:
        for edge_idx in move_table.get(move):
            pos, orientation = edge_list[edge_idx]
            edge_list[edge_idx] = (pos, 0 if orientation == 1 else 1)