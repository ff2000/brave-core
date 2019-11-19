/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_ATTESTATION_ATTESTATION_ANDROID_H_
#define BRAVELEDGER_ATTESTATION_ATTESTATION_ANDROID_H_

#include <map>
#include <string>

#include "bat/ledger/internal/attestation/attestation.h"

namespace bat_ledger {
class LedgerImpl;
}

namespace braveledger_attestation {

class AttestationAndroid : public Attestation {
 public:
  explicit AttestationAndroid(bat_ledger::LedgerImpl* ledger);
  ~AttestationAndroid() override;

  void Start(const std::string& payload, StartCallback callback) override;

  void Confirm(
      const std::string& solution,
      ConfirmCallback callback) override;

 private:
  void ParseClaimSolution(
      const std::string& response,
      base::Value* result);

  void OnStart(
      const int response_status_code,
      const std::string& response,
      const std::map<std::string, std::string>& headers,
      StartCallback callback);

  void OnConfirm(
      const int response_status_code,
      const std::string& response,
      const std::map<std::string, std::string>& headers,
      ConfirmCallback callback);
};

}  // namespace braveledger_attestation
#endif  // BRAVELEDGER_ATTESTATION_ATTESTATION_ANDROID_H_
