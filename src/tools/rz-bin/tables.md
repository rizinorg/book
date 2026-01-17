# Table Output and Queries

Rizin generates tables for certain commands, such as `aflt`, `is`, `izz`, and `il`, when they are executed on a file. These commands return structured data in the form of tables.

The table output is used to process and display data. Using the table query syntax, users can sort rows, filter (grep) data, select specific columns or rows, paginate results, and limit the output. Tables can also be printed in different output formats such as CSV and JSON, or displayed in various textual layouts, including with borders and headers, with headers only, or without headers.

## Table Command Syntax

In Rizin, the help command for the table query syntax is `:?`.

```text
Usage:
<command>[:<table_spec>[:<table_spec>...]][:<output_spec>]
```
Note: Table specifiers are applied from left to right. Output format specifiers must be specified at the end.  

Table format specifiers `(<table_spec>)`:
```
| <col>/sort/rev            # Sort table by column <col> in reverse order.
| <col>/sortlen/rev         # Sort table by column <col> length in reverse order.
| <col>/cols[/<col2>[/<col3>...]] # Show only specified columns in the table.
| <col>                     # Show only column <col> (it must not have the same name as an output format specifier).
| <col>/gt/<val>            # Grep rows where column <col> is greater than <val>.
| <col>/ge/<val>            # Grep rows where column <col> is greater than or equal to <val>.
| <col>/lt/<val>            # Grep rows where column <col> is less than <val>.
| <col>/le/<val>            # Grep rows where column <col> is less than or equal to <val>.
| <col>/eq/<val>            # Grep rows where column <col> is equal to <val>.
| <col>/ne/<val>            # Grep rows where column <col> is not equal to <val>.
| <col|*>/uniq              # Only get the first row where column <col> or all columns are unique.
| */page/<n_page>/<page_size> # Show <page_size> rows starting from the page number <n_page>.
| */head/<n_rows>           # Show the first <n_rows> rows.
| */tail/<n_rows>           # Show the last <n_rows> rows.
| <col>/str/<value>         # Grep rows where string <value> is a substring of column <col>.
| <col>/strlen/<value>      # Grep rows where the length of column <col> is <value>.
| <col>/minlen/<value>      # Grep rows where the length of column <col> is greater than <value>.
| <col>/maxlen/<value>      # Grep rows where the length of column <col> is less than <value>.
| <col>/sum/<value>         # Sum all the values of column <col>.
```
Note: The `/sort` and `/sortlen` commands sort values in increasing order by default. Adding `/rev` reverses the order of the output.

Example:

`aflt:nbbs/sort` sorts the results in increasing order of `nbbs` values.

`aflt:nbbs/sort/rev` sorts the results in decreasing order of `nbbs` values.

Output format specifiers `(<output_spec>)`:
```
| csv    # Print the table in CSV format.
| json   # Print the table in JSON format.
| fancy  # Print the table in a nice form with borders and headers.
| simple # Print the table in a simple form, only with headers.
| quiet  # Print the table in a simple form, without headers.
```
Some examples which give a general overview of how to use.

---

### Example 1: Filter, sort, and format analyzed functions

```
aflt:addr/cols/name/nbbs:size/gt/32:nbbs/gt/1:nbbs/lt/10:nbbs/sort/rev:fancy
```
This command selects the `addr`, `name`, and `nbbs` columns. It filters functions whose size is greater than 32 bytes and keeps only those functions whose number of basic blocks (`nbbs`) is greater than 1 and less than 10. The results are displayed in reverse order of nbbs using the fancy table format.

### Example 2: Paginate strings, filter by length, and export as CSV
```
izz:string/minlen/8:length/sort/rev:*/page/0/15:csv
```
This command filters strings whose length is greater than 8 characters and sorts them by length in reverse order. It then paginates the output to show only the first page containing 15 rows and prints the result in CSV format.

### Example 3: Combine uniqueness, filtering, and JSON output for symbols
```
is:name/uniq:addr/gt/0x1000:name/str/init:addr/sort:json
```
This command keeps only the first occurrence of each unique symbol name. It filters symbols whose address is greater than `0x1000` and whose name contains the substring `init`. The results are sorted in increasing order.