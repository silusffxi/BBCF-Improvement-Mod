#pragma once

namespace bbcf_im
{
    /**
    *@brief Provides tools to assist with debugging.
    */
    class debug_tools
    {
    public:
        static void wait_for_debugger();
    };
}

#if defined(_DEBUG) && 0
#define BBCF_IM_DEBUG_WAIT_FOR_DEBUGGER() bbcf_im::debug_tools::wait_for_debugger()
#else
#define BBCF_IM_DEBUG_WAIT_FOR_DEBUGGER()
#endif