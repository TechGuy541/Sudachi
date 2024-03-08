// SPDX-FileCopyrightText: 2014 Citra Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <memory>

#include "common/logging/log.h"
#include "common/settings.h"
#include "core/core.h"
#include "core/frontend/emu_window.h"
#include "core/frontend/graphics_context.h"
#include "video_core/host1x/gpu_device_memory_manager.h"
#include "video_core/host1x/host1x.h"
#include "video_core/renderer_base.h"
#include "video_core/renderer_vulkan/renderer_vulkan.h"
#include "video_core/video_core.h"

namespace {

std::unique_ptr<VideoCore::RendererBase> CreateRenderer(
    Core::System& system, Core::Frontend::EmuWindow& emu_window, Tegra::GPU& gpu,
    std::unique_ptr<Core::Frontend::GraphicsContext> context) {
    auto& telemetry_session = system.TelemetrySession();
    auto& device_memory = system.Host1x().MemoryManager();

    return std::make_unique<Vulkan::RendererVulkan>(telemetry_session, emu_window,
                                                    device_memory, gpu, std::move(context));
}

} // Anonymous namespace

namespace VideoCore {

std::unique_ptr<Tegra::GPU> CreateGPU(Core::Frontend::EmuWindow& emu_window, Core::System& system) {
    YuzuSettings::UpdateRescalingInfo();

    const auto nvdec_value = YuzuSettings::values.nvdec_emulation.GetValue();
    const bool use_nvdec = nvdec_value != YuzuSettings::NvdecEmulation::Off;
    const bool use_async = YuzuSettings::values.use_asynchronous_gpu_emulation.GetValue();
    auto gpu = std::make_unique<Tegra::GPU>(system, use_async, use_nvdec);
    auto context = emu_window.CreateSharedContext();
    auto scope = context->Acquire();
    try {
        auto renderer = CreateRenderer(system, emu_window, *gpu, std::move(context));
        gpu->BindRenderer(std::move(renderer));
        return gpu;
    } catch (const std::runtime_error& exception) {
        scope.Cancel();
        LOG_ERROR(HW_GPU, "Failed to initialize GPU: {}", exception.what());
        return nullptr;
    }
}

} // namespace VideoCore
