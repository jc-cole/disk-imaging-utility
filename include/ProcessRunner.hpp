#pragma once

#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>


class ProcessRunner {
public:
    static std::string exec(const std::string& cmd);
};