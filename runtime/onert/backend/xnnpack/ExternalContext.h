/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __ONERT_BACKEND_XNNPACK_EXTERNAL_CONTEXT_H__
#define __ONERT_BACKEND_XNNPACK_EXTERNAL_CONTEXT_H__

#include <backend/IExternalContext.h>
#include <util/ConfigSource.h>

namespace
{
const int kDefaultNumThreadpoolThreads = 1;
}

namespace onert
{
namespace backend
{
namespace xnnpack
{

// TODO: Use threadpool of xnnpack
class ExternalContext : public IExternalContext
{
public:
  ExternalContext() = default;
};

} // namespace xnnpack
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_XNNPACK_EXTERNAL_CONTEXT_H__
