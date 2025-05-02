#include <chrono>
#include <thread>
#include "../platform.h"
#include "debug_tools.hpp"

using namespace std::chrono_literals;

void bbcf_im::debug_tools::wait_for_debugger()
{
#ifdef _DEBUG
    // This function should only do something when we have a debug build.
    // Release builds SHOULD NOT include this logic.
    while (!IsDebuggerPresent())
    {
        std::this_thread::sleep_for(100ms);
    }
#endif
}
