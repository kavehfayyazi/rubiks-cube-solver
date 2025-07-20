import pickle
from collections import deque
from cube.pieces import CubePieces, pieces_to_cube
from .utils import CORNER_TOTAL, encode_state, decode_state

def build_corner_pdb(max_depth: int = -1):
    """
    Build a corner-state pattern DB, storing two 4-bit depth bits per byte
    
    """
    size = (CORNER_TOTAL + 1) // 2
    corner_pdb = bytearray([0xFF]) * size # All nibbles = 0xF

    # BFS queue of (state_id, depth)
    solved = CubePieces()
    corner_state, _ = solved.return_pieces()
    start_id = encode_state(corner_state, 'corners')
    queue = deque([(start_id, 0)])

    MOVES = [
        "U","U'","U2","D","D'","D2",
        "L","L'","L2","R","R'","R2",
        "F","F'","F2","B","B'","B2"
    ]

    while queue:
        state_id, depth = queue.popleft()
        idx = state_id // 2
        even = (state_id % 2 == 0)
        b = corner_pdb[idx]

        # extract the nibble
        nibble = (b >> 4) & 0x0F if even else (b & 0x0F)
        if nibble != 0x0F:
            continue

        d = depth & 0x0F
        if d == 0x0F: d = 0x0E

        if even:
            corner_pdb[idx] = (b & 0x0F) | (d << 4)
        else:
            corner_pdb[idx] = (b & 0xF0) | d

        if max_depth >= 0 and depth >= max_depth:
            continue

        corners = decode_state(state_id, 'corners')
        cube = pieces_to_cube((corners, (tuple(range(12)), (0,) * 12)))

        for m in MOVES:
            next_cube = cube.move(m)
            next_corners, __ = next_cube.return_pieces()
            next_id = encode_state(next_corners, 'corners')
            # print(next_corners, next_id, depth + 1, sep=' ')
            queue.append((next_id, depth + 1))
    return corner_pdb

def main():
    pdb = build_corner_pdb(max_depth=12)
    with open('src/pattern_db/corner_pdb.pkl', 'wb') as file:
        pickle.dump(pdb, file) 

    # with open('src/pattern_db/corner_pdb.pkl', 'rb') as file:
    #     data = pickle.load(file)

    #     for i in range(20):
    #         print(data[i])

if __name__ == '__main__':
    main()