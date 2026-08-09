#include "BlockDeviceManager.hpp"

std::vector<BlockDevice> BlockDeviceManager::get_block_devices() {
    std::vector<BlockDevice> block_devices;
    if (!std::filesystem::exists(block_devices_path)) {
        throw BlockDeviceManagerExcepton("block device path not found.");
    }
    for (const auto& entry : std::filesystem::directory_iterator(block_devices_path)) {
        BlockDevice block_device(entry.path().filename().string());
        block_devices.push_back(block_device);
    }
    return block_devices;
}