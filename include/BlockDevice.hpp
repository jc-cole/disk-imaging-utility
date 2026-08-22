#pragma once

#include "PartitionTable.hpp"

#include <filesystem>
#include <string>
#include <optional>
#include <fstream>
#include <vector>

class BlockDeviceExcepton : public std::exception {
private:
    std::string message;
public:
    BlockDeviceExcepton(std::string msg) : message(std::move(msg)) {}
    
    // noexcept ensures the what() function itself won't throw errors
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class BlockDevice {
private:
    std::string identifier;

    uint64_t sizeBytes;

    uint32_t logicalSectorSize;
    uint32_t physicalSectorSize;

    PartitionTableType partitionTable;
    std::optional<std::string> diskId;

    std::vector<Partition> partitions;

public:
    BlockDevice(std::string identifier);

    std::string get_identifier() const;

    std::filesystem::path get_dev_path() const;

    std::filesystem::path get_sys_path() const;

    unsigned long long size();
};