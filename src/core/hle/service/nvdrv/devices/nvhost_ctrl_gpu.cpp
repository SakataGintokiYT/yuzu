// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/assert.h"
#include "common/logging/log.h"
#include "core/hle/service/nvdrv/devices/nvhost_ctrl_gpu.h"

namespace Service {
namespace Nvidia {
namespace Devices {

u32 nvhost_ctrl_gpu::ioctl(u32 command, const std::vector<u8>& input, std::vector<u8>& output) {
    LOG_WARNING(Debug_GPU, "Got Ioctl 0x%x, inputsz: 0x%x, outputsz: 0x%x", command, input.size(),
                output.size());

    switch (command) {
    case IocGetCharacteristicsCommand:
        return GetCharacteristics(input, output);
    case IocGetTPCMasksCommand:
        return GetTPCMasks(input, output);
    case IocGetActiveSlotMaskCommand:
        return GetActiveSlotMask(input, output);
    }
    /*
    switch (command) {
    case IocGetConfigCommand:
        return NvOsGetConfigU32(input, output);
    }*/
    UNIMPLEMENTED();
    return 0;
}

u32 nvhost_ctrl_gpu::GetTPCMasks(const std::vector<u8>& input, std::vector<u8>& output) {
    nvgpu_gpu_get_tpc_masks_args params;
    std::memcpy(&params, input.data(), sizeof(params));
    LOG_WARNING(Service, "(STUBBED) called, mask=0x%x, mask_buf_addr=0x%lx", params.mask_buf_size,
                params.mask_buf_addr);
    std::memcpy(output.data(), &params, sizeof(params));
    return 0;
    // UNIMPLEMENTED();
}

u32 nvhost_ctrl_gpu::GetActiveSlotMask(const std::vector<u8>& input, std::vector<u8>& output) {
    active_slot_mask params{};
    std::memcpy(&params, input.data(), input.size());
    params.mask = 0x00;
    params.slot = 0x07;
    std::memcpy(output.data(), &params, output.size());
    return 0;
    // UNIMPLEMENTED();
}

u32 nvhost_ctrl_gpu::GetCharacteristics(const std::vector<u8>& input, std::vector<u8>& output) {
    LOG_WARNING(Service, "(STUBBED) called");
    characteristics params;
    // std::memcpy(&params, input.data(), sizeof(params));
    params.gc.arch = 0x120;
    params.gc.impl = 0xb;
    params.gc.rev = 0xa1;
    params.gc.num_gpc = 0x1;
    params.gc.l2_cache_size = 0x40000;
    params.gc.on_board_video_memory_size = 0x0;
    params.gc.num_tpc_per_gpc = 0x2;
    params.gc.bus_type = 0x20;
    params.gc.big_page_size = 0x20000;
    params.gc.compression_page_size = 0x20000;
    params.gc.pde_coverage_bit_count = 0x1B;
    params.gc.available_big_page_sizes = 0x30000;
    params.gc.gpc_mask = 0x1;
    params.gc.sm_arch_sm_version = 0x503;
    params.gc.sm_arch_spa_version = 0x503;
    params.gc.sm_arch_warp_count = 0x80;
    params.gc.gpu_va_bit_count = 0x28;
    params.gc.reserved = 0x0;
    params.gc.flags = 0x55;
    params.gc.twod_class = 0x902D;
    params.gc.threed_class = 0xB197;
    params.gc.compute_class = 0xB1C0;
    params.gc.gpfifo_class = 0xB06F;
    params.gc.inline_to_memory_class = 0xA140;
    params.gc.dma_copy_class = 0xB0B5;
    params.gc.max_fbps_count = 0x1;
    params.gc.fbp_en_mask = 0x0;
    params.gc.max_ltc_per_fbp = 0x2;
    params.gc.max_lts_per_ltc = 0x1;
    params.gc.max_tex_per_tpc = 0x0;
    params.gc.max_gpc_count = 0x1;
    params.gc.rop_l2_en_mask_0 = 0x21D70;
    params.gc.rop_l2_en_mask_1 = 0x0;
    params.gc.chipname = 0x6230326D67;
    params.gc.gr_compbit_store_base_hw = 0x0;
    params.gpu_characteristics_buf_size = 0xA0;
    params.gpu_characteristics_buf_addr = 0xdeadbeef;
    std::memcpy(output.data(), &params, sizeof(params));
    return 0x0;
}

} // namespace Devices
} // namespace Nvidia
} // namespace Service
