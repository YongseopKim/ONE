/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NNFW_BENCHMARK_PHASE_H__
#define __NNFW_BENCHMARK_PHASE_H__

#include "Types.h"

#include <string>
#include <vector>

namespace benchmark
{

struct Phase
{
  Phase(const std::string &t, uint32_t c) : tag(t), count(c)
  {
    // DO NOTHING
  }

  const std::string tag;
  uint32_t count;
  std::vector<uint64_t> time;                                // us
  std::vector<uint32_t> memory[MemoryType::END_OF_MEM_TYPE]; // kB
};

struct PhaseOption
{
  PhaseOption() : memory(false), memory_gpu(false) {}
  PhaseOption(bool m) : memory(m) {}
  PhaseOption(bool m, int64_t ms) : memory(m), memory_gpu(false), memory_interval(ms) {}
  PhaseOption(bool m, bool mg) : memory(m), memory_gpu(mg) {}
  PhaseOption(bool m, bool mg, int64_t ms) : memory(m), memory_gpu(mg), memory_interval(ms) {}

  bool memory = false;
  bool memory_gpu = false;     // very specific...
  int64_t memory_interval = 5; // ms
};

} // namespace benchmark

namespace std
{

template <> struct hash<benchmark::PhaseEnum>
{
  size_t operator()(benchmark::PhaseEnum value) const noexcept
  {
    using type = typename std::underlying_type<benchmark::PhaseEnum>::type;
    return hash<type>()(static_cast<type>(value));
  }
};

} // namespace std

#endif // __NNFW_BENCHMARK_PHASE_H__
