#include "version.hpp"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

namespace
{

TEST(VersionTest, ProjectPatchVersionShouldGreaterNullWhenRequired)
{
    // Act
    const auto patch_version = version::GetProjPatchVersion();

    // Assert
    EXPECT_THAT(patch_version, testing::Gt(0U));
}

}  // namespace