# pragma once

#include <string>
#include <vector>
#include "ProcessRunner.hpp"
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/sysmacros.h>

class LoopDiskUtils {
public:
    static std::vector<std::string> get_active_loop_devices();
    static std::string make_loop_device(std::string filename, int mb);
private:
    static bool is_loop_device(const std::string& device_name);
};