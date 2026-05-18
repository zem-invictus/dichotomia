#include <benchmark/benchmark.h>
#include "../include/dichotomia.hpp"

using namespace dich::math;
using namespace dich::math::literals;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

static void BM_Mat4_Multiplication(benchmark::State& state) {
    Mat4f m1 = Mat4f::Translation({1.0f, 2.0f, 3.0f}) * Mat4f::RotationY(ToRadians(45.0_deg));
    Mat4f m2 = Mat4f::Perspective(ToRadians(90.0_deg), 1.33f, 0.1f, 100.0f);
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(m1);
        benchmark::DoNotOptimize(m2);
        Mat4f res = m1 * m2;
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Mat4_Multiplication);

static void BM_Mat4_Inverse(benchmark::State& state) {
    Mat4f m = Mat4f::Translation({1.0f, 2.0f, 3.0f}) * Mat4f::RotationY(ToRadians(45.0_deg));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(m);
        Mat4f res = m.Inverse();
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Mat4_Inverse);

static void BM_Quat_Mul_Vec3(benchmark::State& state) {
    Quatf q = Quatf::FromEuler(ToRadians(10.0_deg), ToRadians(20.0_deg), ToRadians(30.0_deg));
    Vec3f v{1.0f, 0.0f, 0.0f};
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(q);
        benchmark::DoNotOptimize(v);
        Vec3f res = q * v;
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Quat_Mul_Vec3);

static void BM_Quat_Multiplication(benchmark::State& state) {
    Quatf q1 = Quatf::FromEuler(ToRadians(10.0_deg), ToRadians(20.0_deg), ToRadians(30.0_deg));
    Quatf q2 = Quatf::FromEuler(ToRadians(Degreesf(-10.0f)), ToRadians(45.0_deg), ToRadians(90.0_deg));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(q1);
        benchmark::DoNotOptimize(q2);
        Quatf res = q1 * q2;
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Quat_Multiplication);

static void BM_Quat_Slerp(benchmark::State& state) {
    Quatf q1 = Quatf::FromEuler(ToRadians(10.0_deg), ToRadians(20.0_deg), ToRadians(30.0_deg));
    Quatf q2 = Quatf::FromEuler(ToRadians(Degreesf(-10.0f)), ToRadians(45.0_deg), ToRadians(90.0_deg));
    float t = 0.5f;
    for (auto _ : state) {
        benchmark::DoNotOptimize(q1);
        benchmark::DoNotOptimize(q2);
        benchmark::DoNotOptimize(t);
        Quatf res = Quatf::Slerp(q1, q2, t);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Quat_Slerp);

static void BM_Vec3_Normalize(benchmark::State& state) {
    Vec3f v{1.0f, 2.0f, 3.0f};
    for (auto _ : state) {
        benchmark::DoNotOptimize(v);
        Vec3f res = v.Normalized();
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Vec3_Normalize);

static void BM_Vec3_Cross(benchmark::State& state) {
    Vec3f v1{1.0f, 2.0f, 3.0f};
    Vec3f v2{4.0f, 5.0f, 6.0f};
    for (auto _ : state) {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        Vec3f res = v1.Cross(v2);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Vec3_Cross);

static void BM_Vec3_Dot(benchmark::State& state) {
    Vec3f v1{1.0f, 2.0f, 3.0f};
    Vec3f v2{4.0f, 5.0f, 6.0f};
    for (auto _ : state) {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        float res = v1.Dot(v2);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Vec3_Dot);

static void BM_Mat4_Determinant(benchmark::State& state) {
    Mat4f m = Mat4f::Translation({1.0f, 2.0f, 3.0f}) * Mat4f::RotationY(ToRadians(45.0_deg));
    for (auto _ : state) {
        benchmark::DoNotOptimize(m);
        float res = m.Determinant();
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Mat4_Determinant);

static void BM_GLM_Mat4_Multiplication(benchmark::State& state) {
    glm::mat4 m1 = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f)), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 m2 = glm::perspective(glm::radians(90.0f), 1.33f, 0.1f, 100.0f);
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(m1);
        benchmark::DoNotOptimize(m2);
        glm::mat4 res = m1 * m2;
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Mat4_Multiplication);

static void BM_GLM_Mat4_Inverse(benchmark::State& state) {
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f)), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(m);
        glm::mat4 res = glm::inverse(m);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Mat4_Inverse);

static void BM_GLM_Quat_Mul_Vec3(benchmark::State& state) {
    glm::quat q = glm::quat(glm::vec3(glm::radians(10.0f), glm::radians(20.0f), glm::radians(30.0f)));
    glm::vec3 v{1.0f, 0.0f, 0.0f};
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(q);
        benchmark::DoNotOptimize(v);
        glm::vec3 res = q * v;
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Quat_Mul_Vec3);

static void BM_GLM_Quat_Multiplication(benchmark::State& state) {
    glm::quat q1 = glm::quat(glm::vec3(glm::radians(10.0f), glm::radians(20.0f), glm::radians(30.0f)));
    glm::quat q2 = glm::quat(glm::vec3(glm::radians(-10.0f), glm::radians(45.0f), glm::radians(90.0f)));
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(q1);
        benchmark::DoNotOptimize(q2);
        glm::quat res = q1 * q2;
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Quat_Multiplication);

static void BM_GLM_Quat_Slerp(benchmark::State& state) {
    glm::quat q1 = glm::quat(glm::vec3(glm::radians(10.0f), glm::radians(20.0f), glm::radians(30.0f)));
    glm::quat q2 = glm::quat(glm::vec3(glm::radians(-10.0f), glm::radians(45.0f), glm::radians(90.0f)));
    float t = 0.5f;
    for (auto _ : state) {
        benchmark::DoNotOptimize(q1);
        benchmark::DoNotOptimize(q2);
        benchmark::DoNotOptimize(t);
        glm::quat res = glm::slerp(q1, q2, t);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Quat_Slerp);

static void BM_GLM_Vec3_Normalize(benchmark::State& state) {
    glm::vec3 v{1.0f, 2.0f, 3.0f};
    for (auto _ : state) {
        benchmark::DoNotOptimize(v);
        glm::vec3 res = glm::normalize(v);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Vec3_Normalize);

static void BM_GLM_Vec3_Cross(benchmark::State& state) {
    glm::vec3 v1{1.0f, 2.0f, 3.0f};
    glm::vec3 v2{4.0f, 5.0f, 6.0f};
    for (auto _ : state) {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        glm::vec3 res = glm::cross(v1, v2);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Vec3_Cross);

static void BM_GLM_Vec3_Dot(benchmark::State& state) {
    glm::vec3 v1{1.0f, 2.0f, 3.0f};
    glm::vec3 v2{4.0f, 5.0f, 6.0f};
    for (auto _ : state) {
        benchmark::DoNotOptimize(v1);
        benchmark::DoNotOptimize(v2);
        float res = glm::dot(v1, v2);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Vec3_Dot);

static void BM_GLM_Mat4_Determinant(benchmark::State& state) {
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f)), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    for (auto _ : state) {
        benchmark::DoNotOptimize(m);
        float res = glm::determinant(m);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_GLM_Mat4_Determinant);
