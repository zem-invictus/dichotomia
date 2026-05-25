import pytest
import dichotomia as dich
import math

def test_quat_identity():
    q = dich.Quatf(0.0, 0.0, 0.0, 1.0)
    assert q.Length() == pytest.approx(1.0)

def test_quat_from_axis_angle():
    axis = dich.Vec3f(0.0, 1.0, 0.0)
    angle = math.pi / 2.0 # 90 degrees
    q = dich.Quatf.FromAxisAngle(axis, angle)
    
    v = dich.Vec3f(1.0, 0.0, 0.0)
    res = q * v
    
    assert res.x == pytest.approx(0.0, abs=1e-5)
    assert res.y == pytest.approx(0.0, abs=1e-5)
    assert res.z == pytest.approx(-1.0, abs=1e-5)

def test_quat_multiplication():
    q1 = dich.Quatf.FromEuler(math.pi/2.0, 0.0, 0.0)
    q2 = dich.Quatf.FromEuler(0.0, math.pi/2.0, 0.0)
    
    q3 = q1 * q2
    assert q3.Length() == pytest.approx(1.0)

def test_quat_slerp():
    q1 = dich.Quatf.FromAxisAngle(dich.Vec3f(1.0, 0.0, 0.0), 0.0)
    q2 = dich.Quatf.FromAxisAngle(dich.Vec3f(1.0, 0.0, 0.0), math.pi)
    
    q_mid = dich.Quatf.Slerp(q1, q2, 0.5)
    v = dich.Vec3f(0.0, 1.0, 0.0)
    res = q_mid * v
    assert res.x == pytest.approx(0.0, abs=1e-5)
    assert res.y == pytest.approx(0.0, abs=1e-5)
    assert res.z == pytest.approx(-1.0, abs=1e-5)
