#include "LoopDiskUtils.hpp"
#include "ProcessRunner.hpp"

#include <sstream>
#include <unistd.h>
#include <vector>


std::vector<std::string> LoopDiskUtils::get_active_loop_devices() {
    std::string raw_output = ProcessRunner::exec("losetup -a");
    std::vector<std::string> tokens;
    std::stringstream ss(raw_output);

    std::string token;
    while (std::getline(ss, token)) {
        tokens.push_back(token);
    }

    return tokens;
}   