import pytest
import dichotomia as dich
import math

def test_mat4_identity():
    m = dich.Mat4f()
    assert m.Determinant() == pytest.approx(1.0)

def test_mat4_translation():
    trans = dich.Vec3f(1.0, 2.0, 3.0)
    m = dich.Mat4f.Translation(trans)
    
    v = dich.Vec4f(0.0, 0.0, 0.0, 1.0)
    res = m * v
    
    assert res.x == pytest.approx(1.0)
    assert res.y == pytest.approx(2.0)
    assert res.z == pytest.approx(3.0)
    assert res.w == pytest.approx(1.0)

def test_mat4_multiplication():
    m1 = dich.Mat4f.Translation(dich.Vec3f(1.0, 2.0, 3.0))
    m2 = dich.Mat4f.Scale(2.0)
    
    res = m1 * m2
    assert res.Determinant() == pytest.approx(8.0)
    
def test_mat4_inverse():
    m = dich.Mat4f.Translation(dich.Vec3f(1.0, 2.0, 3.0))
    inv = m.Inverse()
    
    res = m * inv
    assert res.Determinant() == pytest.approx(1.0)
