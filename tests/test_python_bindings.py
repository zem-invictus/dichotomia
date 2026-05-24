import dichotomia
import sys

def main():
    print("Testing dichotomia python bindings...")
    
    # Test Vec3
    v1 = dichotomia.Vec3f(1.0, 2.0, 3.0)
    v2 = dichotomia.Vec3f(4.0, 5.0, 6.0)
    v3 = v1 + v2
    
    assert abs(v3.x - 5.0) < 1e-5
    assert abs(v3.y - 7.0) < 1e-5
    assert abs(v3.z - 9.0) < 1e-5
    print("Vec3 addition OK:", v3)

    dot = v1.Dot(v2)
    assert abs(dot - (1*4 + 2*5 + 3*6)) < 1e-5
    print("Vec3 Dot OK:", dot)

    # Test Mat4
    m1 = dichotomia.Mat4f.Identity()
    m2 = dichotomia.Mat4f.Translation(dichotomia.Vec3f(10, 20, 30))
    m3 = m2 * m1

    # Apply translation
    v4 = dichotomia.Vec4f(0, 0, 0, 1)
    res = m3 * v4
    assert abs(res.x - 10.0) < 1e-5
    assert abs(res.y - 20.0) < 1e-5
    assert abs(res.z - 30.0) < 1e-5
    print("Mat4 translation OK:", res)

    # Test Quat
    q = dichotomia.Quatf.FromAxisAngle(dichotomia.Vec3f(0, 1, 0), 3.14159265359 / 2.0)
    print("Quat from Axis-Angle OK:", q)

    m_rot = q.ToMat4()
    print("Quat to Mat4 OK.")

    print("All python bindings tests passed successfully!")

if __name__ == "__main__":
    main()
