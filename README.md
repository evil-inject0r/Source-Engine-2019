# Source Engine 2019
Custom Source Engine branch based on Source Engine 2007 currently available on Windows in x86. Forked from [Quiver](https://github.com/quiverteam/Engine).

**Pull this repository with recursive submodules (`git clone --recursive`) to clone get prebuilt shaders**


[![Build Status](https://dev.azure.com/evil-inject0r/source%20engine%202019/_apis/build/status/evil-inject0r.Source-Engine-2019?branchName=master)](https://dev.azure.com/evil-inject0r/source%20engine%202019/_build/latest?definitionId=1&branchName=master)

# Building

## Windows

1. Install [Visual Studio 2019 Community](https://visualstudio.microsoft.com/downloads/), Make sure to go to Individual components and install `C++ MFC for v142 build tools (x86 and x64)`

2. Install [Perl](http://strawberryperl.com/), open Perl Command Line and enter `cpan String::CRC32`. This is needed for building shaders.

3. Run /src/createallprojects.bat and build the solution either as release or debug.

4. Run /src/materialsystem/stdshaders/buildallshaders.bat, then build stdshader projects.


## 64-bit

64-bit support is being worked on. In the current state the entire codebase compiles as 64-bit but it cannot be started at this point. Feel free to contribute with a pull request.

Run ``createallprojects-x64.bat`` to create 64-bit projects. To build 64-bit projects you need to run ``build-solution-x64.bat`` through the [Microsoft Developer Command Prompt for VS2019](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs).

You can run the engine with run_mod_hl2.bat or run_hl2r.bat.

## Linux

Linux support is currently being worked on in the posix-support branch. Feel free to contribute with pull-requests.

## Contributing

Feel free to contribute to the project with pull requests. They will be reviewed and merged as fast as possible.
