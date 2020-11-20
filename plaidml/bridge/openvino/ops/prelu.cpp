// Copyright (C) 2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "plaidml_ops.hpp"
#include "plaidml_util.hpp"

#include "ngraph/opsets/opset.hpp"
#include "ngraph/opsets/opset1.hpp"

#include "plaidml/op/op.h"

using namespace plaidml;          // NOLINT[build/namespaces]
using namespace InferenceEngine;  // NOLINT[build/namespaces]

namespace PlaidMLPlugin {

static OpRegistration reg("prelu", [](const Context& ctx) {
  IE_ASSERT(ctx.operands.size() == 2);
  auto I = ctx.operands.at(0);
  auto slope = ctx.operands.at(1);
  DType target_type = to_plaidml(ctx.layer->get_default_output().get_element_type());
  auto O = select(I < 0.0, cast(slope * I, target_type), cast(I, target_type));
  return edsl::make_tuple(O);
});

}  // namespace PlaidMLPlugin
