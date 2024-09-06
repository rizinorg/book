## Android

Rizin can be cross-compiled for other architectures/systems as well, like Android.

### Prerequisites

* Python 3
* Meson
* Ninja
* Git
* Android NDK

### Step-by-step

#### Download and extract the Android NDK

Download the Android NDK from the [official site](https://developer.android.com/ndk) and extract it somewhere on your system (e.g. `/tmp/android-ndk`)

#### Meson

See also [BUILDING.md](https://github.com/rizinorg/rizin/blob/dev/BUILDING.md#cross-compilation-for-android).

##### Create a cross-file for meson

Meson needs a configuration file that describes the cross compilation environment (e.g. `meson-android.ini`).
You can adjust it as necessary, but something like the following should be a good starting point:
```
[binaries]
c       = '/tmp/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android28-clang'
cpp     = '/tmp/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android28-clang++'
ar      = '/tmp/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android-ar'
as      = '/tmp/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android-as'
ranlib  = '/tmp/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android-ranlib'
ld      = '/tmp/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android-ld'
strip   = '/tmp/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip'
pkgconfig = 'false'

[properties]
sys_root = '/tmp/android-ndk/sysroot'

[host_machine]
system = 'android'
cpu_family = 'arm'
cpu = 'aarch64'
endian = 'little'
```

##### Compile with meson + ninja

Now setup the build directory with meson as usual:
```
$ meson --default-library static -Dstatic_runtime=true --prefix=/tmp/android-dir -Dblob=true build --cross-file ./meson-android.ini
```

A bit of explanation about all the options:
* `--default-library static -Dstatic_runtime=true`: this ensure that libraries
  and binaries are statically compiled, so you do not need to properly set LD_\*
  environment variables in your Android environment to make it find the right
  libraries. Binaries have everything they need inside.
* `-Dblob=true`: it tells meson to compile just one binary with all the needed
  code for running `rizin`, `rz-bin`, `rz-asm`, etc. and creates symbolic links to
  those names. This avoids creating many statically compiled large binaries and
  just create one that provides all features. You will still have `rz-bin`,
  `rz-asm`, `rz-ax`, etc. but they are just symlinks to `rizin`.
* `--cross-file ./meson-android.ini`: it describes how to compile rizin for Android

Then compile and install the project:
```
$ ninja -C build
$ ninja -C build install
```

##### Move files to your android device and enjoy

At this point you can copy the generated files in /tmp/android-dir to your Android device and running rizin from it.
For example:
```
$ cd /tmp && tar -cvf rizin-android.tar.gz android-dir
$ adb push rizin-android.tar.gz /data/local/tmp
$ adb shell
DEVICE:/ $ cd /data/local/tmp
DEVICE:/data/local/tmp $ tar xvf rizin-android.tar.gz
DEVICE:/data/local/tmp $ ./android-dir/bin/rizin
Usage: rizin [-ACdfLMnNqStuvwzX] [-P patch] [-p prj] [-a arch] [-b bits] [-i file]
          [-s addr] [-B baddr] [-m maddr] [-c cmd] [-e k=v] file|pid|-|--|=
```
