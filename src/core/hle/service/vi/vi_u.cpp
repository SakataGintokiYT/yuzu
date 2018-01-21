// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/service/vi/vi.h"
#include "core/hle/service/vi/vi_u.h"

namespace Service {
namespace VI {

void VI_U::GetDisplayService(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service, "(STUBBED) called");

    IPC::RequestBuilder rb{ctx, 2, 0, 0, 1};
    rb.PushIpcInterface<IApplicationDisplayService>(nv_flinger);
}

VI_U::VI_U() : ServiceFramework("vi:u") {
    static const FunctionInfo functions[] = {
        {0, &VI_U::GetDisplayService, "GetDisplayService"},
    };
    RegisterHandlers(functions);
    nv_flinger = std::make_shared<NVFlinger>();
}

} // namespace VI
} // namespace Service
