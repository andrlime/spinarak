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

public:
    CLI(int argc, char** argv);

    auto print_usage() -> void;

    inline auto
    get_file_names() -> std::pair<std::string, std::string>
    {
        return std::make_pair(bios_file_name_, rom_file_name_);
    }
};

} // namespace cli
} // namespace spinarak
