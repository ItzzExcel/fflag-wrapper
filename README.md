# fflag-wrapper

**Greetings to Bitdancer and the entire team behind Hyperion for planning the removal and the manual setting of FFlags, which will make it impossible for many people with low-end computers to play Roblox. 😹**

A quite simple Wrapper for Fast Flags.\
Compatible with Bloxstrap, automatically calculates the game directories.

The header does not follow best practices, you are absolutely right if you don't like my code.

## Requirements

-   [nlohmann/json](https://github.com/nlohmann/json)
    -   You can install this with vcpkg if you're using a Visual Studio enviroment.
-   C++14 or higher.
    -   You'll need this to use the filesystem library.

## Usage

> [!TIP]
> Better documentation could be written in [this line of the header](https://github.com/ItzzExcel/fflag-wrapper/blob/main/src/fflags.hpp#L14).

```cpp
#include "fflags.hpp"

int main(int argc, char const *argv[])
{
    // Change if Bloxstrap is allowed.
    fflags::ALLOW_BLOXSTRAP = <bool>;

    // Read a value from ClientAppSettings.json
    std::string value = fflags::Read("DFIntTaskSchedulerTargetFps");
    printf("The value of DFIntTaskSchedulerTargetFps is %s", value.c_str());

    // Write a value in ClientAppSettings.json
    std::string fps_cap = "999";
    if (fflags::Write("DFIntTaskSchedulerTargetFps", fps_cap)) {
        printf("DFIntTaskSchedulerTargetFps set to %s", fps_cap.c_str());
    }

    // Delete a value from ClientAppSettings.json
    if (fflags::Delete("DFIntTaskSchedulerTargetFps")) {
        printf("DFIntTaskSchedulerTargetFps deleted from ClientAppSettings.json");
    }

    return 0;
}

```

<hr/>

If you use this, please give a little credit in your project.\
— Made with love by Excel. <3
