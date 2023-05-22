# CITS3003 Project Template 2023

This is the template for the CITS3003 Project for 2023

## Important Preface

Firstly, **DO NOT** bother trying to run/build this in a VM or WSL or anything like that.
While it _may_ be _possible_ to do, there is no good reason to do it, and no support will be provided if you try this and have problems.

If you wish to dual boot or something, that is totally fine, but no support will be provided with getting the dual boot itself setup.

So, with that out of the way, pick your OS and IDE and follow the guide below.

## Terms

### Project Directory
This is the main directory you download, it will most likely be called `cits3003_project`, however regardless of what it is called,
it is the directory which contains `CMakeLists.txt`, `src`, `lib`, `res`, etc.. and also `README.md` this readme file itself.

## Setup

### Downloading Template

First download the project, by cloning the repository with (this requires you have git installed of course):

`git clone --recurse-submodules https://github.com/Matthew-Chidlow/cits3003_project_start_2023 cits3003_project`

Note that the `--recurse-submodules` is essential since, submodules are used for many of the dependencies.
(If you forget it, then you can run `git submodule update --recursive --init` to fetch them after the fact.)

Or if you have a partner, and they have already done this then clone from their git repo.

This will create the [Project Directory](#project-directory) and call it `cits3003_project`

If you cloned my git repo and want to create your own to store it, then the easiest thing to do:
* Create an empty repo on GitHub (or whatever git hosting website you want) just make sure it's **PRIVATE**, which you can share access to with your partner (if needed).
* `git remote rename origin upstream`
* `git remote add origin {url to your new repo}`
* `git branch -M {your repos main branch}`
* `git push -u origin {your repos main branch}`

Then you can treat it like a normal repo, and in the event that my repo is ever updated with say a patch to a bug,
you can pull that patch down with: `git pull upstream main` (and hopefully you don't have to deal with merge conflicts)

### Getting ready to build (Linux)

On Linux you will need a few build dependencies first before you can build the project.

For a debian based distro (like Ubuntu or PopOS), the following command should get you everything you need.
(If not then ask for help if you need it, and try to inform me what is missing, so I can add it to the list).

`sudo apt update && sudo apt install git cmake build-essential libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev xorg-dev`

### Getting ready to build (macOS)

A build chain, like: gcc/g++ or clang, etc is needed, this is usually provided by xCode, so if you don't have them
then get the xcode command line tools (or xcode itself, up to you). If there is an issue compiling, you might need to update xcode.

Cmake is also needed, you can get it from either homebrew or https://cmake.org/download/, either way make sure it's added
to your PATH, so it can be used from the command line. To do this you can run the cmake application, and then from the `Tools` menu,
select `How to Install For Command Line Use` and run one of the options that is presented to you.


### Getting ready to build (Windows)

If you plan to use CLion as your IDE, then there is nothing you need to do for this step, just skip to the CLion step below.

A build chain is needed, if you are familiar with the likes of cygwin or mingw, those work.
Otherwise, install Visual Studio (not Visual Studio Code, that's different) and when installing make sure to
select the `Desktop development with C++` `Workload` in the installer. To double-check, you can run `Visual Studio Installer` and
click `Modify` then check under `Workloads` that `Desktop development with C++`.

NOTE: If you wish to also use VS as an IDE you will need a version > 2017, since there is a bug in 2017 with cmake and git.


## Building and Running

### CLion (Windows, Mac & Linux)

Clion is my preferred c/c++ IDE, and in case you didn't know you can use your student email to get free access to all Jetbrains IDE (including CLion).

CLion makes it very simple to build and run.
* Firstly of course you will need to download and install CLion, either standalone or via Jetbrains Toolbox (this is the preferred way).
* Then, run CLion and open the [Project Directory](#project-directory).
* It may then ask you if you trust this project, say yes.
* It may or may not complain about not having a toolchain, if so then look back at the OS specific section and make sure you downloaded everything you need, if so ask for help.
* It then may ask you to set up your CMake profiles, I suggest clicking the `+` at the top of the list on the left to automatically add a release profile for compiling with optimizations enabled. Then click OK.
* Now you can switch between release and debug by clicking the `cits3003_project | {profile}` button again, and clicking the `Debug` or `Release` buttons.
* Then to build and run just click the play button next to `cits3003_project | {profile}`, to run with the debugger attached (to be able to hit break points) you can click the debug button next to that.
  * Something of important note is that debugging will only work properly if you have the `Debug` profile selected.


When you add source files, CLion should prompt you to add them to `CMakeLists.txt`, agree, as you need to do this.
If it doesn't prompt you then you will need to manually add the source files, and after editing `CMakeLists.txt` a prompt should appear to reload the CMake project,
you need to do this for the changes to `CMakeLists.txt` to be detected (You can also enable auto reloading if you want).

If it fails to prompt you, you can force it by in the toolbar clicking `Tools > CMake > Reload CMake Project`


### Visual Studio (Windows Only)

Visual Studio is Microsoft's heavyweight IDE.

VS Code is also simple to use:
* As a part of the Windows specify setup you should already have it installed.
* **HOWEVER**, Visual studio 2017 has a bug with cmake and git, so make sure you have a newer version than that.
* Then just open the [Project Directory](#project-directory), then wait for it to detect cmake and set things up.
* After that, up the top, select cits3003_project.exe as the startup item.
* Now you can run, debug and change profiles as you would normally.
  * To get a release profile click `x64-Debug`, then `Manage Configurations`, click the green plus on the left, then select `x64-release` from the list.
    Then change the `Configuration Type` to `Release`, then save that "file". Now you can click `x64-Debug` and select `x64-Release`.

### VS Code (Windows, Mac & Linux)

VS Code is a lightweight generic IDE that works manly via plugins to add support for languages and to add features.

VS Code is also simple to use:
* Firstly of course you need to download and install VS Code.
* Then make sure to install the `C/C++ Extension Pack` plugin, as this will add what you need for c++ and cmake.
* Then open the [Project Directory](#project-directory), trusting the folder.
* Dismiss any cmake notifications
* Then along the bottom of the screen there should be a button with a spanner crossing a screwdriver, labelled either `No Kit Selected` or something like GCC, Clang, MSVC, etc... . If this does say `No Kit Selected` click this and select one, e.g. GCC, Clang, MSVC, etc...
  * If no options show up, then click `Scan for kits`, and if then still nothing shows, revisit the OS specific section to make sure you installed everything, if you did ask for help
* Left of this kit selection button there is a profile selection button which allows you to switch between debug and release
* The first time, you may need to right-click `CMakeLists.txt` and click `Configure All Projects`
* Then down the bottom, there should also be buttons to run the current profile, as well as to run or debug it.
  * Something of important note is that debugging will only work properly if you have the `Debug` profile selected.
  * DO NOT try using the other methods of building/running, only these buttons down the bottom will correctly use CMake.

When you add source files, you will need to add them to the list in `CMakeLists.txt`, when saving the file, it should automatically reload the cmake projects.
If it fails to do that, then right right-click `CMakeLists.txt` and click `Configure All Projects`.

### Command Line

Make sure to `cd` into the [Project Directory](#project-directory)

Then to generate build files, run (these only needs to be re-run if you update CMakeLists.txt)

`cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug`

`cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release`

Then to build the debug profile, run:

`cmake --build cmake-build-debug`

Then to build the release profile, run:

`cmake --build cmake-build-release`

Then to run the last built profile, run:

`./cits3003_project` (or `/cits3003_project.exe` on Windows)


## Project Notes


### Default Control Scheme

* The `` ` `` key can be used to toggle ImGUI
* When interacting with a Drag/Slider control in ImGUI, ctrl+click (or double-click on Drag controls) to edit the value with the keyboard
* When interacting with a Drag control in ImGUI, use shift/alt to fasten/slow the dragging
* The `R` key can be used to reset the camera (Button also available in `Options & Info > Camera Options` menu)
* (In scenes that support it) The `V` key can be used to switch between camera types (Button also available in `Options & Info > Scene Settings` menu)
* The panning camera uses Middle Mouse, Right Mouse and Scroll Wheel
* The flying camera uses Right Mouse, WASD and Shift, Space
* The editor scene support Ctrl + O, Ctrl + S, Ctrl + Shift + S to open, save and save as. (Buttons also available in `Scene Hierachy`)

### Adding more source files

When/If you add a new source file to the project, then your IDE may handle this for you, but if not, you will need to
manually add the source file to the list in `CmakeLists.txt`, the `add_executable(project sources...)` list specifically,
notice that cmake use a whitespace deliminator to separate elements in a list.

### Properly propagating new entities and/or renderers

Be aware that if you add a new renderer or entity, there are many places that you might need to touch to hook it up correctly.
