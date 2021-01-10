# Debugging on MacOS over SSH

If you are trying to debug a program over SSH, you may experience failures like rizin
getting stuck while opening the file. This is because the OS is waiting for
user authentication before allowing the debugging. However, since you are over
SSH the OS has no way of showing the permission window.

To avoid this problem you can either run rizin with `sudo` or you may instruct taskport to not authenticate the user by executing the following commands:

```sh
security authorizationdb read system.privilege.taskport > taskport.plist
/usr/libexec/PlistBuddy -c 'Set :authenticate-user false' ./taskport.plist
sudo security authorizationdb write system.privilege.taskport < taskport.plist
```

The above will disable the debugging authentication prompt even after you reboot.
