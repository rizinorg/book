# macOS/iOS

## Sign rizin binary
If you install the Rizin pkg file and try to use it to debug a binary, you
will very likely get an error message such as:
```
Child killed
ptrace: Cannot attach: Invalid argument

Please ensure your rizin binary is signed and it has the right entitlements
to make debugger work. Be aware that binaries signed by Apple cannot be
debugged due to the Apple System Integrity Protection (SIP).

For more info look at: https://book.rizin.re/debugger/apple.html#sign-rizin-binary
```

This is because the Darwin kernel will refuse to allow rizin to debug another
process if you don't have special rights (or if you are not root).

To sign the binary and give it the special rights to allow debugging as a
regular user, download the Entitlements file
[here](https://github.com/rizinorg/rizin/blob/dev/binrz/rizin/rizin_macos.xml).
Then execute the following command:

```bash
$ codesign --entitlements <entitlements-file> --force -s - $(which rizin)
```

However, be aware that even with a signed rizin binary you cannot debug
binaries signed by Apple. To bypass the problem you have a few options:
- Remove the certificate of the debuggee, by using
  `codesign --remove-signature <binary>` or other alternatives like
  [unsign](https://github.com/steakknife/unsign). WARNING: this cannot be
  undone, so we suggest to make a copy of the original binary.
- Disable SIP with `csrutil enable --without debug` in Recovery Mode.


## Debugging on MacOS over SSH

If you are trying to debug a program over SSH, you may experience failures
like rizin getting stuck while opening the file. This is because the OS is
waiting for user authentication to allow debugging. However, since
you are over SSH, the OS has no way of showing the permission window.

To avoid this problem you can either run rizin with `sudo` or you may
instruct taskport to not authenticate the user by executing the following
commands. This will disable the debugging authentication prompt even after
you reboot.

```bash
security authorizationdb read system.privilege.taskport > taskport.plist
/usr/libexec/PlistBuddy -c 'Set :authenticate-user false' ./taskport.plist
sudo security authorizationdb write system.privilege.taskport < taskport.plist
```
