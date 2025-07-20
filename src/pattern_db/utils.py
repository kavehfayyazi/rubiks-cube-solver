from math import factorial

# Total corner states = 8! * 3^7
NUM_CORNER_PERMUTATIONS = factorial(8)
NUM_CORNER_ORIENTATIONS = 3 ** 7
CORNER_TOTAL = NUM_CORNER_PERMUTATIONS * NUM_CORNER_ORIENTATIONS

# Utilizes Lehmer code
def perm_to_rank(perm: list):
    n = len(perm)
    rank = 0
    for i in range(n):
        smaller = sum(1 for x in perm[i+1:] if x < perm[i])
        rank += smaller * factorial(n - 1 - i)
    return rank

def rank_to_lehmer(rank, n):
    leh = [0]*n
    for i in range(n):
        f = factorial(n - 1 - i)
        leh[i] = rank // f
        rank %= f
    return leh

def lehmer_to_perm(leh: list):
    elems = list(range(len(leh)))
    perm = []
    for v in leh:
        perm.append(elems.pop(v))
    return tuple(perm)

# Uses Base-3 to encode a list to a single integer.
# assumes len(list) = 7
def corner_ori_encode(oris: list):
    val = 0
    for ori in oris[:7]:
        val = val * 3 + ori
    return val

# Decodes using base-3
# assumes len(list) = 7
def corner_ori_decode(val: int):
    ori = [0]*7
    for i in range(6, -1, -1):
        ori[i] = val % 3
        val //= 3
    ori.append((-sum(ori)) % 3)
    return tuple(ori)

# TODO: here
 
# Uses Base-2 to encode a list to a single integer.
# assumes len(list) = 7
def edge_ori_encode(oris: list):
    val = 0
    for ori in oris:
        val = (val << 1) | ori
    return val

# Decodes using base-2
def edge_ori_decode(val: int):
    ori = [-1] * 7
    for i in range(6, -1, -1):
        ori[i] = val & 1
        val >>= 1
    # calculates out the 8th orientation
    last = sum(ori) % 2
    ori.append(last)
    return ori

def encode_state(pieces: list, type=''):
    match type:
        case 'corners':
            perm, oris = pieces
            rank = perm_to_rank(perm)
            oc = corner_ori_encode(oris)
            return rank * NUM_CORNER_ORIENTATIONS + oc
        # case 'edges':
        #     return perm_to_lehmer(pieces[0]) * NUM_EDGE_ORIENTATIONS + corner_ori_encode(pieces[1])

def decode_state(state, type=''):
    match type:
        case 'corners':
            oc = state % NUM_CORNER_ORIENTATIONS
            rank = state // NUM_CORNER_ORIENTATIONS
            leh = rank_to_lehmer(rank, 8)
            perm = lehmer_to_perm(leh)
            oris = corner_ori_decode(oc)
            return (perm, oris)
        # case 'edges':