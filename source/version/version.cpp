#include "version.hpp"

#include "config.hpp"

namespace version
{

uint32_t GetProjPatchVersion() noexcept { return PROJECT_VERSION_PATCH; }

}  // namespace version
