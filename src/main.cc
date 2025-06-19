#include <cli/cli.hpp>
#include <emulator/emulator.hpp>

using spinarak::cli::CLI;

auto
app_init(int argc, char** argv) -> void
{
    CLI(argc, argv);
}

auto
main(int argc, char** argv) -> int
{
    app_init(argc, argv);
    auto emulator = spinarak::emulator::Emulator(CLI::get_instance()->get_file_names());

    // Go instruction by instruction

    // TODO: draw stuff
    // TODO: timer
    // TODO: larger ROMs

    return 0;
}
