#pragma once
#include "../platform.h"

LONG WINAPI unhandled_exception_filter(PEXCEPTION_POINTERS ex_info);

namespace bbcf_im
{
    class crash_handler
    {
    public:
        static LONG write_crash_dump(PEXCEPTION_POINTERS ex_info);
    };
}
