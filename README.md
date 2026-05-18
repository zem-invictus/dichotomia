# Dichotomia (zem_math) v1.0

A minimalistic, modern C++23 math library for basic 3D graphics applications. It currently provides core linear algebra components with an emphasis on `constexpr` and modern C++ features.

![CI](https://github.com/your-username/zem_math/actions/workflows/ci.yml/badge.svg)

## Features
- **Vectors (`Vec2`, `Vec3`, `Vec4`)**: Fully templated, `constexpr` arithmetic, strict ISO C++ `operator[]` using `std::unreachable()`.
- **Matrices (`Mat4`)**: 4x4 matrix operations, fast `Inverse` and `Determinant`, `Perspective`, `Orthographic`, `LookAt` (RH Zero-to-One standard).
- **Quaternions (`Quat`)**: Fast Euler-to-Quaternion conversion, Spherical Linear Interpolation (`Slerp`), rotation matrices.
- **Angles (`Radians`, `Degrees`)**: Type-safe angle structs with user-defined literals (`180.0_deg`, `3.14_rad`).
- **Standardized**: Zero-warning compilation, 100% Google C++ Style Guide compliant, complete Google Test coverage.

## Usage

Dichotomia is a header-only library (using `INTERFACE` CMake targets). Add it to your project via `FetchContent`:

```cmake
include(FetchContent)

FetchContent_Declare(
    zem_math
    GIT_REPOSITORY https://github.com/your-username/zem_math.git
    GIT_TAG main
)
FetchContent_MakeAvailable(zem_math)

# Link your target
target_link_libraries(your_engine PRIVATE zem::dichotomia)
```

### Example
```cpp
#include "dichotomia.hpp"

using namespace dich::math;
using namespace dich::math::literals;

int main() {
    Vec3f axis{0.0f, 1.0f, 0.0f};
    Quatf rotation = Quatf::FromAxisAngle(axis, 90.0_deg);
    
    Mat4f model = rotation.ToMat4() * Mat4f::Translation({0.0f, 5.0f, 0.0f});
    Mat4f view = Mat4f::LookAt({0.0f,0.0f,10.0f}, {0.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f});
    Mat4f proj = Mat4f::Perspective(90.0_deg, 16.0f/9.0f, 0.1f, 100.0f);
    
    Mat4f mvp = proj * view * model;
    return 0;
}
```

## Testing
Built with complete GTest coverage.
```bash
mkdir build && cd build
cmake ..
make
ctest --output-on-failure
```