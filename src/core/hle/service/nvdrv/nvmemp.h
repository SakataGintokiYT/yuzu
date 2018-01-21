// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service {
namespace Nvidia {

class NVMEMP final : public ServiceFramework<NVMEMP> {
public:
    NVMEMP();
    ~NVMEMP() = default;

private:
    void Unknown0(Kernel::HLERequestContext& ctx) {
        ctx.DumpIPC();
        IPC::RequestParser rp{ctx};
        for (int i = 0; i < 32; i++)
            printf("%lx\n", rp.Pop<u64>());
        // IPC::RequestBuilder rb{ctx, 1};
        // rb.Push(RESULT_SUCCESS);
        // rb.Push<u32>(0x100);
        UNIMPLEMENTED();
    }

    void Unknown1(Kernel::HLERequestContext& ctx) {
        ctx.DumpIPC();
        IPC::RequestParser rp{ctx};
        for (int i = 0; i < 32; i++)
            printf("%lx\n", rp.Pop<u64>());
        IPC::RequestBuilder rb{ctx, 1};
        rb.Push(RESULT_SUCCESS);
        // rb.Push<u32>(0x100);
    }
};

} // namespace Nvidia
} // namespace Service
