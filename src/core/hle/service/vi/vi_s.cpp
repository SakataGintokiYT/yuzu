// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/service/vi/vi.h"
#include "core/hle/service/vi/vi_s.h"

namespace Service {
namespace VI {

void VI_S::GetDisplayService(Kernel::HLERequestContext &ctx) {
  LOG_WARNING(Service, "(STUBBED) called");

  IPC::RequestBuilder rb{ctx, 2, 0, 0, 1};
  rb.PushIpcInterface<IApplicationDisplayService>(nv_flinger);
}

VI_S::VI_S() : ServiceFramework("vi:s") {
  static const FunctionInfo functions[] = {
      {2, &VI_S::GetDisplayService, "GetDisplayService"},
      {3, nullptr, "GetDisplayServiceWithProxyNameExchange"},
  };
  RegisterHandlers(functions);
  nv_flinger = std::make_shared<NVFlinger>();
}

} // namespace VI
} // namespace Service
