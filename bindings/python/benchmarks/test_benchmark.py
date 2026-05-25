import pytest
import dichotomia as dich
import glm
import numpy as np
import math

def test_bench_mat4_multiplication_dich(benchmark):
    m1 = dich.Mat4f.Translation(dich.Vec3f(1.0, 2.0, 3.0)) * dich.Mat4f.RotationY(math.radians(45.0))
    m2 = dich.Mat4f.Perspective(math.radians(90.0), 1.33, 0.1, 100.0)
    
    def do_work():
        return m1 * m2
        
    benchmark(do_work)

def test_bench_mat4_multiplication_glm(benchmark):
    m1 = glm.translate(glm.mat4(1.0), glm.vec3(1.0, 2.0, 3.0)) * glm.rotate(glm.mat4(1.0), math.radians(45.0), glm.vec3(0.0, 1.0, 0.0))
    m2 = glm.perspective(math.radians(90.0), 1.33, 0.1, 100.0)
    
    def do_work():
        return m1 * m2
        
    benchmark(do_work)

def test_bench_mat4_multiplication_numpy(benchmark):
    m1 = np.random.rand(4, 4).astype(np.float32)
    m2 = np.random.rand(4, 4).astype(np.float32)
    
    def do_work():
        return m1 @ m2
        
    benchmark(do_work)

def test_bench_quat_multiplication_dich(benchmark):
    q1 = dich.Quatf.FromEuler(math.radians(10.0), math.radians(20.0), math.radians(30.0))
    q2 = dich.Quatf.FromEuler(math.radians(-10.0), math.radians(45.0), math.radians(90.0))
    
    def do_work():
        return q1 * q2
        
    benchmark(do_work)

def test_bench_quat_multiplication_glm(benchmark):
    q1 = glm.quat(glm.vec3(math.radians(10.0), math.radians(20.0), math.radians(30.0)))
    q2 = glm.quat(glm.vec3(math.radians(-10.0), math.radians(45.0), math.radians(90.0)))
    
    def do_work():
        return q1 * q2
        
    benchmark(do_work)

def test_bench_quat_slerp_dich(benchmark):
    q1 = dich.Quatf.FromEuler(math.radians(10.0), math.radians(20.0), math.radians(30.0))
    q2 = dich.Quatf.FromEuler(math.radians(-10.0), math.radians(45.0), math.radians(90.0))
    
    def do_work():
        return dich.Quatf.Slerp(q1, q2, 0.5)
        
    benchmark(do_work)

def test_bench_quat_slerp_glm(benchmark):
    q1 = glm.quat(glm.vec3(math.radians(10.0), math.radians(20.0), math.radians(30.0)))
    q2 = glm.quat(glm.vec3(math.radians(-10.0), math.radians(45.0), math.radians(90.0)))
    
    def do_work():
        return glm.slerp(q1, q2, 0.5)
        
    benchmark(do_work)

def test_bench_vec3_cross_dich(benchmark):
    v1 = dich.Vec3f(1.0, 2.0, 3.0)
    v2 = dich.Vec3f(4.0, 5.0, 6.0)
    
    def do_work():
        return v1.Cross(v2)
        
    benchmark(do_work)

def test_bench_vec3_cross_glm(benchmark):
    v1 = glm.vec3(1.0, 2.0, 3.0)
    v2 = glm.vec3(4.0, 5.0, 6.0)
    
    def do_work():
        return glm.cross(v1, v2)
        
    benchmark(do_work)

def test_bench_vec3_cross_numpy(benchmark):
    v1 = np.array([1.0, 2.0, 3.0], dtype=np.float32)
    v2 = np.array([4.0, 5.0, 6.0], dtype=np.float32)
    
    def do_work():
        return np.cross(v1, v2)
        
    benchmark(do_work)

def test_bench_vec3_normalize_dich(benchmark):
    v = dich.Vec3f(1.0, 2.0, 3.0)
    
    def do_work():
        return v.Normalized()
        
    benchmark(do_work)

def test_bench_vec3_normalize_glm(benchmark):
    v = glm.vec3(1.0, 2.0, 3.0)
    
    def do_work():
        return glm.normalize(v)
        
    benchmark(do_work)

def test_bench_vec3_normalize_numpy(benchmark):
    v = np.array([1.0, 2.0, 3.0], dtype=np.float32)
    
    def do_work():
        return v / np.linalg.norm(v)
        
    benchmark(do_work)
