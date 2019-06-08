# Unnamed _(Placeholder)_
It's not going to be called **_Unnamed_**, but I haven't though of a **good unused** name.

[LGPL-3.0 License Logo]: https://www.gnu.org/graphics/lgplv3-with-text-95x42.png
[LGPL-3.0 License]: https://www.gnu.org/licenses/lgpl-3.0
[CC-BY-4.0 License Logo]: https://i.creativecommons.org/l/by/4.0/88x31.png
[CC-BY-4.0 License]: https://creativecommons.org/licenses/by/4.0/legalcode
[Travis CI Status]: https://img.shields.io/travis/etaoinshrdlcumwfgypbvkjxqz/unnamed.svg?logo=travis&style=plastic
[Travis CI Build]: https://travis-ci.org/etaoinshrdlcumwfgypbvkjxqz/unnamed
[AppVeyor Status]: https://img.shields.io/appveyor/ci/etaoinshrdlcumwfgypbvkjxqz/unnamed.svg?logo=appveyor&style=plastic
[AppVeyor Build]: https://ci.appveyor.com/project/etaoinshrdlcumwfgypbvkjxqz/unnamed

| Licenses                                                                                                                                                                            | Build Status                                                                                      |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------|
|[![GNU Lesser General Public License 3.0][LGPL-3.0 License Logo]][LGPL-3.0 License]<br>[![Creative Commons Attribution 4.0 International][CC-BY-4.0 License Logo]][CC-BY-4.0 License]|[![Travis CI][Travis CI Status]][Travis CI Build]<br>[![AppVeyor][AppVeyor Status]][AppVeyor Build]|

## About
Nothing as of now.

## Setup
1. `git clone https://github.com/etaoinshrdlcumwfgypbvkjxqz/unnamed.git`
2. Change directory to the cloned directory.
3. `git submodule update --init --recursive`

### Dependencies
#### Required
- **[Git](https://git-scm.com/downloads)**
- **[CMake](https://cmake.org/download/) _3.12 or above_**
- **[Boost](https://www.boost.org/users/download/) _1.44.0 or above_**
##### Linux
- **X11**
  - **RandR**
  - **Xinerama**
  - **Xcursor**
  - **XInput**

#### Optional
##### Android
- **[Android NDK](https://developer.android.com/ndk/downloads/) _r15c_**

#### Commands
##### Linux
**Ubuntu**: `sudo apt-get install git cmake libboost-all-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev`

### Microsoft Visual Studio
4. Click **File > Open > CMake...** and then choose **_CMakeLists.txt_**.
5. _Wait..._
6. **Almost** everything should be set because some configurations will not work.<br>
   See below.
#### Windows
##### iOS
_You can't.<br>
Use a machine running on **macOS** instead._
##### Linux
7. See this **[guide](https://blogs.msdn.microsoft.com/vcblog/2017/02/08/targeting-windows-subsystem-for-linux-from-visual-studio/)** _([archive](https://archive.fo/QgEBg))_ to build for **Linux** on **Windows**.<br>
   You may also want to remove `#` from `#Port 22` and change `22` to **any port that you haven't used** when editing **_/etc/ssh/sshd_config_**.
   When connecting, use **the port you set** instead of `22`.
##### macOS
_You can't.<br>
Use a machine running on **macOS** instead._
#### Linux
_Working on it..._

### Console
4. See [_usage of_ **polly**](https://github.com/ruslo/polly/blob/master/README.md#usage).<br>
   Additional **CMake** arguments for each configuration can be found in **_CMakeSettings.json_**.<br>
   See above for installing missing components needed to build for specific configurations.

### Others
_New guides are being added._<br>
_If you want to add new guides, start a **pull request**._
