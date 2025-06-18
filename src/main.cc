#include <cli/cli.hpp>
#include <emulator/emulator.hpp>

auto
main(int argc, char** argv) -> int
{
    auto cli = spinarak::cli::CLI(argc, argv); // TODO: make singleton
    auto emulator = spinarak::emulator::Emulator(cli.get_file_names());
    return 0;
}
