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

#include <matter_drivers.h>

#include <media_playback/ameba_media_playback_delegate.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app/util/config.h>

#include <string>

using namespace chip;
using namespace chip::app;
using namespace chip::app::DataModel;
using namespace chip::app::Clusters::MediaPlayback;
using namespace chip::Uint8;
using chip::CharSpan;

void AmebaMediaPlaybackManagerInit(uint8_t endpoint)
{
    AmebaMediaPlaybackDelegate * mgr = new AmebaMediaPlaybackDelegate();
    chip::app::Clusters::MediaPlayback::SetDefaultDelegate(static_cast<EndpointId>(endpoint), mgr);
}

PlaybackStateEnum AmebaMediaPlaybackDelegate::HandleGetCurrentState()
{
    return mCurrentState;
}

uint64_t AmebaMediaPlaybackDelegate::HandleGetStartTime()
{
    return mStartTime;
}

uint64_t AmebaMediaPlaybackDelegate::HandleGetDuration()
{
    return mDuration;
}

CHIP_ERROR AmebaMediaPlaybackDelegate::HandleGetSampledPosition(AttributeValueEncoder & aEncoder)
{
    return aEncoder.Encode(mPlaybackPosition);
}

float AmebaMediaPlaybackDelegate::HandleGetPlaybackSpeed()
{
    return mPlaybackSpeed;
}

uint64_t AmebaMediaPlaybackDelegate::HandleGetSeekRangeStart()
{
    return mStartTime;
}

uint64_t AmebaMediaPlaybackDelegate::HandleGetSeekRangeEnd()
{
    return mDuration;
}

CHIP_ERROR AmebaMediaPlaybackDelegate::HandleGetActiveAudioTrack(AttributeValueEncoder & aEncoder)
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

CHIP_ERROR AmebaMediaPlaybackDelegate::HandleGetAvailableAudioTracks(AttributeValueEncoder & aEncoder)
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

CHIP_ERROR AmebaMediaPlaybackDelegate::HandleGetActiveTextTrack(AttributeValueEncoder & aEncoder)
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

CHIP_ERROR AmebaMediaPlaybackDelegate::HandleGetAvailableTextTracks(AttributeValueEncoder & aEncoder)
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

/* Commands */
/* PlaybackSpeed:   1: indicate normal playback
                    > 0: indicate that as playback is happening the meida is currently advancing in time within the duration of the media
                    < 0: indicate that as playback is happening the media is currently going back iin time within the duration of the media
                    0: indicate the media is currently not playing back. CurrentState = PAUSED, NOT PLAYING, BUFFERING*/
/* PlaybackResponse
 * data: optional app-specific data
 * status: Success, InvalidStateForCommand, NotAllowed, NotActive
*/
void AmebaMediaPlaybackDelegate::HandlePlay(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    mCurrentState  = PlaybackStateEnum::kPlaying;
    mPlaybackSpeed = 1;

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);

    matter_driver_media_playback_handler("play");
}

void AmebaMediaPlaybackDelegate::HandlePause(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    mCurrentState  = PlaybackStateEnum::kPaused;
    mPlaybackSpeed = 0;

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);

    matter_driver_media_playback_handler("pause");
}

void AmebaMediaPlaybackDelegate::HandleStop(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    mCurrentState     = PlaybackStateEnum::kNotPlaying;
    mPlaybackSpeed    = 0;
    mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(0) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);

    matter_driver_media_playback_handler("stop");
}

void AmebaMediaPlaybackDelegate::HandleStartOver(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(0) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);
}

void AmebaMediaPlaybackDelegate::HandlePrevious(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    mCurrentState     = PlaybackStateEnum::kPlaying;
    mPlaybackSpeed    = 1;
    mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(0) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);

    matter_driver_media_playback_handler("play");
}

void AmebaMediaPlaybackDelegate::HandleNext(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper)
{
    mCurrentState     = PlaybackStateEnum::kPlaying;
    mPlaybackSpeed    = 1;
    mPlaybackPosition = { 0, chip::app::DataModel::Nullable<uint64_t>(0) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);

    matter_driver_media_playback_handler("play");
}

void AmebaMediaPlaybackDelegate::HandleRewind(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                        const chip::Optional<bool> & audioAdvanceUnmuted)
{
    // TODO: Insert code here
}

void AmebaMediaPlaybackDelegate::HandleFastForward(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                             const chip::Optional<bool> & audioAdvanceUnmuted)
{
    // TODO: Insert code here
}

void AmebaMediaPlaybackDelegate::HandleSkipForward(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                             const uint64_t & deltaPositionMilliseconds)
{
    uint64_t newPosition = mPlaybackPosition.position.Value() + deltaPositionMilliseconds;
    newPosition          = newPosition > mDuration ? mDuration : newPosition;
    mPlaybackPosition    = { 0, chip::app::DataModel::Nullable<uint64_t>(newPosition) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);
}

void AmebaMediaPlaybackDelegate::HandleSkipBackward(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                              const uint64_t & deltaPositionMilliseconds)
{
    uint64_t newPosition = (mPlaybackPosition.position.Value() > deltaPositionMilliseconds
                                ? mPlaybackPosition.position.Value() - deltaPositionMilliseconds
                                : 0);
    mPlaybackPosition    = { 0, chip::app::DataModel::Nullable<uint64_t>(newPosition) };

    Commands::PlaybackResponse::Type response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("optional app-specific data"));
    response.status = StatusEnum::kSuccess;
    helper.Success(response);
}

void AmebaMediaPlaybackDelegate::HandleSeek(CommandResponseHelper<Commands::PlaybackResponse::Type> & helper,
                                      const uint64_t & positionMilliseconds)
{
    // TODO: Insert code here
}

bool AmebaMediaPlaybackDelegate::HandleActivateAudioTrack(const chip::CharSpan & trackId, const uint8_t & audioOutputIndex)
{
    // TODO: Insert code here
    return false;
}

bool AmebaMediaPlaybackDelegate::HandleActivateTextTrack(const chip::CharSpan & trackId)
{
    // TODO: Insert code here
    return false;
}

bool AmebaMediaPlaybackDelegate::HandleDeactivateTextTrack()
{
    // TODO: Insert code here
    return false;
}

uint32_t AmebaMediaPlaybackDelegate::GetFeatureMap(chip::EndpointId endpoint)
{
    uint32_t featureMap = 0;
    Attributes::FeatureMap::Get(endpoint, &featureMap);
    return featureMap;
}

uint16_t AmebaMediaPlaybackDelegate::GetClusterRevision(chip::EndpointId endpoint)
{
    uint16_t clusterRevision = 0;
    bool success =
        (Attributes::ClusterRevision::Get(endpoint, &clusterRevision) == chip::Protocols::InteractionModel::Status::Success);
    if (!success)
    {
        ChipLogError(Zcl, "AmebaMediaPlaybackDelegate::GetClusterRevision error reading cluster revision");
    }
    return clusterRevision;
}
