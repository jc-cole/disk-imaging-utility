#include "ProcessRunner.hpp"



std::string ProcessRunner::exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    
    // Open the pipe in read mode
    // Using custom deleter to automatically call pclose() when exiting scope
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("popen() failed");
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}
