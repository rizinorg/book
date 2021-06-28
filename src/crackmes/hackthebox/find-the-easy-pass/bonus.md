# Bonus

In the previous pages, we discovered the right password
but is it calculated or hard-coded.

To do this, we will look at what happens from the
beginning of the current function from the
address `0x00454084`.

go to the address `0x00454084`

![bonus-01](./img/bonus-01.png)

Take a break and observe the assembly code.
You will see a repeating code sequence :

```assembly
mov eax, [ebp - X] ; or X is between 0x8 and 0x24
mov edx, Y , or Y is between 0x00454188  and 0x004541d0
```


Look the address `0x00454188`

![bonus-02](./img/bonus-02.png)

![bonus-03](./img/bonus-03.png)

Pay attention to the previous picture. You can see the password
broken down letter by letter.

The routine concatenates each letter into a string and compares
it to a user input.
