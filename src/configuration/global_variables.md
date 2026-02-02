# Global Variables(`avg` Commands)

Global variables are declared outside of any function or block and are accessible throughout the entire program. They persist for the full duration of execution.

In reverse engineering, identifying global variables:

- Improves code readability  
- Makes cross-references easier to follow  
- Helps with data-flow and structure analysis  

**Important:**
> In Rizin, global variables are identified during analysis.  
> Run `aa` or `aaa` before using `avg` commands, otherwise no globals will appear.

The help command to list all `avg` commands is: `avg?` 
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

 ``` 
 avgl [<var_name>]       # show/list global variables
 avglj [<var_name>]      # show/list global variables (JSON mode)
 avglq [<var_name>]      # show/list global variables (quiet mode)
 avglt [<var_name>]      # show/list global variables (table mode)
 ```
 There are 3 modes of display. Which helps in a better analysis and view the variables.

 **Adding Global Variables**

 `avga <var_name> <type>` This command lets you manually add global variables with their name and type.

 You use then when a global variables is missed during the analysis. Here `<type>` means the datatype of the variable. Example: `int`, `char`, `long`.

 This manually defines a global variable when Rizin’s automatic analysis did not detect it.

 **Printing Global Variables**

 `avgp <name>` reads memory at the address of the specified global variable and displays its current value.
 >In debug mode → shows the value at the current breakpoint.
 
 >Without debugging → shows the value stored in the binary.
 

 **Changing Variable Type**

 `avgt <var_name> <type>` This command lets you change the data-type of the variable.

 Note: The correct data-type must be used which helps in improving output, cross-reference accuracy and structure recovery.

 There are two modes of display quiet and JSON.
 
 ### Example:
 
 ```
# Ran 'avglt' to check for existing global variables(none were present).
 [0x00001040]> avglt
 name type size address decl_file decl_line decl_col
 ――――――――――――――――――――――――――――――――――――――――――――――――――――
 [0x00001040]> avga test_variable int
 [0x00001040]> avglt
 name          type size address decl_file decl_line decl_col
 ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
 test_variable int   0x4  0x1040 -                -1       -1
 [0x00001040]> avgp test_variable
  int : 0x00001040 = 3644689736
 [0x00001040]> avgt test_variable char
 [0x00001040]> avgp test_variable
  char : 0x00001040 = 'H'
 [0x00001040]> avgn test_variable renamed_variable
 [0x00001040]> avglt
 name             type size address decl_file decl_line decl_col
 ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
 renamed_variable char  0x1  0x1040 -                -1       -1
 [0x00001040]> avgx renamed_variable
 [0x00001040]> avgm renamed_variable
 [0x00001040]> avglt
 name type size address decl_file decl_line decl_col
 ――――――――――――――――――――――――――――――――――――――――――――――――――――
 ```

### What Was Done in This Example

- Ran `avglt` to check for existing global variables (none were present).
- Used `avga test_variable int` to manually create a new global variable of type `int`.
- Ran `avglt` again to confirm the variable was successfully added.
- Used `avgp test_variable` to print the value at that memory location as an `int`.
- Changed the variable type with `avgt test_variable char`.
- Printed the value again using `avgp test_variable`, now interpreted as a `char` (`'H'`), showing how type affects data interpretation.
- Renamed the variable using `avgn test_variable renamed_variable`.
- Ran `avglt` to verify the variable name and updated type were reflected.
- Used `avgx renamed_variable` to check for cross-references (none found since it was manually added).
- Deleted the variable using `avgm renamed_variable`.
- Ran `avglt` one final time to confirm the global variable list was empty again.
