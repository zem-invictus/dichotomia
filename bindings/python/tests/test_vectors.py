import pytest
import dichotomia as dich
import math

def test_vec2_operations():
    v1 = dich.Vec2f(1.0, 2.0)
    v2 = dich.Vec2f(3.0, 4.0)
    
    v3 = v1 + v2
    assert v3.x == pytest.approx(4.0)
    assert v3.y == pytest.approx(6.0)
    
    v4 = v1 * 2.0
    assert v4.x == pytest.approx(2.0)
    assert v4.y == pytest.approx(4.0)
    
    dot = v1.Dot(v2)
    assert dot == pytest.approx(11.0)

def test_vec3_operations():
    v1 = dich.Vec3f(1.0, 0.0, 0.0)
    v2 = dich.Vec3f(0.0, 1.0, 0.0)
    
    v3 = v1.Cross(v2)
    assert v3.x == pytest.approx(0.0)
    assert v3.y == pytest.approx(0.0)
    assert v3.z == pytest.approx(1.0)
    
    assert v1.Length() == pytest.approx(1.0)
    
    v_un = dich.Vec3f(2.0, 0.0, 0.0)
    v_norm = v_un.Normalized()
    assert v_norm.x == pytest.approx(1.0)

def test_vec4_operations():
    v1 = dich.Vec4f(1.0, 2.0, 3.0, 4.0)
    v2 = dich.Vec4f(1.0, 1.0, 1.0, 1.0)
    
    v3 = v1 - v2
    assert v3.x == pytest.approx(0.0)
    assert v3.y == pytest.approx(1.0)
    assert v3.z == pytest.approx(2.0)
    assert v3.w == pytest.approx(3.0)
