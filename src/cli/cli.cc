#include <cli/cli.hpp>

namespace spinarak {
namespace cli {

#define seq(s1, s2) strcmp((s1), (s2)) == 0

CLI::CLI(int argc, char** argv)
{
    if (argc == 2 && (seq(argv[1], "--help") || seq(argv[1], "-h"))) {
        print_usage();
    }

    if (argc != 3) {
        std::cout << "expected three arguments, run with --help for usage" << "\n";
        exit(0);
    }

    bios_file_name_ = argv[1];
    rom_file_name_ = argv[2];
}

void
CLI::print_usage()
{
    std::cout << "Usage:" << "\n";
    std::cout << "\tspinarak <bios_file_name> <rom_file_name>" << "\n";
    std::cout << "\t\tbios_file_name:\tpath to the GameBoy BIOS" << "\n";
    std::cout << "\t\trom_file_name:\tpath to the GameBoy ROM to run" << "\n";
    std::cout << "\tspinarak --help" << "\n";
    std::cout << "\t\tprints this help message" << "\n";
    exit(0);
}

} // namespace cli
} // namespace spinarak
