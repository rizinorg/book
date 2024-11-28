# SDB

SDB stands for String DataBase. It's a simple key-value database that only operates with strings created by pancake.
It is used in many parts of rizin to have a disk and in-memory database which is small and fast to manage using it
as a hashtable on steroids.

SDB is a simple string key/value database based on djb’s cdb disk storage and supports JSON and arrays introspection.

SDB supports:

- namespaces (multiple sdb paths)
- atomic database sync (never corrupted)
- bindings for vala, luvit, newlisp and nodejs
- commandline frontend for sdb databases
- memcache client and server with sdb backend
- arrays support (syntax sugar)
- json parser/getter


## Usage example

Let's create a database!

```
$ sdb d hello=world
$ sdb d hello
world
```

Using arrays:

```
$ sdb - '[]list=1,2' '[0]list' '[0]list=foo' '[]list' '[+1]list=bar'
1
foo
2
foo
bar
2
```

Let's play with json:

```
$ sdb d g='{"foo":1,"bar":{"cow":3}}'
$ sdb d g?bar.cow
3
$ sdb - user='{"id":123}' user?id=99 user?id
99
```

Using the command line without any disk database:

```
$ sdb - foo=bar foo a=3 +a -a
bar
4
3

$ sdb -
foo=bar
foo
bar
a=3
+a
4
-a
3
```

Remove the database

```
$ rm -f d
```

## So what ?

So, you can now do this inside your rizin sessions!

Let's take a simple binary [hello_world](https://github.com/rizinorg/book/tree/master/examples/hello_world),
and check what is already _sdbized_.

```
$ rizin -A hello_world
[0x00001100]> k ** # list namespaces under analysis
analysis
bin
debug
syscall

[0x00001100]> k bin/**
cur
fd.3
```

---

## More Examples

List namespaces

```
k **
```

List sub-namespaces

```
k analysis/**
```

List keys

```
k *
k analysis/*
```

Set a key

```
k foo=bar
```

Get the value of a key

```
k foo
```

List all syscalls

```
k syscall/*~^0x
```

List all comments

```
k analysis/meta/*~.C.
```

Show a comment at given offset:

```
k %analysis/meta/[1]meta.C.0x100005000
```
