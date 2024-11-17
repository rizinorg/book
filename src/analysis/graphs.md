# Graph commands

When analyzing data it is usually handy to have different ways to represent it in order to get new perspectives to
allow the analyst to understand how different parts of the program interact.

Representing basic block edges, function calls, string references as graphs show a very clear view of this information.

Rizin supports various types of graph available through commands starting with `ag`:

```
[0x00005000]> ag?
Usage: ag<?>   # Analysis graph commands
| aga <format>=ascii      # Data reference graph
| agA <format>=ascii      # Global data references graph
| agc <format>=ascii      # Function callgraph
| agC <format>=ascii      # Global callgraph
| agCi <format>=ascii     # Inter-procedual control flow graph
| agF <format>=ascii      # Control flow graph (without calls)
| agf <format>=ascii      # Basic blocks function graph
| agi <format>=ascii      # Imports graph
| agr <format>=ascii      # References graph
| agR <format>=ascii      # Global references graph
| ags <format>=ascii      # Normal graph
| agl <format>=ascii      # Line graph
| agx <format>=ascii      # Cross-references graph
| agI <format>=ascii      # RzIL graph of the instruction at the current offset.
| agg <format>=ascii      # Custom graph
| ag-                     # Clear the custom graph
| agn[-]                  # Managing custom graph nodes
| age[-]                  # Managing custom graph edges
| agw <graphtype>=dataref <path> [-global] # Write to path or display graph image (see graph.gv.format)

Formats:
| ascii       # Ascii art
| cmd         # rizin commands
| dot         # Graphviz dot
| gml         # Graph Modelling Language
| json        # json
| json_disasm # json formatted disassembly
| sdb         # SDB key-value
| interactive # Interactive ascii art
```

The structure of the commands is as follows: `ag <graph type> <output format>`.

For example, `agi dot` displays the imports graph in dot format, while `agg json`
outputs the custom graph in JSON format.

Here's a short description for every output format available:

### Ascii Art (e.g. `agf`)

Displays the graph directly to stdout using ASCII art to represent blocks and edges.

_Warning: displaying large graphs directly to stdout might prove to be computationally expensive and will make Rizin
not responsive for some time. In case of doubt, prefer using the interactive view (explained below)._

### Interactive Ascii Art (e.g. `agf interactive`)

Displays the ASCII graph in an interactive view similar to `VV` which allows to move the screen, zoom in / zoom out, ...

### Graphviz dot (e.g. `agf dot`)

Prints the dot source code representing the graph, which can be interpreted by programs such as
[graphviz](https://graphviz.gitlab.io/download/) or online viewers like [webgraphviz](http://www.webgraphviz.com/).

### JSON (e.g. `agf json`)

Prints a JSON string representing the graph.

- In the case of the `f` format (basic blocks of function), it will have detailed information about the function and
  will also contain the disassembly of the function (use `J` format for the formatted disassembly).
- In all other cases, it will only have basic information about the nodes of the graph (id, title, body, and edges).

### Graph Modelling Language (e.g. `agf gml`)

Prints the GML source code representing the graph, which can be interpreted by programs such as
[yEd](https://www.yworks.com/products/yed/download)

### SDB key-value (e.g. `agf sdb`)

Prints key-value strings representing the graph that was stored by sdb (Rizin's string database).

### Rizin custom graph commands (e.g. `agg`)

Prints rizin commands that would recreate the desired graph. The commands to construct the graph are
`agn [title] [body]` to add a node and `age [title1] [title2]` to add an edge.
The `[body]` field can be expressed in base64 to include special formatting (such as newlines).

To easily execute the printed commands, it is possible to prepend a dot to the command (`.agg`).

### Web / image	(e.g. `agw`)

Rizin will convert the graph to dot format, use the `dot` program to convert it to a `.gif` image and then try to find
an already installed viewer on your system (`xdg-open`, `open`, ...) and display the graph there.

The extension of the output image can be set with the `graph.gv.format` config variable. Available extensions are
`png, jpg, pdf, ps, svg, json`.

_Note: for particularly large graphs, the most recommended extension is `svg` as it will produce images of much
smaller size_
