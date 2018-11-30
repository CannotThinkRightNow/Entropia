# Setup
1. See [PREREQUISITE.md](PREREQUISITE.md).

## Microsoft Visual Studio
2. Click **File > Open > CMake...** and then choose **_CMakeLists.txt_**.
3. _Wait..._
4. **Almost** everything should be set because some configurations will not work.<br>
   See below.
### Windows
#### iOS
_You can't.<br>
Use a machine running on **macOS** instead._
#### Linux
5. See this **[guide](https://blogs.msdn.microsoft.com/vcblog/2017/02/08/targeting-windows-subsystem-for-linux-from-visual-studio/)** _([archive](https://archive.fo/QgEBg))_ to build for **Linux** on **Windows**.<br>
   You may also want to remove `#` from `#Port 22` and change `22` to **any port that you haven't used** when editing **_/etc/ssh/sshd_config_**.
   When connecting, use **the port you set** instead of `22`.
#### macOS
_You can't.<br>
Use a machine running on **macOS** instead._
### Linux
_Working on it..._

## Console
2. See [_usage of_ **polly**](https://github.com/ruslo/polly/blob/master/README.md#usage).<br>
   Additional **CMake** arguments for each configuration can be found in **_CMakeSettings.json_**.<br>
   See above for installing missing components needed to build for specific configurations.

## Others
_New guides are being added._<br>
_If you want to add new guides, start a **pull request**._
