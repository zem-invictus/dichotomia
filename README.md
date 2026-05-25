# Dichotomia v1.0

A minimalistic, modern C++23 math library for basic 3D graphics applications. It currently provides core linear algebra components with an emphasis on `constexpr` and modern C++ features.

![CI](https://github.com/Waldemarsch/dichotomia/actions/workflows/ci.yml/badge.svg)

## Features
- **Vectors (`Vec2`, `Vec3`, `Vec4`)**: Fully templated, `constexpr` arithmetic, strict ISO C++ `operator[]` using `std::unreachable()`.
- **Matrices (`Mat4`)**: 4x4 matrix operations, fast `Inverse` and `Determinant`, `Perspective`, `Orthographic`, `LookAt` (RH Zero-to-One standard).
- **Quaternions (`Quat`)**: Fast Euler-to-Quaternion conversion, Spherical Linear Interpolation (`Slerp`), rotation matrices.
- **Angles (`Radians`, `Degrees`)**: Type-safe angle structs with user-defined literals (`180.0_deg`, `3.14_rad`).
- **Standardized**: Zero-warning compilation, 100% Google C++ Style Guide compliant, complete Google Test coverage.

## Performance

Dichotomia leverages C++23 `[[assume]]` contracts and explicit object parameters (`Deducing This`) to achieve zero-overhead abstractions. Thanks to aggressive compiler auto-vectorization (tested on GCC 14 `-O3`), the pure scalar implementation frequently matches or exceeds manually tuned SIMD libraries like GLM in heavy operations:

| Benchmark | Dichotomia (Scalar C++23) | GLM |
| :--- | :--- | :--- |
| `Quat * Vec3` | **2.38 ns** | 3.80 ns |
| `Quat::Slerp` | **11.2 ns** | 13.1 ns |
| `Mat4::Inverse` | **13.5 ns** | 14.7 ns |
| `Vec3::Dot` | **0.577 ns** | 0.582 ns |
| `Vec3::Cross` | 1.22 ns | **1.16 ns** |
| `Mat4 * Mat4` | 3.49 ns | **3.26 ns** |
| `Mat4::Determinant`| 3.74 ns | **3.60 ns** |
| `Quat * Quat` | 1.94 ns | **1.73 ns** |
| `Vec3::Normalize`| 1.89 ns | **1.38 ns** |

*(GLM typically wins in `Normalize` due to explicit hardware `rsqrt` intrinsics).*

## Python Bindings (Fast 3D Math for Python)

**Stop using Numpy for single 3D vectors!**
Dichotomia is designed as a high-performance **surgical scalpel for gameplay scripting**. 
If you are doing data-oriented processing on millions of vectors at once, use `numpy`. But if you are writing OOP-style gameplay logic in your engine where you manipulate one entity at a time, `numpy`'s runtime type checking, array allocation, and GIL overhead will kill your framerate.

Dichotomia provides C++23 native scalar math bound to Python via `nanobind`. It operates directly on the stack with zero heap allocation overhead, making it up to **120x faster** than `numpy` for basic operations:

| Benchmark (nanoseconds) | Numpy | PyGLM | dichotomia (Python) |
| :--- | :--- | :--- | :--- |
| `Vec3 Cross` | 11,710 ns | 134 ns | **96 ns** (120x faster than Numpy) |
| `Vec3 Normalize` | 1,279 ns | 111 ns | **91 ns** (14x faster than Numpy) |
| `Quat Slerp` | N/A | 151 ns | **133 ns** (10% faster than PyGLM) |

*(Note: PyGLM currently outperforms Dichotomia in `Mat4` multiplication, which we plan to address in upcoming SIMD updates).*

## Usage

Dichotomia is a header-only library (using `INTERFACE` CMake targets). Add it to your project via `FetchContent`:

```cmake
include(FetchContent)

FetchContent_Declare(
    dichotomia
    GIT_REPOSITORY https://github.com/Waldemarsch/dichotomia.git
    GIT_TAG main
)
FetchContent_MakeAvailable(dichotomia)

# Link your target
target_link_libraries(your_engine PRIVATE dichotomia::dichotomia)
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

### Installation & Usage (Python)
You can install the Python bindings directly via `pip`:
```bash
# Clone the repository
git clone https://github.com/Waldemarsch/dichotomia.git
cd dichotomia

# Install into your environment
pip install .
```

```python
import dichotomia as dich
import math

v1 = dich.Vec3f(1.0, 0.0, 0.0)
q = dich.Quatf.FromAxisAngle(dich.Vec3f(0.0, 1.0, 0.0), math.pi / 2.0)
v2 = q * v1 # Rotates v1 by 90 degrees around Y axis
```

### Troubleshooting
**Python.h not found / Build fails:**
You need the Python development headers installed on your system.
```bash
sudo apt install python3-dev
# or specifically for 3.12:
sudo apt install python3.12-dev
```

**"externally-managed-environment" error when running `pip install`:**
Modern Linux distributions block global pip installations to prevent breaking system tools. Always use a virtual environment:
```bash
# Create a virtual environment
python -m venv .venv

# Activate it
source .venv/bin/activate

# Now you can install packages safely
pip install pytest pytest-benchmark PyGLM numpy
```