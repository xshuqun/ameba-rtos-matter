/*
 *    This module is a confidential and proprietary property of RealTek and
 *    possession or use of this module requires written permission of RealTek.
 *
 *    Copyright(c) 2025, Realtek Semiconductor Corporation. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <app-common/zap-generated/cluster-objects.h>
#include <app/clusters/microwave-oven-control-server/microwave-oven-control-server.h>
#include <app/clusters/operational-state-server/operational-state-server.h>

#include <app/util/config.h>
#include <cstring>
#include <protocols/interaction_model/StatusCode.h>
#include <utility>

namespace chip {
namespace app {
namespace Clusters {

namespace MicrowaveOvenControl {

class AmebaMicrowaveOvenControlDelegate : public MicrowaveOvenControl::Delegate
{

public:
    /**
     * Handle command for microwave oven control: set cooking parameters
     */
    Protocols::InteractionModel::Status HandleSetCookingParametersCallback(uint8_t cookMode, uint32_t cookTimeSec,
                                                                           bool startAfterSetting,
                                                                           Optional<uint8_t> powerSettingNum,
                                                                           Optional<uint8_t> wattSettingIndex) override;

    /**
     * Handle command for microwave oven control: add more time
     */
    Protocols::InteractionModel::Status HandleModifyCookTimeSecondsCallback(uint32_t finalcookTimeSec) override;

    /**
     *   Get the watt setting from the supported watts array.
     *   @param index The index of the watt setting to be returned. It is assumed that watt setting are indexable from 0 and with no
     * gaps.
     *   @param wattSetting A reference to receive the watt setting on success.
     *   @return Returns a CHIP_NO_ERROR if there was no error and the label was returned successfully.
     *   CHIP_ERROR_NOT_FOUND if the index in beyond the list of available labels.
     */
    CHIP_ERROR GetWattSettingByIndex(uint8_t index, uint16_t & wattSetting) override;

    /**
     * Get the value of power setting number.
     */
    uint8_t GetPowerSettingNum() const override { return mPowerSettingNum; }

    /**
     * Get the value of min power number.
     */
    uint8_t GetMinPowerNum() const override { return kMinPowerNum; }

    /**
     * Get the value of max power number.
     */
    uint8_t GetMaxPowerNum() const override { return kMaxPowerNum; }

    /**
     * Get the value of power step number.
     */
    uint8_t GetPowerStepNum() const override { return kPowerStepNum; }

    /**
     * Get the value of max cook time in seconds.
     */
    uint32_t GetMaxCookTimeSec() const override { return kMaxCookTimeSec; }

    /**
     * Get the value of selected watt index.
     */
    uint8_t GetCurrentWattIndex() const override { return mSelectedWattIndex; };

    /**
     * Get the value of watt rating.
     */
    uint16_t GetWattRating() const override { return mWattRating; };

private:

    // set default value for the optional attributes
    static constexpr uint8_t kMinPowerNum            = 20u;
    static constexpr uint8_t kMaxPowerNum            = 90u;
    static constexpr uint8_t kPowerStepNum           = 10u;
    static constexpr uint32_t kMaxCookTimeSec        = 86400u;
    static constexpr uint8_t kDefaultPowerSettingNum = kMaxPowerNum;

    // define the mode value
    static constexpr uint8_t kModeNormal  = 0u;
    static constexpr uint8_t kModeDefrost = 1u;

    // define the example watts
    static constexpr uint16_t kExampleWatt1 = 100u;
    static constexpr uint16_t kExampleWatt2 = 300u;
    static constexpr uint16_t kExampleWatt3 = 500u;
    static constexpr uint16_t kExampleWatt4 = 800u;
    static constexpr uint16_t kExampleWatt5 = 1000u;

    // MicrowaveOvenControl variables
    uint8_t mPowerSettingNum   = kDefaultPowerSettingNum;
    uint8_t mSelectedWattIndex = 0;
    uint16_t mWattRating       = 0;

    const uint16_t mWattSettingList[5] = { kExampleWatt1, kExampleWatt2, kExampleWatt3, kExampleWatt4, kExampleWatt5 };
};

} // namespace MicrowaveOvenControl

} // namespace Clusters
} // namespace app
} // namespace chip
