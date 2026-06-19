# Introduction

This is a book about [Rizin](https://rizin.re) reverse engineering framework and it's originally
based on the [radare2 book](https://github.com/radareorg/radare2book)

Check the Github site to add new contents or fix typos:

* Github: [https://github.com/rizinorg/book](https://github.com/rizinorg/book)
* Online: [https://book.rizin.re/](https://book.rizin.re)

## Offline

For offline use you need to fetch the [Quarto](https://quarto.org) tool and run the build locally:
```sh
quarto preview
```
It will open your Web-browser pointing to `http://localhost:[some port]` to read it offline.

Another option is to render the book to any of the formats that are supported by Quarto:
```sh
quarto render . --to pdf --toc
```

## Content additions

New documentation should focus on the value it provides to the user.
The examples and topics should cover common use cases and problems people try to solve,
like "Command X solves problem Y for you."
Figuring out the common use cases is part of contributing to the book.

## AI guidelines

It is not allowed to generate documentation solely with AI.
New contributions must be correct and cannot contain _any_ hallucinations.
Beginners should first use a module’s API or commands by experimenting with it,
then write the documentation.

AI can be used to get an initial overview and an idea of where to start experimenting.
