# fflag-wrapper
A quite simple Wrapper for Fast Flags.\
Compatible with Bloxstrap, automatically calculates the game directories.

The header does not follow best practices, you are absolutely right if you don't like my code.

## Requirements
- [nlohmann/json](https://github.com/nlohmann/json)
  - You can install this with vcpkg if you're using a Visual Studio enviroment.
- C++14 or higher.
  - You'll need this to use the filesystem library.

## Usage

```cpp
#include "fflags.hpp"

int main(int argc, char const *argv[])
{
    // Read a value from ClientAppSettings.json
    std::string value = FFlags::Read("DFIntTaskSchedulerTargetFps");
    printf("The value of DFIntTaskSchedulerTargetFps is %s", value.c_str());

    // Write a value in ClientAppSettings.json
    std::string fps_cap = "999";
    if (FFlags::Write("DFIntTaskSchedulerTargetFps", fps_cap)) {
        printf("DFIntTaskSchedulerTargetFps set to %s", fps_cap.c_str());
    }

    // Delete a value from ClientAppSettings.json
    if (FFlags::Delete("DFIntTaskSchedulerTargetFps")) {
        printf("DFIntTaskSchedulerTargetFps deleted from ClientAppSettings.json");
    }

    // Change if Bloxstrap is allowed.
    FFlags::ALLOW_BLOXSTRAP = <bool>;

    return 0;
}

```
<hr/>

If you use this, please give a little credit in your project.\
— Made with love by Excel. <3
