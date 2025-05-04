#pragma once
#if defined(__cplusplus)
#include <string>
namespace bbcf_im
{
    /**
    *@brief Returns the current time as a string using the specified strftime format.
    */
    std::string timestamp_string(const std::string& time_format = "%Y-%m-%d %H:%M:%S");
}
#endif
