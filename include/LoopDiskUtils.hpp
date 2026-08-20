# pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <filesystem>
#include <cstdlib>
#include <format>
#include <map>
#include <stdio.h>

class LoopDiskUtilsException : public std::exception {
private:
    std::string message;
public:
    LoopDiskUtilsException(std::string msg) : message(std::move(msg)) {}
    
    // noexcept ensures the what() function itself won't throw errors
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class LoopDiskUtils {
public:
    static std::vector<std::string> get_active_loop_devices();
    static std::string make_loop_device(int mb, const std::string& image_directory);
    static bool is_loop_device(const std::string& device_name);
};