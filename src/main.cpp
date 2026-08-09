#include "BlockDevice.hpp"
#include "BlockDeviceManager.hpp"
#include <iostream>

int main() {
    BlockDeviceManager block_device_manager;

    std::vector<BlockDevice> block_devices = block_device_manager.get_block_devices();

    for (const auto& device : block_devices) {
        std::cout << device.get_identifier();
    }

    return 0;
}