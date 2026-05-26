import pytest
np = pytest.importorskip("numpy")
import dichotomia as dich
import math

def test_numpy_zero_copy_vector():
    v = dich.Vec3f(1.5, 2.5, 3.5)
    
    # Create numpy array without copying underlying memory
    arr = np.array(v, copy=False)
    
    assert arr.shape == (3,)
    assert arr.dtype == np.float32
    assert arr[0] == 1.5
    assert arr[1] == 2.5
    assert arr[2] == 3.5
    
    # Modify the numpy array
    arr[0] = 99.0
    
    # Assert that the C++ object was modified (zero-copy)
    assert v.x == 99.0

def test_numpy_zero_copy_matrix():
    mat = dich.Mat4f.RotationX(math.pi)
    
    arr = np.array(mat, copy=False)
    assert arr.shape == (4, 4)
    assert arr.dtype == np.float32
    
    # Modify numpy array
    arr[3, 3] = 42.0
    
    # We can't directly index mat from python easily right now without an __getitem__,
    # but we can check if determinant changed significantly due to this modification
    assert mat.Determinant() == pytest.approx(42.0, abs=1e-5) # diagonal elements 1, -1, -1, 42 -> 42 

def test_numpy_zero_copy_quaternion():
    q = dich.Quatf(1.0, 2.0, 3.0, 4.0)
    arr = np.array(q, copy=False)
    assert arr.shape == (4,)
    
    arr[0] = 10.0
    assert q.x == 10.0
