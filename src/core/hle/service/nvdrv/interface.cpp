// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/kernel/event.h"
#include "core/hle/service/nvdrv/interface.h"
#include "core/hle/service/nvdrv/nvdrv.h"

namespace Service {
namespace Nvidia {

void NVDRV::Open(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service, "(STUBBED) called");

    auto buffer = ctx.BufferDescriptorA()[0];

    std::string device_name = Memory::ReadCString(buffer.Address(), buffer.Size());

    u32 fd = nvdrv->Open(device_name);
    IPC::RequestBuilder rb{ctx, 4};
    rb.Push(RESULT_SUCCESS);
    rb.Push<u32>(fd);
    rb.Push<u32>(0);
}

void NVDRV::Ioctl(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service, "(STUBBED) called");

    for (int i = 0; i < 0x80 / 4; i++) {
        if (i % (16 / 4) == 0)
            printf("\n");
        u32_le buf = ctx.CommandBuffer()[i];
        u8 a = (buf >> 24) & 0xFF;
        u8 b = (buf >> 16) & 0xFF;
        u8 c = (buf >> 8) & 0xFF;
        u8 d = buf & 0xFF;
        printf("%02x %02x %02x %02x ", d, c, b, a);
    }
    printf("\n");

    IPC::RequestParser rp{ctx};
    u32 fd = rp.Pop<u32>();
    u32 command = rp.Pop<u32>();

    ctx.DumpInfo();
    u32 nv_result = 0x0;

    if (ctx.BufferDescriptorA()[0].Size() != 0) {
        auto input_buffer = ctx.BufferDescriptorA()[0];
        auto output_buffer = ctx.BufferDescriptorB()[0];
        std::vector<u8> input(input_buffer.Size());
        std::vector<u8> output(output_buffer.Size());
        Memory::ReadBlock(input_buffer.Address(), input.data(), input_buffer.Size());
        nv_result = nvdrv->Ioctl(fd, command, input, output);
        Memory::WriteBlock(output_buffer.Address(), output.data(), output_buffer.Size());
    } else {
        auto input_buffer = ctx.BufferDescriptorX()[0];
        auto output_buffer = ctx.BufferDescriptorC()[0];
        std::vector<u8> input(input_buffer.size);
        std::vector<u8> output(output_buffer.size);
        Memory::ReadBlock(input_buffer.Address(), input.data(), input_buffer.size);
        nv_result = nvdrv->Ioctl(fd, command, input, output);
        Memory::WriteBlock(output_buffer.Address(), output.data(), output_buffer.size);
    }

    IPC::RequestBuilder rb{ctx, 3};
    rb.Push(RESULT_SUCCESS);
    rb.Push(nv_result);
}

void NVDRV::Close(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service, "(STUBBED) called");

    IPC::RequestParser rp{ctx};
    u32 fd = rp.Pop<u32>();

    auto result = nvdrv->Close(fd);

    IPC::RequestBuilder rb{ctx, 2};
    rb.Push(result);
}

void NVDRV::Initialize(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service, "(STUBBED) called");
    IPC::RequestBuilder rb{ctx, 3};
    rb.Push(RESULT_SUCCESS);
    rb.Push<u32>(0);
}

void NVDRV::SetClientPID(Kernel::HLERequestContext& ctx) {
    IPC::RequestParser rp{ctx};
    u64 pid = rp.Pop<u64>();
    PID = pid;

    LOG_WARNING(Service, "(STUBBED) called, pid=%lx", pid);
    IPC::RequestBuilder rb{ctx, 3};
    rb.Push(RESULT_SUCCESS);
    rb.Push<u32>(0);
}

void NVDRV::FinishInitialize(Kernel::HLERequestContext& ctx) {
    IPC::RequestBuilder rb{ctx, 2};
    rb.Push(RESULT_SUCCESS);
}

void NVDRV::QueryEvent(Kernel::HLERequestContext& ctx) {
    IPC::RequestParser rp{ctx};
    u32 fd = rp.Pop<u32>();
    u32 event_id = rp.Pop<u32>();
    LOG_WARNING(Service, "(STUBBED) called, fd=%x, event_id=%x", fd, event_id);

    IPC::RequestBuilder rb{ctx, 2};
    rb.Push(RESULT_SUCCESS);
    auto event = Kernel::Event::Create(Kernel::ResetType::Pulse, "NVEvent");
    event->Signal();
    LOG_WARNING(Service, "Event is %x - %x - %x", event->GetObjectId(), event->GetHandleType(),
                event);
    rb.PushCopyObjects(event);
}

NVDRV::NVDRV(std::shared_ptr<Module> nvdrv, const char* name)
    : ServiceFramework(name), nvdrv(std::move(nvdrv)) {
    static const FunctionInfo functions[] = {
        {0, &NVDRV::Open, "Open"},
        {1, &NVDRV::Ioctl, "Ioctl"},
        {2, &NVDRV::Close, "Close"},
        {3, &NVDRV::Initialize, "Initialize"},
        {4, &NVDRV::QueryEvent, "QueryEvent"},
        {8, &NVDRV::SetClientPID, "SetClientPID"},
        {13, &NVDRV::FinishInitialize, "FinishInitialize"},
    };
    RegisterHandlers(functions);
}

} // namespace Nvidia
} // namespace Service
