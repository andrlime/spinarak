#include <memory/memory.hpp>

int
main()
{
    spinarak::memory::Memory("../roms/dmg_boot.bin", "../roms/hello.gb");
    return 0;
}
