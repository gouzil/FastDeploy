// Copyright (c) 2023 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include "fastdeploy_capi/config.h"

#ifdef ENABLE_VISION
#include "fastdeploy_capi/vision/classification/ppcls/model.h"
#include "fastdeploy_capi/vision/detection/ppdet/model.h"
#include "fastdeploy_capi/vision/ocr/ppocr/model.h"
#include "fastdeploy_capi/vision/result.h"
#include "fastdeploy_capi/vision/visualize.h"
#endif

#include "fastdeploy_capi/fd_type.h"
#include "fastdeploy_capi/runtime_option.h"
