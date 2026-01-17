## Windows

Rizin relies on the Meson build system generator to support compilation on all platforms, including Windows. Meson will generate a Visual Studio Solution, all the necessary project files, and wire up the Microsoft Visual C++ compiler for you.

> **tip** You can download nightly binaries from https://ci.appveyor.com/project/rizinorg/rizin/history. Be sure to download only from `master` branch!

### Prerequisites

* Visual Studio 2015 (or higher)
* Python 3
* Meson
* Git

### Step-by-Step

#### Install Visual Studio 2015 (or higher)

Visual Studio must be installed with a Visual C++ compiler, supporting C++ libraries, and the appropriate Windows SDK for the target platform version.

* In the Visual Studio 2015 installer, ensure `Programming Languages > Visual C++` is selected
* In the Visual Studio 2017+ installers, ensure the `Desktop development with C++` workload is selected

If you need a copy of Visual Studio, the Community versions are free and work great.

* [Download Visual Studio 2015 Community (registration required)](https://my.visualstudio.com/Downloads?q=visual%20studio%202015&wt.mc_id=o~msft~vscom~older-downloads)
* [Download Visual Studio 2017 Community](https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads)
* [Download Visual Studio 2019 Community](https://my.visualstudio.com/Downloads?q=visual%20studio%202019&wt.mc_id=o~msft~vscom~older-downloads)
* [Download Visual Studio 2022 Community](https://my.visualstudio.com/Downloads?q=visual%20studio%202022&wt.mc_id=o~msft~vscom~older-downloads)

#### Install Python 3 and Meson/Ninja via Conda
It is strongly recommended you install Conda — a Python environment management system — when working with Python on the Windows platform. This will isolate the Rizin build environment from other installed Python versions and minimize potential conflicts.

##### Set Up Conda:
1. Download the appropriate Conda (Python 3.x) for your platform (https://conda.io/miniconda.html)
2. Install Conda with the recommended defaults

##### Create a Python Environment for Rizin
Follow these steps to create and activate a Conda environment named *rizin*. All instructions from this point on will assume this name matches your environment, but you may change this if desired.

1. Start > Anaconda Prompt
2. `conda create -n rizin python=3`
3. `activate rizin`

Any time you wish to enter this environment, open the Anaconda Prompt and re-issue `activate rizin`. Conversely, `deactivate` will leave the environment.

##### Install Meson + Ninja

1. Enter the Rizin Conda environment, if needed (`activate rizin`)
2. Download meson + ninja
3. `pip install meson ninja`
4. Verify Meson is version 0.50 or higher (`meson -v`)

#### Install Git for Windows
All Rizin code is managed via the Git version control system and [hosted on GitHub](https://github.com/rizinorg).

Follow these steps to install Git for Windows.

1. Download [Git for Windows](https://git-scm.com/download/win)

  As you navigate the install wizard, we recommend you set these options when they appear:
    * Use a TrueType font in all console windows
    * Use Git from the Windows Command Prompt
    * Use the native Windows Secure Channel library (instead of OpenSSL)
    * Checkout Windows-style, commit Unix-style line endings (core.autocrlf=true)
    * Use Windows' default console window (instead of Mintty)

2. Close any previously open console windows and re-open them to ensure they receive the new PATH
3. Ensure `git --version` works

#### Get Rizin Code
Follow these steps to clone the Rizin git repository.

1. In your Rizin Conda environment, navigate to a location where the code will be saved and compiled. This location needs approximately **3-4GiB** of space
2. Clone the repository with `git clone --recurse-submodules https://github.com/rizinorg/rizin.git`

#### Compile Rizin Code
Follow these steps to compile the Rizin Code.

Compiled binaries will be installed into the `dest` folder.

1. Enter the Rizin Conda environment
2. Navigate to the root of the Rizin sources (`cd rizin`)
3. Initialize Visual Studio tooling by executing the command below that matches the version of Visual Studio installed on your machine and the version of Rizin you wish to install:

    * **Visual Studio 2015:**

        Note: For the 64-bit version change only the `x86` at the very end of the command below to `x64`.

        `"%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86`

    * **Visual Studio 2017/2019:**

        Note 1: Change `Community` to either `Professional` or `Enterprise` in the command below depending on the version installed.

        Note 2: Change `vcvars32.bat` to `vcvars64.bat` in the command below for the 64-bit version.

        Note 3: Change `2017` to `2019` if you are using Visual Studio 2019.

         `"%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"`
    
    * **Visual Studio 2022:**

        Note: For the 32-bit version change only the `x64` at the very end of the command to `x86`.

         `call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64`

    * **Visual Studio Preview:**

        Note 1: Change `Community` to either `Professional` or `Enterprise` in the command below depending on the version installed.

        Note 2: Change `vcvars32.bat` to `vcvars64.bat` in the command below for the 64-bit version.

        `"%ProgramFiles(x86)%\Microsoft Visual Studio\Preview\Community\VC\Auxiliary\Build\vcvars32.bat"`


4. Generate the build system with Meson:

  Note 1: Change `debug` to `release` in the command below depending on whether the latest version or release version is desired.

  `meson --buildtype debug --prefix %cd%\dest build`

  Meson currently requires `--prefix` to point to an absolute path. We use the %CD% pseudo-variable to get the absolute path to the current working directory.

5. Start a build:

  `ninja -C build`

6. Install into your destination folder: `ninja -C build install`
7. Check your Rizin version: `dest\bin\rizin.exe -v`

#### Check That Rizin Runs From All Locations
1. In the file explorer go to the folder Rizin was just installed in.
2. From this folder go to `dest` > `bin` and keep this window open.
3. Go to System Properties: In the Windows search bar enter `sysdm.cpl`.
4. Go to `Advanced > Environment Variables`.
5. Click on the PATH variable and then click edit (if it exists within both the user and system variables, look at the user version).
6. Ensure the file path displayed in the window left open is listed within the PATH variable. If it is not add it and click `ok`.
7. Log out of your Windows session.
8. Open up a new Windows Command Prompt: type `cmd` in the search bar. Ensure that the current path is not in the Rizin folder.
9. Check Rizin version from Command Prompt Window: `rizin -v`
