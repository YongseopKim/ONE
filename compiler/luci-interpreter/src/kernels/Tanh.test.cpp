/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 * Copyright 2017 The TensorFlow Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "kernels/Tanh.h"
#include "kernels/TestUtils.h"

namespace luci_interpreter
{
namespace kernels
{
namespace
{

using namespace testing;

TEST(TanhTest, Float)
{
  Shape input_shape{1, 2, 4, 1};
  std::vector<float> input_data{
      0, -6, 2,  4, //
      3, -2, 10, 1, //
  };
  Tensor input_tensor = makeInputTensor<DataType::FLOAT32>(input_shape, input_data);
  Tensor output_tensor = makeOutputTensor(DataType::FLOAT32);

  Tanh kernel(&input_tensor, &output_tensor);
  kernel.configure();
  kernel.execute();

  std::vector<float> ref_output_data{
      0,          -0.9999877, 0.9640275, 0.999329,  //
      0.99505475, -0.9640275, 1,         0.7615941, //
  };
  EXPECT_THAT(extractTensorData<float>(output_tensor),
              ElementsAreArray(ArrayFloatNear(ref_output_data)));
}

TEST(TanhTest, Uint8)
{
  float kMin = -1;
  float kMax = 127.f / 128.f;
  float kTanhTolerance = 2 * (1. / 256);
  std::pair<float, int32_t> input_quant_param = quantizationParams<uint8_t>(8 * kMin, 8 * kMax);
  std::pair<float, int32_t> output_quant_param = quantizationParams<uint8_t>(kMin, kMax);
  std::vector<float> input_data{
      0,  -6, 2, 4, //
      -4, -2, 8, 1, //
      0,  -6, 2, 4, //
      -4, -2, 8, 1, //
      0,  -6, 2, 4, //
      -4, -2, 8, 1, //
      0,  -6, 2, 4, //
      -4, -2, 8, 1, //
      0,  -6, 2, 4, //
      -4, -2, 8, 1, //
      0,  -6, 2, 4, //
      -4, -2, 8, 1, //
  };
  Tensor input_tensor{
      DataType::U8, {2, 6, 4, 1}, {{input_quant_param.first}, {input_quant_param.second}}, ""};
  Tensor output_tensor =
      makeOutputTensor(DataType::U8, output_quant_param.first, output_quant_param.second);
  std::vector<uint8_t> quantize_input =
      quantize<uint8_t>(input_data, input_quant_param.first, input_quant_param.second);
  input_tensor.writeData(quantize_input.data(), quantize_input.size() * sizeof(uint8_t));

  Tanh kernel(&input_tensor, &output_tensor);
  kernel.configure();
  kernel.execute();

  std::vector<float> ref_output_data{
      0.0,       -0.999987, 0.964027, 0.999329, //
      -0.999329, -0.96402,  0.99999,  0.76159,  //
      0.0,       -0.999987, 0.964027, 0.999329, //
      -0.999329, -0.96402,  0.99999,  0.76159,  //
      0.0,       -0.999987, 0.964027, 0.999329, //
      -0.999329, -0.96402,  0.99999,  0.76159,  //
      0.0,       -0.999987, 0.964027, 0.999329, //
      -0.999329, -0.96402,  0.99999,  0.76159,  //
      0.0,       -0.999987, 0.964027, 0.999329, //
      -0.999329, -0.96402,  0.99999,  0.76159,  //
      0.0,       -0.999987, 0.964027, 0.999329, //
      -0.999329, -0.96402,  0.99999,  0.76159,  //
  };
  std::vector<int32_t> ref_output_shape{2, 6, 4, 1};
  EXPECT_THAT(dequantize<uint8_t>(extractTensorData<uint8_t>(output_tensor), output_tensor.scale(),
                                  output_tensor.zero_point()),
              ElementsAreArray(ArrayFloatNear(ref_output_data, kTanhTolerance)));
  EXPECT_THAT(extractTensorShape(output_tensor), ::testing::ElementsAreArray(ref_output_shape));
}

} // namespace
} // namespace kernels
} // namespace luci_interpreter