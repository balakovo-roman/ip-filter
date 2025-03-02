#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "version.hpp"

namespace  {

TEST(VersionTest, ProjectPatchVersionShouldGreaterNullWhenRequired)
{
    // Act
    const auto patch_version = version::GetProjPatchVersion();

    // Assert
    EXPECT_THAT(patch_version, testing::Gt(0U));
}

}