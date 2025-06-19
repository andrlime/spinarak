#pragma once

#include <globals.hpp>
#include <string.h>
#include <types.hpp>

#include <iostream>

namespace spinarak {
namespace cli {

class CLI {
private:
    std::string bios_file_name_;
    std::string rom_file_name_;

    static CLI* instance_;

public:
    CLI(int argc, char** argv);

    static inline auto
    get_instance() -> CLI*
    {
        if (instance_ == nullptr) {
            std::cerr << "CLI not initialized, cannot get_instance()" << "\n";
            std::exit(1);
        }
        return instance_;
    }

    auto print_usage() -> void;

    inline auto
    get_file_names() -> std::pair<std::string, std::string>
    {
        return std::make_pair(bios_file_name_, rom_file_name_);
    }
};

} // namespace cli
} // namespace spinarak
