## Global Variables(avg commands)

Global variables are declared outside any function or block and are accessible throughout the program. They persist for the program's entire execution. This improves readability, enables better analysis and makes cross-references easier to follow.

Note: In Rizin you can analyze using `aa` or `aaa`. You will get global variables only after analyzing, so make sure you analyze first.

Rizin provides a list of `avg` commands to list, add, modify, delete and inspect the global variables found in the analysis of the executable file.

Note: The help command to list all `avg` commands is: `avg?`
```
 avgl[jqt] [<var_name>]          # show/list global variables
 avga <var_name> <type>          # add global variable manually
 avgd <addr>                     # delete the global variable at the addr
 avgm <name>                     # delete global variable with name
 avgn <old_var_name> <new_var_name> # rename the global variable
 avgp <name>                     # print the global variable value
 avgt <var_name> <type>          # change the global variable type
 avgx[jq] <name>                 # print all xrefs to the global variable
```

 **Listing Global Variables**

 `avgl[jqt] <var_name>` This command will list all the global variables.

 ``` 
 avgl [<var_name>]       # show/list global variables
 avglj [<var_name>]      # show/list global variables (JSON mode)
 avglq [<var_name>]      # show/list global variables (quiet mode)
 avglt [<var_name>]      # show/list global variables (table mode)
 ```
 There are 3 modes of display. Which helps in a better analysis and view the variables.

 **Adding Global Variables**

 `avga <var_name> <type>` This command lets you manually add global variables with their name and type.

 You use then when a global variables is missed during the analysis. Here `<type>` means the datatype of the variable. Example int, char, long.

 **Deleting Global Variables**

 `avgd <addr>` This command deletes the global variable located at the given address.

 `avgm <name>` This command also lets you delete the global variable using its name.

 **Renaming Global Variables**

 `avgn <old_var_name> <new_var_name>` This command lets you rename the global variables.

 **Printing Global Variables**

 `avgp <name>` This command prints the value of the variable.

 **Changing Variable Type**

 `avgt <var_name> <type>` This command lets you change the data-type of the variable.

 Note: The correct data-type must be used which helps in improving output, cross-reference accuracy and structure recovery.

 **Cross-References to Global Variables**

 `avgx[jq] <name>` This command shows all the xrefs to the given global variable.
 
 ```
 avgx <name>      # print all xrefs to the global variable
 avgxj <name>     # print all xrefs to the global variable (JSON mode)
 avgxq <name>     # print all xrefs to the global variable (quiet mode)
 ```
 There are two modes of display quiet and JSON.
