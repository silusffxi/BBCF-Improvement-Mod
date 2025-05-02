#include <cstdio>
#include <string>
#include <sstream>
#include "../logger.h"
#include "../D3D9EXWrapper/d3d9.h"
#include "d3d_logger.h"

namespace
{
    std::string d3d_format_name(const D3DFORMAT format)
    {
        switch (format)
        {
        case D3DFMT_UNKNOWN:
            return "D3DFMT_UNKNOWN";
        case D3DFMT_R8G8B8:
            return "D3DFMT_R8G8B8";
        case D3DFMT_A8R8G8B8:
            return "D3DFMT_A8R8G8B8";
        case D3DFMT_X8R8G8B8:
            return "D3DFMT_X8R8G8B8";
        case D3DFMT_R5G6B5:
            return "D3DFMT_R5G6B5";
        case D3DFMT_X1R5G5B5:
            return "D3DFMT_X1R5G5B5";
        case D3DFMT_A1R5G5B5:
            return "D3DFMT_A1R5G5B5";
        case D3DFMT_A4R4G4B4:
            return "D3DFMT_A4R4G4B4";
        case D3DFMT_R3G3B2:
            return "D3DFMT_R3G3B2";
        case D3DFMT_A8:
            return "D3DFMT_A8";
        case D3DFMT_A8R3G3B2:
            return "D3DFMT_A8R3G3B2";
        case D3DFMT_X4R4G4B4:
            return "D3DFMT_X4R4G4B4";
        case D3DFMT_A2B10G10R10:
            return "D3DFMT_A2B10G10R10";
        case D3DFMT_A8B8G8R8:
            return "D3DFMT_A8B8G8R8";
        case D3DFMT_X8B8G8R8:
            return "D3DFMT_X8B8G8R8";
        case D3DFMT_G16R16:
            return "D3DFMT_G16R16";
        case D3DFMT_A2R10G10B10:
            return "D3DFMT_A2R10G10B10";
        case D3DFMT_A16B16G16R16:
            return "D3DFMT_A16B16G16R16";
        case D3DFMT_A8P8:
            return "D3DFMT_A8P8";
        case D3DFMT_P8:
            return "D3DFMT_P8";
        case D3DFMT_L8:
            return "D3DFMT_L8";
        case D3DFMT_A8L8:
            return "D3DFMT_A8L8";
        case D3DFMT_A4L4:
            return "D3DFMT_A4L4";
        case D3DFMT_V8U8:
            return "D3DFMT_V8U8";
        case D3DFMT_L6V5U5:
            return "D3DFMT_L6V5U5";
        case D3DFMT_X8L8V8U8:
            return "D3DFMT_X8L8V8U8";
        case D3DFMT_Q8W8V8U8:
            return "D3DFMT_Q8W8V8U8";
        case D3DFMT_V16U16:
            return "D3DFMT_V16U16";
        case D3DFMT_A2W10V10U10:
            return "D3DFMT_A2W10V10U10";
        case D3DFMT_UYVY:
            return "D3DFMT_UYVY";
        case D3DFMT_R8G8_B8G8:
            return "D3DFMT_R8G8_B8G8";
        case D3DFMT_YUY2:
            return "D3DFMT_YUY2";
        case D3DFMT_G8R8_G8B8:
            return "D3DFMT_G8R8_G8B8";
        case D3DFMT_DXT1:
            return "D3DFMT_DXT1";
        case D3DFMT_DXT2:
            return "D3DFMT_DXT2";
        case D3DFMT_DXT3:
            return "D3DFMT_DXT3";
        case D3DFMT_DXT4:
            return "D3DFMT_DXT4";
        case D3DFMT_DXT5:
            return "D3DFMT_DXT5";
        case D3DFMT_D16_LOCKABLE:
            return "D3DFMT_D16_LOCKABLE";
        case D3DFMT_D32:
            return "D3DFMT_D32";
        case D3DFMT_D15S1:
            return "D3DFMT_D15S1";
        case D3DFMT_D24S8:
            return "D3DFMT_D24S8";
        case D3DFMT_D24X8:
            return "D3DFMT_D24X8";
        case D3DFMT_D24X4S4:
            return "D3DFMT_D24X4S4";
        case D3DFMT_D16:
            return "D3DFMT_D16";

        case D3DFMT_D32F_LOCKABLE:
            return "D3DFMT_D32F_LOCKABLE";
        case D3DFMT_D24FS8:
            return "D3DFMT_D24FS8";

#if !defined(D3D_DISABLE_9EX)

        case D3DFMT_D32_LOCKABLE:
            return "D3DFMT_D32_LOCKABLE";
        case D3DFMT_S8_LOCKABLE:
            return "D3DFMT_S8_LOCKABLE";

#endif

        case D3DFMT_L16:
            return "D3DFMT_L16";
        case D3DFMT_VERTEXDATA:
            return "D3DFMT_VERTEXDATA";
        case D3DFMT_INDEX16:
            return "D3DFMT_INDEX16";
        case D3DFMT_INDEX32:
            return "D3DFMT_INDEX32";
        case D3DFMT_Q16W16V16U16:
            return "D3DFMT_Q16W16V16U16";
        case D3DFMT_MULTI2_ARGB8:
            return "D3DFMT_MULTI2_ARGB8";
        case D3DFMT_R16F:
            return "D3DFMT_R16F";
        case D3DFMT_G16R16F:
            return "D3DFMT_G16R16F";
        case D3DFMT_A16B16G16R16F:
            return "D3DFMT_A16B16G16R16F";
        case D3DFMT_R32F:
            return "D3DFMT_R32F";
        case D3DFMT_G32R32F:
            return "D3DFMT_G32R32F";
        case D3DFMT_A32B32G32R32F:
            return "D3DFMT_A32B32G32R32F";
        case D3DFMT_CxV8U8:
            return "D3DFMT_CxV8U8";

#if !defined(D3D_DISABLE_9EX)

        case D3DFMT_A1:
            return "D3DFMT_A1";
        case D3DFMT_A2B10G10R10_XR_BIAS:
            return "D3DFMT_A2B10G10R10_XR_BIAS";
        case D3DFMT_BINARYBUFFER:
            return "D3DFMT_BINARYBUFFER";

#endif

        case D3DFMT_FORCE_DWORD:
        default: // NOLINT(clang-diagnostic-covered-switch-default)
            return "<Unknown>";
        }
    }

