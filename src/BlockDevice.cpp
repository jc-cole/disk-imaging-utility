#include "BlockDevice.hpp"

BlockDevice::BlockDevice(std::string device_identifier) : identifier(device_identifier) {}

std::string BlockDevice::get_identifier() const {
    return identifier;
}

std::filesystem::path BlockDevice::get_dev_path() const {
    return std::filesystem::path("/dev").append(identifier);
}

std::filesystem::path BlockDevice::get_sys_path() const {
    return std::filesystem::path("/sys/block").append(identifier);
}

unsigned long long BlockDevice::size() {
    unsigned long long sectors = 0;
    unsigned long long sector_size = 512; 

    std::filesystem::path sys_path = get_sys_path();
    if (!std::filesystem::exists(sys_path)) {
        throw BlockDeviceExcepton("block device not found in /sys/block.");
    }

    // possible race condition if device removed after check
    std::filesystem::path size_path = sys_path.append("/size");
    if (!std::filesystem::exists(sys_path)) {
        throw BlockDeviceExcepton("block device size file not found in /sys/block/" + identifier + ".");
    }
    std::ifstream size_file(size_path);
    if (size_file.is_open() && size_file >> sectors) {
        return sectors * sector_size;
    } else {
        throw BlockDeviceExcepton("block device size file failed to open.");
    }
}
