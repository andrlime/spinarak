#include <example/hello_world.h>

namespace spinarak {
namespace example {

void
print_hello_world()
{
    std::cout << spinarak::globals::name << "\n";
}

} // namespace globals
} // namespace spinarak
