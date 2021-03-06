/*
Copyright 2020 The OneFlow Authors. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "oneflow/core/common/error.h"
#include "oneflow/core/common/protobuf.h"
#include "oneflow/core/common/util.h"

namespace oneflow {

namespace {

void LogError(const Error& error) {
  // gdb break point
  LOG(ERROR) << error->msg();
}

}  // namespace

Error::operator std::string() const { return PbMessage2TxtString(*error_proto_); }

Error Error::Ok() { return std::make_shared<ErrorProto>(); }

Error Error::ProtoParseFailedError() {
  auto error = std::make_shared<ErrorProto>();
  error->mutable_proto_parse_failed_error();
  return error;
}

Error Error::JobSetEmpty() {
  auto error = std::make_shared<ErrorProto>();
  error->set_job_build_and_infer_error(JobBuildAndInferError::kJobSetEmpty);
  return error;
}

Error Error::DeviceTagNotFound() {
  auto error = std::make_shared<ErrorProto>();
  error->set_job_build_and_infer_error(JobBuildAndInferError::kDeviceTagNotFound);
  return error;
}

Error Error::JobTypeNotSet() {
  auto error = std::make_shared<ErrorProto>();
  error->set_job_build_and_infer_error(JobBuildAndInferError::kJobTypeNotSet);
  return error;
}

Error Error::CheckFailedError() {
  auto error = std::make_shared<ErrorProto>();
  error->mutable_check_failed_error();
  return error;
}

Error Error::Todo() {
  auto error = std::make_shared<ErrorProto>();
  error->mutable_todo_error();
  return error;
}

Error Error::Unimplemented() {
  auto error = std::make_shared<ErrorProto>();
  error->mutable_unimplemented_error();
  return error;
}

Error Error::BoxingNotSupported() {
  auto error = std::make_shared<ErrorProto>();
  error->set_boxing_error(BoxingError::kNotSupported);
  return error;
}

Error Error::OpKernelNotFoundError(const std::string& error_summary,
                                   const std::vector<std::string>& error_msgs) {
  auto error = std::make_shared<ErrorProto>();
  error->set_error_summary(error_summary);
  auto* op_kernel_not_found_error = error->mutable_op_kernel_not_found_error();
  for (const auto& msg : error_msgs) {
    op_kernel_not_found_error->add_op_kernels_not_found_debug_str(msg);
  }
  return error;
}

Error Error::MultipleOpKernelsMatchedError(const std::string& error_summary,
                                           const std::vector<std::string>& error_msgs) {
  auto error = std::make_shared<ErrorProto>();
  error->set_error_summary(error_summary);
  auto* multiple_op_kernels_matched_error = error->mutable_multiple_op_kernels_matched_error();
  for (const auto& msg : error_msgs) {
    multiple_op_kernels_matched_error->add_matched_op_kernels_debug_str(msg);
  }
  return error;
}

Error Error::MemoryZoneOutOfMemoryError(int64_t machine_id, int64_t mem_zone_id, uint64_t calc,
                                        uint64_t available, const std::string& device_tag) {
  auto error = std::make_shared<ErrorProto>();
  auto* memory_zone_out_of_memory_error = error->mutable_memory_zone_out_of_memory_error();
  memory_zone_out_of_memory_error->add_machine_id(std::to_string(machine_id));
  memory_zone_out_of_memory_error->add_mem_zone_id(std::to_string(mem_zone_id));
  memory_zone_out_of_memory_error->add_device_tag(device_tag);
  memory_zone_out_of_memory_error->add_available(std::to_string(available) + " bytes");
  memory_zone_out_of_memory_error->add_required(std::to_string(calc) + " bytes");
  return error;
}

Error Error::LossBlobNotFoundError(const std::string& error_summary) {
  auto error = std::make_shared<ErrorProto>();
  error->mutable_loss_blob_not_found_error();
  error->set_error_summary(error_summary);
  return error;
}

Error Error::GradientFunctionNotFound() {
  auto error = std::make_shared<ErrorProto>();
  error->mutable_gradient_function_not_found_error();
  return error;
}

Error&& operator<=(const std::pair<std::string, std::string>& loc_and_func, Error&& error) {
  LogError(error);
  CHECK(error.error_proto()->stack_frame().empty());
  auto* stack_frame = error.error_proto()->add_stack_frame();
  stack_frame->set_location(loc_and_func.first);
  stack_frame->set_function(loc_and_func.second);
  return std::move(error);
}

}  // namespace oneflow
