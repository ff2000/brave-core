/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/core/origin_trials/origin_trial_context.h"

#define AddFeature AddFeature_ChromiumImpl
#define AddForceEnabledTrials AddForceEnabledTrials_ChromiumImpl
#include "../../../../../../../third_party/blink/renderer/core/origin_trials/origin_trial_context.cc"
#undef AddForceEnabledTrials
#undef AddFeature

namespace blink {

// AddFeature doesn't check if origin_trials::IsTrialValid.
void OriginTrialContext::AddFeature(OriginTrialFeature feature) {
  static const std::array<OriginTrialFeature, 2> kBraveDisabledTrialFeatures = {
      OriginTrialFeature::kSubresourceWebBundles,
      OriginTrialFeature::kSignedExchangeSubresourcePrefetch,
  };
  if (base::Contains(kBraveDisabledTrialFeatures, feature))
    return;

  AddFeature_ChromiumImpl(feature);
}

// AddForceEnabledTrials only has a DCHECK with origin_trials::IsTrialValid.
void OriginTrialContext::AddForceEnabledTrials(
    const Vector<String>& trial_names) {
  static const char* const kBraveDisabledTrialNames[] = {
      "SubresourceWebBundles",
      "SignedExchangeSubresourcePrefetch"
  };

  for (const auto* disabled_name : kBraveDisabledTrialNames) {
    if (base::Contains(trial_names, disabled_name))
      return;
  }

  AddForceEnabledTrials_ChromiumImpl(trial_names);
}

}  // namespace blink
