import pytest
from src.cube.pieces import CubePieces
from src.cube.faces import CubeFaces
from src.cube.translator import faces_to_pieces, pieces_to_faces

def test_pieces():
    pieces = CubePieces()
    faces = CubeFaces()
    assert faces_to_pieces(faces).return_pieces() == pieces.return_pieces()
    assert pieces_to_faces(pieces).return_faces() == faces.return_faces()
    assert pieces.is_solved
    assert pieces.move('').is_solved

    pieces_inverse = CubePieces()
    assert pieces_inverse.move("U U'").is_solved
    assert pieces_inverse.move("U' U").is_solved
    assert pieces_inverse.move("B B'").is_solved
    assert pieces_inverse.move("B' B").is_solved
    assert pieces_inverse.move("L L'").is_solved
    assert pieces_inverse.move("L' L").is_solved
    assert pieces_inverse.move("R R'").is_solved
    assert pieces_inverse.move("R' R").is_solved
    assert pieces_inverse.move("F F'").is_solved
    assert pieces_inverse.move("F' F").is_solved
    assert pieces_inverse.move("B B'").is_solved
    assert pieces_inverse.move("B' B").is_solved

    pieces_doubles = CubePieces()

    assert pieces_doubles.move("U2 U2").is_solved
    assert pieces_doubles.move("D2 D2").is_solved
    assert pieces_doubles.move("L2 L2").is_solved
    assert pieces_doubles.move("R2 R2").is_solved
    assert pieces_doubles.move("F2 F2").is_solved
    assert pieces_doubles.move("B2 B2").is_solved

    pieces_around = CubePieces()

    assert pieces_around.move("U U' U2").is_solved
    assert pieces_around.move("D D' D2").is_solved
    assert pieces_around.move("L L' L2").is_solved
    assert pieces_around.move("R R' R2").is_solved
    assert pieces_around.move("F F' F2").is_solved
    assert pieces_around.move("B B' B2").is_solved