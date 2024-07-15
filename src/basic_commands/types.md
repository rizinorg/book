## Working with data types

Rizin can also work with data types. You can use standard C data types or define your own using C. Currently, there is a support for structs, unions, function signatures, and enums.

```
[0x00000000]> t?
Usage: t[?]   # Types, noreturn, signatures, C parser and more
| t[j*] [<type>] # List all types / Show type information
| t- <type>      # Remove the type
| t-*            # Remove all types
| tc[dc]         # List loaded types in C format
| td <type>      # Define type from C definition
| te[jbcdf]      # List loaded enums
| tf[j-c?]       # List loaded functions definitions
| tn[j-?]        # Manage noreturn function attributes and marks
| to[es]         # Open C header file and load types from it
| tp[vx]         # Print formatted type casted to the address
| ts[jlcd]       # List loaded structures
| tt[jc]         # List loaded typedefs
| tu[jlcd]       # List loaded unions
| tx[fgl]        # Type xrefs
```

### Defining new types

There are three different methods to define new types:

1. Defining a new type from rizin shell immediately, to do this you will use `td` command, and put the whole line between double quotes. For example:

`td "struct person {int age; char *name; char *address;};"`

2. You can also use `to -` to open a text editor and write your own types in there. This is preferable when you got too many types to define.

3. Rizin also supports loading header files using the command `to` followed by a path to the header file you want to load.

You can View loaded types in rizin using `ts` for structures, `tu` for unions, `tf` for function signatures, `te` for enums.

You can also cast pointers to data types and view data in there accordingly with `tp`. EX:

```
[0x00400511]> tp person = 0x7fff170a46b0
       age : 0x7fff170a46b0 = 20
       name : (*0x4005b0) 0x7fff170a46b4 = My name
       address : (*0x4005b8) 0x7fff170a46bc = My age
[0x00400511]> 
```