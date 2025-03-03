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

#include "fastdeploy/vision.h"

static bool CreateRuntimeOption(fastdeploy::RuntimeOption* option,
                        int argc, char* argv[], bool remove_flags) {
  google::ParseCommandLineFlags(&argc, &argv, remove_flags);
  if (FLAGS_profile_mode == "runtime") {
    option->EnableProfiling(FLAGS_include_h2d_d2h, FLAGS_repeat, FLAGS_warmup);
  }
  if (FLAGS_device == "gpu") {
    option->UseGpu(FLAGS_device_id);
    if (FLAGS_backend == "ort") {
      option->UseOrtBackend();
    } else if (FLAGS_backend == "paddle") {
      option->UsePaddleInferBackend();
    } else if (FLAGS_backend == "trt" || FLAGS_backend == "paddle_trt") {
      option->UseTrtBackend();
      if (FLAGS_backend == "paddle_trt") {
        option->UsePaddleInferBackend();
        option->paddle_infer_option.enable_trt = true;
      }
      if (FLAGS_use_fp16) {
        option->trt_option.enable_fp16 = true;
      }
    } else if (FLAGS_backend == "default") {
      return true;
    } else {
      std::cout << "While inference with GPU, only support "
                   "default/ort/paddle/trt/paddle_trt now, "
                << FLAGS_backend << " is not supported." << std::endl;
      PrintUsage();
      return false;
    }
  } else if (FLAGS_device == "cpu") {
    option->SetCpuThreadNum(FLAGS_cpu_thread_nums);
    if (FLAGS_backend == "ort") {
      option->UseOrtBackend();
    } else if (FLAGS_backend == "ov") {
      option->UseOpenVINOBackend();
    } else if (FLAGS_backend == "paddle") {
      option->UsePaddleInferBackend();
    } else if (FLAGS_backend == "lite") {
      option->UsePaddleLiteBackend();
      if (FLAGS_use_fp16) {
        option->paddle_lite_option.enable_fp16 = true;
      }
    } else if (FLAGS_backend == "default") {
      return true;
    } else {
      std::cout << "While inference with CPU, only support "
                   "default/ort/ov/paddle/lite now, "
                << FLAGS_backend << " is not supported." << std::endl;
      PrintUsage();
      return false;
    }
  } else if (FLAGS_device == "xpu") {
    option->UseKunlunXin(FLAGS_device_id);
    if (FLAGS_backend == "ort") {
      option->UseOrtBackend();
    } else if (FLAGS_backend == "paddle") {
      option->UsePaddleInferBackend();
    } else if (FLAGS_backend == "lite") {
      option->UsePaddleLiteBackend();
      if (FLAGS_use_fp16) {
        option->paddle_lite_option.enable_fp16 = true;
      }
    } else if (FLAGS_backend == "default") {
      return true;
    } else {
      std::cout << "While inference with XPU, only support "
                   "default/ort/paddle/lite now, "
                << FLAGS_backend << " is not supported." << std::endl;
      PrintUsage();
      return false;
    }
  } else {
    std::cerr << "Only support device CPU/GPU/XPU now, " << FLAGS_device
              << " is not supported." << std::endl;
    PrintUsage();
    return false;
  }
  PrintBenchmarkInfo();
  return true;
}
