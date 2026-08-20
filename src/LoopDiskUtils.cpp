#include "LoopDiskUtils.hpp"
#include <cstdio>
#include <fcntl.h>


constexpr unsigned int LOOP_MAJOR = 7;
bool LoopDiskUtils::is_loop_device(const std::string& device_name) {
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
    std::vector<std::string> loop_devices;
    const std::filesystem::path block_devices("/sys/block");

    for (const auto& block_device_directory : std::filesystem::directory_iterator(block_devices)) {
        const std::string block_device_name = block_device_directory.path().filename();
        if (is_loop_device(block_device_name)) {
            loop_devices.push_back(block_device_name);
        }
    }

    return loop_devices;
}

std::string LoopDiskUtils::make_loop_device(int mb, const std::string& image_directory) {
    if (mb > 128000) {
        throw LoopDiskUtilsException("limit set to 128000 mb. More than that is likely a mistake when testing.");
    }

    const std::string make_empty_image_cmd = std::format("dd if=/dev/zero of={}/disk.img bs=1M count={}", image_directory, mb);
    int dd_result = std::system(make_empty_image_cmd.c_str());
    if (dd_result != 0) {
        throw LoopDiskUtilsException(std::format("dd command exited with code {}", dd_result));
    }

    const std::string losetup_cmd = std::format("sudo losetup -f {}/disk.img --show", image_directory);
    FILE* pipe = popen(losetup_cmd.c_str(), O_RDONLY);
    if (!pipe) {
        throw LoopDiskUtilsException("popen failed to run losetup.");
    }

    std::array<char, 128> buffer;
    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    int losetup_exit_code = pclose(pipe);
    if (losetup_exit_code != 0) {
        throw LoopDiskUtilsException(std::format("losetup exited with {}", losetup_exit_code));
    }

    return result;
}