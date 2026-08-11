#include "BlockDevice.hpp"
#include "BlockDeviceManager.hpp"
#include "LoopDiskUtils.hpp"
#include <iostream>



int main() {
    BlockDeviceManager block_device_manager;

    std::vector<std::string> device_ids = LoopDiskUtils::get_active_loop_devices();

    for (const auto& s : device_ids) {
        std::cout << s << std::endl;
    }

    return 0;
}