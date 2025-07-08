class CubePieces:
    def __init__(self, corners = None, edges = None):
        if corners is not None and edges is not None:
            self.corners = corners
            self.edges = edges
        else:
            CubePieces.defaultCube(self)
    
    def defaultCube(self):
        self.corners = (
            [i for i in range(8)],
            ['UFL', 'UFR', 'UBL', 'UBR', 'DFL', 'DFR', 'DBL', 'DBR'],
            [0] * 8 # TO DO
        )
        self.edges = (
            [i for i in range(8)],
            ['UF', 'UL', 'UR', 'UB', 'DF', 'DL', 'DR', 'DB'],
            [0] * 8 # TO DO
        )

    def print(self):
        print(self.corners)
        print(self.edges)