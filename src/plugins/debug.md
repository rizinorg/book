# Debugging

It is common to have an issues when you write a plugin, especially if you do this for the first
time. This is why debugging them is very important. The first step for debugging is
to set an environment variable when running rizin instance:
```
R_DEBUG=yes rizin /bin/ls
Loading /usr/local/lib/rizin/2.2.0-git//bin_xtr_dyldcache.so
Cannot find symbol 'rizin_plugin' in library '/usr/local/lib/rizin/2.2.0-git//bin_xtr_dyldcache.so'
Cannot open /usr/local/lib/rizin/2.2.0-git//2.2.0-git
Loading /home/user/.config/rizin/plugins/asm_mips_ks.so
PLUGIN OK 0x55b205ea6070 fcn 0x7f298de08762
Loading /home/user/.config/rizin/plugins/asm_sparc_ks.so
PLUGIN OK 0x55b205ea6070 fcn 0x7f298de08762
Cannot open /home/user/.config/rizin/plugins/pimp
Cannot open /home/user/.config/rizin/plugins/yara
Loading /home/user/.config/rizin/plugins/asm_arm_ks.so
PLUGIN OK 0x55b205ea6070 fcn 0x7f298de08762
Loading /home/user/.config/rizin/plugins/core_yara.so
Module version mismatch /home/user/.config/rizin/plugins/core_yara.so (2.1.0) vs (2.2.0-git)
Loading /home/user/.config/rizin/plugins/asm_ppc_ks.so
PLUGIN OK 0x55b205ea6070 fcn 0x7f298de08762
Loading /home/user/.config/rizin/plugins/lang_python3.so
PLUGIN OK 0x55b205ea5ed0 fcn 0x7f298de08692
Loading /usr/local/lib/rizin/2.2.0-git/bin_xtr_dyldcache.so
Cannot find symbol 'rizin_plugin' in library '/usr/local/lib/rizin/2.2.0-git/bin_xtr_dyldcache.so'
Cannot open /usr/local/lib/rizin/2.2.0-git/2.2.0-git
Cannot open directory '/usr/local/lib/rizin-extras/2.2.0-git'
Cannot open directory '/usr/local/lib/rizin-bindings/2.2.0-git'
USER CONFIG loaded from /home/user/.config/rizin/rizinrc
 -- In visual mode press 'c' to toggle the cursor mode. Use tab to navigate
[0x00005520]>
```