    std::string multi_sample_name(const D3DMULTISAMPLE_TYPE type)
    {
        switch (type)
        {
        case D3DMULTISAMPLE_NONE:
            return "D3DMULTISAMPLE_NONE";
        case D3DMULTISAMPLE_NONMASKABLE:
            return "D3DMULTISAMPLE_NONMASKABLE";
        case D3DMULTISAMPLE_2_SAMPLES:
            return "D3DMULTISAMPLE_2_SAMPLES";
        case D3DMULTISAMPLE_3_SAMPLES:
            return "D3DMULTISAMPLE_3_SAMPLES";
        case D3DMULTISAMPLE_4_SAMPLES:
            return "D3DMULTISAMPLE_4_SAMPLES";
        case D3DMULTISAMPLE_5_SAMPLES:
            return "D3DMULTISAMPLE_5_SAMPLES";
        case D3DMULTISAMPLE_6_SAMPLES:
            return "D3DMULTISAMPLE_6_SAMPLES";
        case D3DMULTISAMPLE_7_SAMPLES:
            return "D3DMULTISAMPLE_7_SAMPLES";
        case D3DMULTISAMPLE_8_SAMPLES:
            return "D3DMULTISAMPLE_8_SAMPLES";
        case D3DMULTISAMPLE_9_SAMPLES:
            return "D3DMULTISAMPLE_9_SAMPLES";
        case D3DMULTISAMPLE_10_SAMPLES:
            return "D3DMULTISAMPLE_10_SAMPLES";
        case D3DMULTISAMPLE_11_SAMPLES:
            return "D3DMULTISAMPLE_11_SAMPLES";
        case D3DMULTISAMPLE_12_SAMPLES:
            return "D3DMULTISAMPLE_12_SAMPLES";
        case D3DMULTISAMPLE_13_SAMPLES:
            return "D3DMULTISAMPLE_13_SAMPLES";
        case D3DMULTISAMPLE_14_SAMPLES:
            return "D3DMULTISAMPLE_14_SAMPLES";
        case D3DMULTISAMPLE_15_SAMPLES:
            return "D3DMULTISAMPLE_15_SAMPLES";
        case D3DMULTISAMPLE_16_SAMPLES:
            return "D3DMULTISAMPLE_16_SAMPLES";
        case D3DMULTISAMPLE_FORCE_DWORD:
        default: // NOLINT(clang-diagnostic-covered-switch-default)
            return "<Unknown>";
        }
    }

