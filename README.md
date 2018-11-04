# Unnamed (Placeholder Name)
It's not going to be called **_Unnamed_**, but I haven't though of a **good unused** name.

## About
Nothing as of now.

## Setup
1. Download **[polly](https://github.com/ruslo/polly)** and save it in a directory named **_polly_** in your project directory or do `git clone https://github.com/ruslo/polly.git` in your project directory.

### Microsoft Visual Studio
2. Click **File > Open > CMake...** and then choose **_CMakeLists.txt_**.
3. _Wait..._
4. **Almost** everything should be set because some configurations will not work.<br>
   See below.
#### Android
5. Download **[Android NDK](https://developer.android.com/ndk/downloads/) _r15c_**.
#### Linux
##### Windows
5. See this **[guide](https://blogs.msdn.microsoft.com/vcblog/2017/02/08/targeting-windows-subsystem-for-linux-from-visual-studio/)** _([archive](https://archive.fo/QgEBg))_ to build for Linux on Windows.<br>
   You may also want to remove `#` from `#Port 22` and change `22` to **any port that you haven't used** when editing **_/etc/ssh/sshd_config_**.
   When connecting, use **the port you set** instead of `22`.
#### iOS _and_ macOS
5. _Haven't figured it out yet. **Help needed.**_ :confused:

### Console
2. Download and install **[CMake](https://cmake.org/download/) _3.8 or above_**.
3. See [_usage of_ **polly**](https://github.com/ruslo/polly/blob/master/README.md#usage).<br>
   Additional **CMake** arguments for each configuration can be found in **_CMakeSettings.json_**.<br>
   See above for installing missing components needed to build for specific configurations.

### Others
_New guides are being added._<br>
_If you want to add new guides, start a **pull request**._
