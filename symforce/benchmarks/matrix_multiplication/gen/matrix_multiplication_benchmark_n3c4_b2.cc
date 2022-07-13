// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     matrix_multiplication_benchmark.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

///
/// Experiment to show timing for the matrix multiplication example in the SymForce paper.
///
/// Run with:
///
///     build/bin/benchmarks/matrix_multiplication_benchmark_n3c4_b2
///
/// See run_matmul_benchmarks.py for more information
///

#include <chrono>
#include <thread>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <spdlog/spdlog.h>

#include <symforce/opt/tic_toc.h>
#include <symforce/opt/util.h>

using namespace sym;

#include "./compute_a_dense_dynamic_n3c4_b2.h"
#include "./compute_a_dense_n3c4_b2.h"
#include "./compute_a_n3c4_b2.h"
#include "./compute_at_b_n3c4_b2.h"
#include "./compute_b_dense_dynamic_n3c4_b2.h"
#include "./compute_b_dense_n3c4_b2.h"
#include "./compute_b_n3c4_b2.h"

template <typename Scalar>
__attribute__((noinline)) Eigen::Matrix<Scalar, 15, 15> ComputeDenseFixedN3C4B2(
    const Scalar x0, const Scalar x1, const Scalar x2, const Scalar x3, const Scalar x4) {
  Eigen::Matrix<Scalar, 20, 15> A = ComputeADenseN3C4B2<Scalar>(x0, x1, x2, x3, x4);
  Eigen::Matrix<Scalar, 20, 15> B = ComputeBDenseN3C4B2<Scalar>(x0, x1, x2, x3, x4);
  return A.transpose() * B;
}

template <typename Scalar>
__attribute__((noinline)) Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
ComputeDenseDynamicN3C4B2(const Scalar x0, const Scalar x1, const Scalar x2, const Scalar x3,
                          const Scalar x4) {
  const auto A = ComputeADenseDynamicN3C4B2<Scalar>(x0, x1, x2, x3, x4);
  const auto B = ComputeBDenseDynamicN3C4B2<Scalar>(x0, x1, x2, x3, x4);
  return A.transpose() * B;
}

template <typename Scalar>
__attribute__((noinline)) Eigen::SparseMatrix<Scalar> ComputeSparseN3C4B2(
    const Scalar x0, const Scalar x1, const Scalar x2, const Scalar x3, const Scalar x4) {
  Eigen::SparseMatrix<Scalar> A = ComputeAN3C4B2<Scalar>(x0, x1, x2, x3, x4);
  Eigen::SparseMatrix<Scalar> B = ComputeBN3C4B2<Scalar>(x0, x1, x2, x3, x4);
  return A.transpose() * B;
}

// ----------------------------------------------------------------------------
// Test Cases
// ----------------------------------------------------------------------------

TEMPLATE_TEST_CASE("sparse_n3c4_b2", "", double, float) {
  using Scalar = TestType;

  fmt::print("n_runs_multiplier: {};\n", 100.0);

  const Scalar x2 = 1.0;
  const Scalar x3 = 2.0;
  const Scalar x4 = 3.0;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("sparse_n3c4_b2_{}", typeid(Scalar).name());

    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeSparseN3C4B2(x0, x1, x2, x3, x4);
        sum += mat.valuePtr()[0];
      }
    }
  }
}

TEMPLATE_TEST_CASE("dense_dynamic_n3c4_b2", "", double, float) {
  using Scalar = TestType;

  fmt::print("n_runs_multiplier: {};\n", 100.0);

  const Scalar x2 = 1.0;
  const Scalar x3 = 2.0;
  const Scalar x4 = 3.0;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("dense_dynamic_n3c4_b2_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeDenseDynamicN3C4B2<Scalar>(x0, x1, x2, x3, x4);
        sum += mat(0, 0);
      }
    }
  }
}

TEMPLATE_TEST_CASE("dense_fixed_n3c4_b2", "", double, float) {
  using Scalar = TestType;

  fmt::print("n_runs_multiplier: {};\n", 100.0);

  const Scalar x2 = 1.0;
  const Scalar x3 = 2.0;
  const Scalar x4 = 3.0;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("dense_fixed_n3c4_b2_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeDenseFixedN3C4B2<Scalar>(x0, x1, x2, x3, x4);
        sum += mat(0, 0);
      }
    }
  }
}

TEMPLATE_TEST_CASE("flattened_n3c4_b2", "", double, float) {
  using Scalar = TestType;

  fmt::print("n_runs_multiplier: {};\n", 100.0);

  const Scalar x2 = 1.0;
  const Scalar x3 = 2.0;
  const Scalar x4 = 3.0;

  std::chrono::milliseconds timespan(100);
  std::this_thread::sleep_for(timespan);

  Scalar sum = 0.0;
  {
    SYM_TIME_SCOPE("flattened_n3c4_b2_{}", typeid(Scalar).name());
    for (Scalar x0 = 0.1; x0 < 100.0; x0 += 0.1) {
      for (Scalar x1 = 0.1; x1 < 100.0; x1 += 0.1) {
        auto mat = ComputeAtBN3C4B2(x0, x1, x2, x3, x4);
        sum += mat(0, 0);
      }
    }
  }
}
