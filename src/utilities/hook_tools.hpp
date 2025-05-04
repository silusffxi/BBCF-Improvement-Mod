#pragma once
#include <string>
#include "../platform.h"
#include <MinHook.h>

namespace bbcf_im
{
    class hook_tools
    {
    public:
        /**
        *@brief Returns a string representation of an @c MH_STATUS value.
        */
        static std::string mh_status_string(MH_STATUS status);
    };
}