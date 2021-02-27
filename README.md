[![CI](https://github.com/wildmichael/cpp_project_template/actions/workflows/ci.yml/badge.svg)](https://github.com/wildmichael/cpp_project_template/actions/workflows/ci.yml)

# C++ Project Template

> A project template that contains the most important boilerplate for a C++17
> project built with CMake.

This repository provides a basic starter template where many of the often
tedious and not-so-obvious problems have been addressed. It uses [CMake] as its
build system and [vcpkg] for the dependency management. Unit testing uses the
[Catch2] and [trompeloeil] libraries. The project contains further setup for
[development inside a Docker container][devcontainer] with the [Visual Studio
Code] IDE. The container setup also includes a number of useful plugins for the
IDE.

## Directory Structure

-   `include/`: public headers provided by this project.
-   `src/lib/`: implementation files and private headers for the library component
    of this project.
-   `src/app`: implementation files and private headers for the application
    component.
-   `test/`: unit tests for the library component.
-   `cmake/`: Helper files for [CMake].
-   `.github/workflows/`: Continuous integration workflow for [GitHub Actions].
-   `.github/ISSUE_TEMPLATE/`: [Templates] for GitHub issues.
-   `.vscode/`: Configuration files for [Visual Studio Code].
-   `.devcontainer/`: Configuration files that allow the development inside a
    [Docker] container with a [standardized setup using Visual Studio
    Code][devcontainer].

## Prerequisites

-   Developing inside a Docker container is not a hard requirement, but I find it
    to be very efficient as it guarantees a consistent environment across the
    whole team. Linux users should be able to install Docker using their package
    manager. Users of recent Windows 10 versions can take advantage of [WSL 2]
    following these [instructions][docker on wsl2]. For Mac there is [Docker for
    Mac].
-   You need a programmer's text editor, or a full-blown IDE. If you decide to
    develop inside a Docker container, [Visual Studio Code] is currently your only
    option. It sits somewhere between text editor and IDE and gained enormous
    popularity over the recent years.
-   A [Git] client.
-   In case you decide against using Docker, you will have to install a number
    of additional dependencies:
    -   A C++ compiler. Again, Linux users can use their package manager to get
        e.g. G++ or Clang. On Windows there are a number of options, ranging from
        free to very expensive. Microsoft provides a free community edition of
        [Visual Studio] for private or open-source use and the [Visual Studio Build
        Tools] (i.e. the compilers without the IDE) even for commercial use. Make
        sure that you select the _C++ build tools_ workload in the installer which
        will get you the MSVC compiler. Additionally, from _Individual Components_,
        you can also install the open-source [Clang] compilers. Mac users can use
        [Xcode] or e.g. [Homebrew] to get a C++ toolchain installed.
    -   [vcpkg] is the package manager used by this project template, so you'll
        have to install that too.
    -   [CMake] is the build system generator used by this project. Depending on
        your system, you might also need to install e.g. [Make] or [Ninja].

## Getting Started Developing in a Container

-   Clone this repository to your computer.
-   Open the cloned repository in [Visual Studio Code].
-   Install the [Remote Containers][ext remote containers] extension.
-   Press `F1` to open the command bar and type `Reopen in Container` and press
    `Enter`. The first time this takes a while because the Docker image needs to
    be built first.
-   If this was successful, Visual Studio Code should prompt you which compiler
    kit to use. You can use either select `Clang 10.0.0 x86_64-pc-linux-gnu` or
    `GCC 9.3.0 x86_64-pc-linux-gnu`, both should work just fine.
-   Hit `F7` to build the project.
-   Open the test explorer (looks like a flask in the left-hand side bar) and
    click the play button to run all tests.
-   Press `F5` to run the main application. You should see a friendly greeting
    in the output window.

If everything was successful, you're good to go!

## Getting Started Developing with Visual Studio Code but without a Container

Ok, containers are not your thing, or your Software is OS dependent / not
cross-platform, but you still want to use [Visual Studio Code].

-   Clone this repository to your computer.
-   Open the cloned repository in [Visual Studio Code].
-   Open the extensions menu (`CTRL+SHIFT+X`) and in the search box type
    `@recommended`. From the `WORKSPACE RECOMMENDATIONS` list at least install the
    following extensions:

    -   [C/C++][ext cpp]
    -   [CMake][ext cmake]
    -   [Test Explorer UI][ext test explorer]
    -   [C++ Test Mate][ext catch2]

    While the other extensions I recommended are optional, they really are
    highly recommended 😉.

-   Hit `F1` and type `Scan for Kits` and press `Enter`.
-   Hit `F1` and type `Edit user-local CMake Kits` and press `Enter`. A file
    named `cmake-tools-kits.json` should open up. It contains a list of discovered
    compiler toolchains. To each of those entries add a new key naming the `vcpkg`
    toolchain file for CMake like the following, substituting of course the real
    path to `vcpkg.cmake`:

```jsonc
{
    // ... SNIP ...
    "toolchainFile": "c:/software/vcpkg/scripts/buildsystems/vcpkg.cmake",
    // ... SNAP ...
},
```

-   Hit `F1` and type `Select a Kit`, press `Enter` and from the selection pick
    the compiler kit of your choice.
-   Again, press `F1` and type `CMake: Configure`, followed by `Enter`. When
    successful, the output panel should display
    `[cmake] -- Build files have been written to: ...` in the last line.
-   Hit `F7` to build the project.
-   Open the test explorer (looks like a flask in the left-hand side bar) and
    click the play button to run all tests.
-   If you are not on Windows, press `F1` again, type `Open launch.json`
    followed by `Enter`. The text editor that opens should have a big blue
    button labelled `Add Configuration...`. Press it and select an appropriate
    configuration. Adjust the `program` entry for the newly added configuration
    to reflect the one present in the `(Windows) Launch` configuration. Save and
    close the file.
-   Press `F5` to run the main application. You should see a friendly greeting
    in the output window.

## Using Neither Containers or Visual Studio Code

You seem to know what you're doing. You'll do just fine.

## Renaming the Project

-   Edit the `vcpkg.json` file and edit the project name. The top-level
    `CMakeLists.txt` reads this file and uses it to define the project name inside
    CMake.
-   Both, `src/lib/CMakeLists.txt` and `src/app/CMakeLists.txt` use that name
    throught the `${PROJECT_NAME}` variable. Depending on your needs, you might
    want to change that. If you do, `test/CMakeLists.txt` might also need to be
    changed.
-   Rename the `include/myproject/` folder. The top-level `CMakeLists.txt` file
    references this folder when creating the `config.hpp` file from `config.hpp.in`,
    so you need to edit that too. That folder name is also used in the
    `#include`'s of `src/app/main.cpp` and `test/hello_test.cpp`.
-   For some purposes, a sanitized, upper-cased project name is required. The
    top-level project defines it in the `${PROJECT_NAME_SAN}` variable by
    upper-casing the project name and replacing all characters that are not
    letters or digits with an underscore (`_`). You should search all
    occurrences of `MYPROJECT` (all-caps) and replace them with your sanitized
    project name.
-   Change the `namespace` name in all source files.
-   Fix the launch configuration in `.vscode/launch.json`.

## Adding New Tests

-   Add the new unit tests file to the `test/` folder.
-   Edit `test/CMakeLists.txt` and add the new test name (without the file
    extension) to the `TEST_NAMES` variable.

## Adding More Dependencies

-   Edit the `vcpkg.json` file and add the additional dependencies to the
    `dependencies` list. Refer to the [documentation][vcpkg manifest] for more
    details on the `vcpkg.json` manifest file.
-   Edit the top-level `CMakeLists.txt` file and add an additional
    `find_package(... CONFIG REQUIRED)` call for each of the dependencies. Note
    that most `vcpkg` packages, but not all, use this convention. When
    installing the package from the command line using `vcpkg install foo`
    the exact usage instructions are printed out at the end.
-   Edit the `CMakeLists.txt` containing the target that will use the dependency.
    In the `target_link_libraries()` call add a new argument. Most packages use
    the convention `foo::foo` for a package named `foo`. But as before, some
    packages deviate, or have more options. Again, installing the package
    manually on the command line will reveal the usage instructions.
-   Upon build, CMake should care of installing the additional dependencies.

## Adding More Targets

-   Add the directory under `src/` and copy the `CMakeLists.txt` file from either
    `lib/` or `app/`, depending on whether you want to add a library or executable
    target. Edit the newly created file as appropriate.
-   Add a `add_subdirectory()` call with the new directory to
    `src/CMakeLists.txt`.

[ext catch2]: https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter
[catch2]: https://github.com/catchorg/Catch2
[clang]: https://clang.llvm.org/
[ext cmake]: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools
[cmake]: https://cmake.org
[ext cpp]: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
[devcontainer]: https://code.visualstudio.com/docs/remote/containers
[docker for mac]: https://docs.docker.com/docker-for-mac/install/
[docker on wsl2]: https://docs.microsoft.com/en-us/windows/wsl/tutorials/wsl-containers
[docker]: https://www.docker.com/
[ext editorconfig]: https://marketplace.visualstudio.com/items?itemName=editorconfig.editorconfig"
[git]: https://git-scm.com
[github actions]: https://docs.github.com/en/actions
[homebrew]: https://brew.sh/
[make]: https://www.gnu.org/software/make/
[ninja]: https://ninja-build.org/
[ext prettier]: https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode
[ext remote containers]: https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers
[templates]: https://docs.github.com/en/communities/using-templates-to-encourage-useful-issues-and-pull-requests/about-issue-and-pull-request-templates
[ext test explorer]: https://marketplace.visualstudio.com/items?itemName=hbenl.vscode-test-explorer
[trompeloeil]: https://github.com/rollbear/trompeloeil
[vcpkg manifest]: https://vcpkg.readthedocs.io/en/latest/users/manifests/
[vcpkg]: https://github.com/microsoft/vcpkg
[visual studio build tools]: https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019
[visual studio code]: https://code.visualstudio.com/
[visual studio]: https://visualstudio.microsoft.com/
[wsl 2]: https://docs.microsoft.com/en-us/windows/wsl/install-win10
[xcode]: https://developer.apple.com/xcode/
