#pragma once

#include <filesystem>
#include <string>
#include <fstream>

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

public:
    BlockDevice(std::string identifier);

    std::string get_identifier() const;

    std::filesystem::path get_dev_path() const;

    std::filesystem::path get_sys_path() const;

    unsigned long long size();
};