/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "support/CommandLine.h"
#include "mir/IrDotDumper.h"

#include <caffe_importer.h>

#include <exception>
#include <iostream>

using namespace nnc;
using namespace mir;

int main(int argc, const char **argv)
{
  cli::Option<std::string> model_path(cli::optname("--model"), cli::overview("Path to the model"));
  cli::CommandLine::getParser()->parseCommandLine(argc, argv);

  try
  {
    auto graph = mir_caffe::loadModel(model_path);
    dumpGraph(graph.get(), std::cout);
  }
  catch (std::exception &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}
