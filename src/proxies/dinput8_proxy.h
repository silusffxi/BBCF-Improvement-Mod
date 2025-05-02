#pragma once
#include "../platform.h"

/**
*@brief Typed function pointer for @c DirectInput8Create.
*/
typedef HRESULT(WINAPI* func_DirectInput8Create)(
    HINSTANCE hInstance,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID* ppvOut,
    LPUNKNOWN pUnkOuter);

#pragma region DirectX Return Codes
//=============================================================================
// DirectX Return Codes
//=============================================================================

/// The operation completed successfully.
#define DI_OK                           S_OK

/// An invalid parameter was passed to the returning function,
/// or the object was not in a state that admitted the function
/// to be called.
#define DIERR_INVALIDPARAM              E_INVALIDARG

/// An undetermined error occured inside the DInput subsystem.
#define DIERR_GENERIC                   E_FAIL

/// The function called is not supported at this time.
#define DIERR_UNSUPPORTED               E_NOTIMPL

/// The DInput subsystem couldn't allocate sufficient memory to complete the
/// caller's request.
#define DIERR_OUTOFMEMORY               E_OUTOFMEMORY

/// The application requires a newer version of DirectInput.
#define DIERR_OLDDIRECTINPUTVERSION     \
    MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_OLD_WIN_VERSION)

/// The application was written for an unsupported prerelease version
/// of DirectInput.
#define DIERR_BETADIRECTINPUTVERSION    \
    MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_RMODE_APP)

#pragma endregion
#if defined(__cplusplus)
#include <atomic>
#include <filesystem>
#include <mutex>

namespace bbcf_im::proxies
{
    class dinput8_proxy
    {
        static std::atomic_bool _dinput8_loaded;
        static std::mutex       _setup_mutex;

    public:
        /**
        *@brief Wrapper around @c DirectInput8Create that should be provided by the real version of dinput8.dll
        *
        * https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ee416756(v=vs.85)
        *
        *@param instance (hInstance) Instance handle to the application or dynamic-link library (DLL) that is creating the DirectInput object.
        *@param version (dwVersion) Version number of DirectInput for which the application is designed.
        *@param unique_id (riidltf) Unique identifier of the desired interface.
        *@param receiver (ppvOut) Address of a pointer to a variable to receive the interface pointer if the call succeeds.
        *@param pUnkOuter Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or NULL if the interface is not aggregated.
        *@return If the function succeeds, the return value is DI_OK. If the function fails, the return value can be one of the following error values: DIERR_BETADIRECTINPUTVERSION, DIERR_INVALIDPARAM, DIERR_OLDDIRECTINPUTVERSION, DIERR_OUTOFMEMORY.
        */
        static HRESULT create(HINSTANCE instance, DWORD version, REFIID unique_id, LPVOID* receiver, LPUNKNOWN pUnkOuter);

        /**
        *@brief Setup and configure the proxy for dinput8.
        *@param dinput8_path Allows another wrapper for dinput8 to be specified and used instead of the one provided by the system.
        */
        static bool setup(const std::filesystem::path& dinput8_path = L"");

        /**
        *@brief Releases the dinput8 proxy and disables the proxy function.
        */
        static bool shutdown();

    private:
        /**
        *@brief Returns the path to @c dinput8.dll determined by the system.
        */
        static std::filesystem::path get_module_path();
    };
}
#endif