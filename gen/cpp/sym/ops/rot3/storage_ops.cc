// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     ops/CLASS/storage_ops.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./storage_ops.h"

#include <algorithm>
#include <cassert>

#include <Eigen/Core>

#include <sym/rot3.h>

namespace sym {

template <typename ScalarType>
void StorageOps<Rot3<ScalarType>>::ToStorage(const Rot3<ScalarType>& a, ScalarType* out) {
  assert(out != nullptr);
  std::copy_n(a.Data().data(), a.StorageDim(), out);
}

template <typename ScalarType>
Rot3<ScalarType> StorageOps<Rot3<ScalarType>>::FromStorage(const ScalarType* data) {
  assert(data != nullptr);
  return Rot3<ScalarType>(Eigen::Map<const typename Rot3<ScalarType>::DataVec>(data),
                          /* normalize */ false);
}

}  // namespace sym

// Explicit instantiation
template struct sym::StorageOps<sym::Rot3<double>>;
template struct sym::StorageOps<sym::Rot3<float>>;
