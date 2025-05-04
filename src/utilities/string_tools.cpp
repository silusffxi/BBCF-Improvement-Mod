#include <ctime>
#include <string>
#include "string_tools.h"

std::string bbcf_im::timestamp_string(const std::string& time_format)
{
    auto format = time_format;
    if (format.empty())
        format = "%Y-%m-%d %H:%M:%S";

    time_t cur_time;
    auto _ = time(&cur_time);

    tm* time_info = localtime(&cur_time);  // NOLINT(concurrency-mt-unsafe)

    auto str = std::string(32, '\0');
    const auto str_size = strftime(str.data(), str.size(), format.c_str(), time_info);
    return str.substr(0, str_size);
}