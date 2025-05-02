#include <cstdint>
#include <filesystem>
#include "platform.h"
#include "globals.hpp"

using namespace bbcf_im;

char* globals::bbcf_base_address = nullptr;

std::filesystem::path globals::bbcf_im_dir = L"";

std::filesystem::path globals::host_process_dir = L"";
std::filesystem::path globals::host_process_path = L"";

uint32_t globals::host_process_id = 0u;

std::filesystem::path globals::module_dir = L"";
std::filesystem::path globals::module_path = L"";

HMODULE globals::instance_module = nullptr;
