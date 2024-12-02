# Rz-pipe

The rz-pipe module permits interacting with Rizin instances in different methods:

* spawn pipes (rizin -0)
* http queries (cloud friendly)
* tcp socket (rizin -c)

| Language | pipe | spawn | async | http | tcp | rap | json |
|----------|------|-------|-------|------|-----|-----|------|
| Python   | x    | x     | -     | x    | x   | x   | x    |
| Haskell  | x    | x     | -     | x    | -   | -   | x    |
| OCaml    | x    | x     | -     | x    | -   | -   | x    |
| Rust     | x    | x     | x     | x    | -   | -   | x    |

## Examples

### Python

```shell
$ pip install rzpipe
```

```python
import rzpipe

rz = rzpipe.open("/bin/ls")
rz.cmd('aa')
print(rz.cmd("afl"))
print(rz.cmdj("aflj"))  # evaluates JSONs and returns an object
```

### Haskell

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

### OCaml

```ocaml
let result = Rz.with_command ~cmd:"/j chown" "/bin/ls"
Printf.printf "Rizin output is: %s" result
```

### Rust

```rust
#[macro_use]
extern crate rzpipe;
extern crate serde_json;
use rzpipe::RzPipe;
fn main() {
  let path = Some("/bin/ls".to_owned());
  let mut rzp = open_pipe!(path).unwrap();
  println!("{}", rzp.cmd("?e Hello World").unwrap());
  if let Ok(json) = rzp.cmdj("ij") {
    println!("{}", serde_json::to_string_pretty(&json).unwrap());
    println!("ARCH {}", json["bin"]["arch"]);
  }
  rzp.close();
}
```

### Ruby

```ruby
require './rzpipe'

begin
  rzp = RzPipe.new
rescue Exception => e
  rzp = RzPipe.new '/bin/ls'
end
  puts rzp.cmd 'a'
  puts rzp.cmd 'pd 10 main'
  rzp.quit
```