    std::string swap_effect_name(const D3DSWAPEFFECT effect)
    {
        switch (effect)
        {
        case D3DSWAPEFFECT_DISCARD:
            return "D3DSWAPEFFECT_DISCARD";
        case D3DSWAPEFFECT_FLIP:
            return "D3DSWAPEFFECT_FLIP";
        case D3DSWAPEFFECT_COPY:
            return "D3DSWAPEFFECT_COPY";
#if !defined(D3D_DISABLE_9EX)
        case D3DSWAPEFFECT_OVERLAY:
            return "D3DSWAPEFFECT_OVERLAY";
        case D3DSWAPEFFECT_FLIPEX:
            return "D3DSWAPEFFECT_FLIPEX";
#endif
        case D3DSWAPEFFECT_FORCE_DWORD:
        default: // NOLINT(clang-diagnostic-covered-switch-default)
            return "<Unknown>";
        }
    }
}

void bbcf_im_log_d3d_params(const D3DPRESENT_PARAMETERS* present_params, const bool original_settings)
{
    LOG(1, "%s", original_settings
        ? "Original D3D presentation parameters:\n"
        : "Modified D3D presentation parameters:\n")

    std::stringstream output;
    output
        << "    - BackBufferWidth           : " << present_params->BackBufferWidth << '\n'
        << "    - BackBufferHeight          : " << present_params->BackBufferHeight << '\n'
        << "    - BackBufferFormat          : " << d3d_format_name(present_params->BackBufferFormat) << '\n'
        << "    - BackBufferCount           : " << present_params->BackBufferCount << '\n'
        << "    - SwapEffect                : " << swap_effect_name(present_params->SwapEffect) << '\n'
        << "    - MultiSampleType           : " << multi_sample_name(present_params->MultiSampleType) << '\n'
        << "    - MultiSampleQuality        : " << present_params->MultiSampleQuality << '\n'
        << "    - EnableAutoDepthStencil    : " << (present_params->EnableAutoDepthStencil ? "true" : "false") << '\n'
        << "    - FullScreen_RefreshRateInHz: " << present_params->FullScreen_RefreshRateInHz;
    LOG(1, "%s", output.str().c_str())

    // TODO: Fix how strings are logged and formatted here since C++17 doesn't have std::format.
    LOG(1, "    - Windowed                  : %s", (present_params->Windowed ? "true" : "false"))
    LOG(1, "    - Flags                     : 0x%p", present_params->Flags)
    LOG(1, "    - PresentationInterval      : 0x%p", present_params->PresentationInterval)
    LOG(1, "%c", '\n')
}

/*
void logD3DPParams(D3DPRESENT_PARAMETERS* pPresentationParameters, bool isOriginalSettings)
{
    if (isOriginalSettings)
    {
        LOG(1, "Original D3D PresentationParameters:\n");
    }
    else
    {
        LOG(1, "Modified D3D PresentationParameters:\n");
    }

    LOG(1, "\t- BackBufferWidth: %u\n", pPresentationParameters->BackBufferWidth);
    LOG(1, "\t- BackBufferHeight: %u\n", pPresentationParameters->BackBufferHeight);
    LOG(1, "\t- BackBufferFormat: %u\n", pPresentationParameters->BackBufferFormat);
    LOG(1, "\t- BackBufferCount: %u\n", pPresentationParameters->BackBufferCount);
    LOG(1, "\t- SwapEffect: %u\n", pPresentationParameters->SwapEffect);
    LOG(1, "\t- MultiSampleType: %u\n", pPresentationParameters->MultiSampleType);
    LOG(1, "\t- MultiSampleQuality: %d\n", pPresentationParameters->MultiSampleQuality);
    LOG(1, "\t- EnableAutoDepthStencil: %d\n", pPresentationParameters->EnableAutoDepthStencil);
    LOG(1, "\t- FullScreen_RefreshRateInHz: %u\n", pPresentationParameters->FullScreen_RefreshRateInHz);
    LOG(1, "\t- hDeviceWindow: 0x%p\n", pPresentationParameters->hDeviceWindow);
    LOG(1, "\t- Windowed: %d\n", pPresentationParameters->Windowed);
    LOG(1, "\t- Flags: 0x%p\n", pPresentationParameters->Flags);
    LOG(1, "\t- PresentationInterval: 0x%p\n", pPresentationParameters->PresentationInterval);
}
*/