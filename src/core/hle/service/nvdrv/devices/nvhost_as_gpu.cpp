// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/assert.h"
#include "common/logging/log.h"
#include "core/hle/service/nvdrv/devices/nvhost_as_gpu.h"

namespace Service {
namespace Nvidia {
namespace Devices {

u32 nvhost_as_gpu::ioctl(u32 command, const std::vector<u8>& input, std::vector<u8>& output) {
    LOG_WARNING(Debug_GPU, "Got Ioctl 0x%x, inputsz: 0x%x, outputsz: 0x%x", command, input.size(),
                output.size());
    switch (command) {
    case IocInitalizeExCommand:
        return InitalizeEx(input, output);
    case IocAllocateSpaceCommand:
        return AllocateSpace(input, output);
    case IocMapBufferExCommand:
        return MapBufferEx(input, output);
    case IocBindChannelCommand:
        return BindChannel(input, output);
    }

    UNIMPLEMENTED();
    return 0;
}

u32 nvhost_as_gpu::InitalizeEx(const std::vector<u8>& input, std::vector<u8>& output) {
    initalize_ex params;
    std::memcpy(&params, input.data(), input.size());
    LOG_WARNING(Service, "(STUBBED) called, big_page_size=0x%x", params.big_page_size);
    std::memcpy(output.data(), &params, output.size());
    return 0;
}

u32 nvhost_as_gpu::AllocateSpace(const std::vector<u8>& input, std::vector<u8>& output) {
    alloc_space params;
    std::memcpy(&params, input.data(), input.size());
    LOG_WARNING(Service, "(STUBBED) called, pages=%x, page_size=%x, flags=%x", params.pages,
                params.page_size, params.flags);
    params.offset = 0xdeadbeef;
    std::memcpy(output.data(), &params, output.size());
    // UNIMPLEMENTED();
    return 0;
}

u32 nvhost_as_gpu::MapBufferEx(const std::vector<u8>& input, std::vector<u8>& output) {
    map_buffer_ex params;
    std::memcpy(&params, input.data(), input.size());
    LOG_WARNING(Service,
                "(STUBBED) called, flags=%x, nvmap_handle=%x, buffer_offset=%lx, mapping_size=%lx, "
                "offset=%lx",
                params.flags, params.nvmap_handle, params.buffer_offset, params.mapping_size,
                params.offset);
    params.offset = 0xdeadbeef;
    std::memcpy(output.data(), &params, output.size());
    // UNIMPLEMENTED();
    return 0;
}

u32 nvhost_as_gpu::BindChannel(const std::vector<u8>& input, std::vector<u8>& output) {
    bind_channel params;
    std::memcpy(&params, input.data(), input.size());
    LOG_WARNING(Service, "(STUBBED) called, fd=%x", params.fd);
    channel = params.fd;

    std::memcpy(output.data(), &params, output.size());
    // UNIMPLEMENTED();
    return 0;
}

} // namespace Devices
} // namespace Nvidia
} // namespace Service
