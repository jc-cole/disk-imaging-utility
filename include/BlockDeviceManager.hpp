#pragma once

#include "BlockDevice.hpp"
#include <vector>
#include <string>

class BlockDeviceManagerExcepton : public std::exception {
private:
    std::string message;
public:
    BlockDeviceManagerExcepton(std::string msg) : message(std::move(msg)) {}
    
    // noexcept ensures the what() function itself won't throw errors
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BlockDeviceManager {
private:
    const std::filesystem::path block_devices_path = "/sys/block";

public:
    std::vector<BlockDevice> get_block_devices();
};