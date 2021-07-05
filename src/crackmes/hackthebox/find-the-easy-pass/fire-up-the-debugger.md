# Fire up the debugger

The next step will be to put a breakpoint at `0x0045412b`,
this address contains probably the right password or our.
Press `F2` key to put a breakpoint.

![find-the-validation-routine-breakpoint-to-fish-code-1](./img/find-the-validation_routine-15.png)

Press `:` , `d` and `c` to run `EasyPass.exe`.

![run-the-program-debugged-1](./img/fire-up-the-debugger-01.png)

![run-the-program-debugged-2](./img/fire-up-the-debugger-02.png)

Press `:` , `d` and `c` or `F9` key.

![run-the-program-debugged-3](./img/fire-up-the-debugger-03.png)

Press `:` , `d` and `c` or `F9` key.

![run-the-program-debugged-4](./img/fire-up-the-debugger-04.png)

The program is launched.

![run-the-program-debugged-5](./img/fire-up-the-debugger-05.png)

Enter a placeholder text and click on the "Check Password" button.

Logically, the program should stop at our breakpoint point.

![run-the-program-debugged-6](./img/fire-up-the-debugger-06.png)

Press `q` and then `p` to show the debugger view panel.

![run-the-program-debugged-7](./img/fire-up-the-debugger-07.png)

Press `F8` key to step over.

![run-the-program-debugged-8](./img/fire-up-the-debugger-08.png)

Press `g`, enter `eax` and `P` twice.

![run-the-program-debugged-9](./img/fire-up-the-debugger-09.png)

That's great our placeholder text is in memory.

Press `p` twice, `g` and enter `rip`.

![run-the-program-debugged-10](./img/fire-up-the-debugger-10.png)

Press `F8` key.

![run-the-program-debugged-11](./img/fire-up-the-debugger-11.png)

Press `g`, enter `edx` and `P` twice.

![run-the-program-debugged-12](./img/fire-up-the-debugger-12.png)

The right password seems to be **fortan!**.

Press `p` twice, `g` and enter `rip`.

Press `F8` key twice.

![run-the-program-debugged-13](./img/fire-up-the-debugger-13.png)

The call at `0x0045413d` seems to compare the previous password and 
when unequal, the program jumps to the "Wrong Pasword!" message.

Press `F9` key to show the message box.

After that, enter "fortan!" string and repeat the previous step until
the address `0x0045413d`.

![run-the-program-debugged-14](./img/fire-up-the-debugger-14.png)

Press `F8`key twice.

![run-the-program-debugged-15](./img/fire-up-the-debugger-15.png)

it's seems all right ! Press `F9` key to confirm this fact.

![run-the-program-debugged-16](./img/fire-up-the-debugger-16.png)
