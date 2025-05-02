#pragma once
#include <cstdint>
#include <string>

/**
*@brief Returns the base address for @c BBCF.exe
*@returns The base address of @c BBCF.exe otherwise @c nullptr will be returned if it cannot be located.
*/
char* bbcf_im_get_bbcf_base_address();

#if defined(__cplusplus)
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

        /**
        *@brief Returns the memory at the pointer as a string.
        *@param src The pointer to the memory segment to convert.
        *@param length The size of the memory region
        */
        static std::string raw_memory_to_string(const uint8_t* src, size_t length);
    };
}
#endif
