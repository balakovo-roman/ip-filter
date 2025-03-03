#include <iostream>

#include "version/version.hpp"

int main([[maybe_unused]] int arg, [[maybe_unused]] char **args) {
  std::cout << "Version: " << version::GetProjPatchVersion() << std::endl;
  std::cout << "Hello, world!" << std::endl;
}