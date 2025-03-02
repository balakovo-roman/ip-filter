#include "version.hpp"

#include "config.h"

namespace version {

uint32_t GetProjPatchVersion() noexcept
{
    return PROJECT_VERSION_PATCH;
}

}
