#include "LoopDiskUtils.hpp"
#include "ProcessRunner.hpp"

constexpr unsigned int LOOP_MAJOR = 7;
bool is_loop_device(const std::string& device_name) {
    std::string path = "/dev/" + device_name;
    
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        return false; 
    }

    if (!S_ISBLK(st.st_mode)) {
        return false;
    }

    return gnu_dev_major(st.st_rdev) == LOOP_MAJOR;
}


std::vector<std::string> LoopDiskUtils::get_active_loop_devices() {
    std::string raw_output = ProcessRunner::exec("losetup -l");
    std::vector<std::string> tokens;
    std::stringstream ss(raw_output);

    std::string token;
    while (std::getline(ss, token)) {
        tokens.push_back(token);
    }

    return tokens;
}

// std::string LoopDiskUtils::make_loop_device(std::string filename, int mb) {

// }