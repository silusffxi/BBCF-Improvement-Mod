#pragma once

namespace bbcf_im
{
    /**
    *@brief Tools to assist with reading and writing memory.
    */
    class memory_tools
    {
    public:
        /**
        *@brief Returns the base address for @c BBCF.exe
        *@returns The base address of @c BBCF.exe otherwise @c nullptr will be returned if it cannot be located.
        */
        static char* get_bbcf_base_address();
    };
}
