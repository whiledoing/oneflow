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
#include "oneflow/core/kernel/copy_hd_kernel.h"

namespace oneflow {

#ifdef WITH_CUDA

void CopyHdKernel::ForwardDataContent(const KernelCtx& ctx,
                                      std::function<Blob*(const std::string&)> BnInOp2Blob) const {
  const Blob* in_blob = BnInOp2Blob(op_attribute().input_bns(0));
  Blob* out_blob = BnInOp2Blob(op_attribute().output_bns(0));
  out_blob->CopyValidDataContentFrom(ctx.device_ctx, in_blob);
}

void CopyHdKernel::ForwardHeader(const KernelCtx& ctx,
                                 std::function<Blob*(const std::string&)> BnInOp2Blob) const {
  BnInOp2Blob("out")->CopyHeaderFrom(ctx.device_ctx, BnInOp2Blob("in"));
}

REGISTER_KERNEL(OperatorConf::kCopyHdConf, CopyHdKernel);

#endif

}  // namespace oneflow
