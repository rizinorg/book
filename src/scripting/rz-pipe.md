# Rz-pipe

The rz-pipe module permits interacting with rizin instances in different methods:

* spawn pipes (rizin -0)
* http queries (cloud friendly)
* tcp socket (rizin -c)

```
         pipe spawn async http tcp rap json
python    x     x     -    x    x    x   x
haskell   x     x     -    x    -    -   x
ocaml     x     x     -    x    -    -   x
```

Examples
========

Python
------

```
$ pip install rz-pipe
```

```python
import rzpipe

rz = rz-pipe.open("/bin/ls")
rz.cmd('aa')
print(rz.cmd("afl"))
print(rz.cmdj("aflj"))  # evaluates JSONs and returns an object
```

Haskell
-------
```haskell
import RzPipe
import qualified Data.ByteString.Lazy as L

showMainFunction ctx = do
  cmd ctx "s main"
  L.putStr =<< cmd ctx "pD `fl $$`"

main = do
  -- Run rizin locally
  open "/bin/ls" >>= showMainFunction
  -- Connect to rizin via HTTP (e.g. if "rizin -qc=h /bin/ls" is running)
  open "http://127.0.0.1:9090" >>= showMainFunction
```

OCaml
-----
```ocaml
let result = Rz.with_command ~cmd:"/j chown" "/bin/ls"
Printf.printf "Rizin output is: %s" result
```
