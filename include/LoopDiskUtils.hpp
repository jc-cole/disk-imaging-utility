# pragma once

#include <string>
#include <vector>
#include "ProcessRunner.hpp"

class LoopDiskUtils {
public:
    static std::vector<std::string> get_active_loop_devices();
};