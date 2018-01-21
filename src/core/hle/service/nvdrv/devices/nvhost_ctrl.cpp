// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/assert.h"
#include "common/logging/log.h"
#include "core/hle/service/nvdrv/devices/nvhost_ctrl.h"

namespace Service {
namespace Nvidia {
namespace Devices {

u32 nvhost_ctrl::ioctl(u32 command, const std::vector<u8>& input, std::vector<u8>& output) {
    LOG_WARNING(Debug_GPU, "Got Ioctl 0x%x, inputsz: 0x%x, outputsz: 0x%x", command, input.size(),
                output.size());

    switch (command) {
    case IocGetConfigCommand:
        return NvOsGetConfigU32(input, output);
    }
    UNIMPLEMENTED();
    return 0;
}

u32 nvhost_ctrl::NvOsGetConfigU32(const std::vector<u8>& input, std::vector<u8>& output) {
    LOG_WARNING(Service, "(STUBBED) lets do it");
    IocGetConfigParams params;
    std::memcpy(&params, input.data(), sizeof(params));
    LOG_WARNING(Service, "(STUBBED) param_str %s", params.param_str);
    LOG_WARNING(Service, "(STUBBED) domain_str %s", params.domain_str);

    if (!strcmp(params.domain_str.data(), "nv")) {
        if (!strcmp(params.param_str.data(), "NV_MEMORY_PROFILER")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVN_THROUGH_OPENGL")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_PREVENT_USE")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_CHANNEL_PRIORITY")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_CHANNEL_INTERLEAVE")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_CHANNEL_TIMESLICE")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_DEFAULT_DEVICE_INDEX")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_IOCTL_MUTEX")) {
            std::memcpy(params.config_str.data(), "1", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_DUMMY")) {
            std::memcpy(params.config_str.data(), "", 0);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_DISABLE")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_GPU_CHARACTERISTICS")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_SYNCPOINTS")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_MAP_BUFFER_EX")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_ROBUSTNESS")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_CYCLESTATS")) {
            std::memcpy(params.config_str.data(), "1", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_DO_NFA_PARTIAL_MAP")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_AS_GET_VA_REGIONS")) {
            std::memcpy(params.config_str.data(), "1", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_SPARSE")) {
            std::memcpy(params.config_str.data(), "1", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_FIXED")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_CHANNEL_ABORT")) {
            std::memcpy(params.config_str.data(), "1", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_ZBC")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_TSG")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_WRAP_CHANNELS_IN_TSGS")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_ECC_OVERRIDES")) {
            std::memcpy(params.config_str.data(), "0", 1);
        } else if (!strcmp(params.param_str.data(), "NVRM_GPU_NVGPU_NO_ZCULL")) {
            std::memcpy(params.config_str.data(), "1", 1);
        } else {
            //UNIMPLEMENTED();
        }
    } else {
        UNIMPLEMENTED();
    }
    std::memcpy(output.data(), &params, sizeof(params));
    LOG_WARNING(Service, "(STUBBED) memcpy");
    return 0;
}

} // namespace Devices
} // namespace Nvidia
} // namespace Service
