# Virtual Tables

There is basic support of virtual tables parsing (RTTI and others).
The most important thing before you start to perform such kind of analysis
is to check if the `analysis.cpp.abi` option is set correctly and change it if needed.

All commands to work with virtual tables are located in the `av` namespace.
Currently, the support is very basic, allowing you only to inspect
parsed tables.

```
|Usage: av[?jr*] C++ vtables and RTTI
| av           search for vtables in data sections and show results
| avj          like av, but as json
| av*          like av, but as rizin commands
| avr[j@addr]  try to parse RTTI at vtable addr (see analysis.cpp.abi)
| avra[j]      search for vtables and try to parse RTTI at each of them
```

The main commands here are `av` and `avr`. `av` lists all virtual tables
found when rizin opened the file. If you are not happy with the result
you may want to try to parse a virtual table at a particular address with
`avr` command. `avra` performs the search and parsing of all virtual
tables in the binary, like rizin does during the file opening.
