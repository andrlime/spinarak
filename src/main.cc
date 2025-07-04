#include <cli/cli.hpp>
#include <emulator/emulator.hpp>

using spinarak::cli::CLI;

auto
main(int argc, char** argv) -> int
{
    auto emulator = spinarak::emulator::Emulator(CLI(argc, argv).get_file_names());

    emulator.run();

    // TODO: draw stuff
    // TODO: timer
    // TODO: larger ROMs

    return 0;
}
