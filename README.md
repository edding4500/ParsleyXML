# ParsleyXML
An xml parser library in C++ that uses a waaaay too complicated state machine for tokenizing and generates an AST for the parsed xml.

## Building

```bash
make
```
lul

## Demo

There is a demo program in the demo folder that can be used to parse xml files and print the AST to stdout.

```bash
cd demo
make
cd build
./demo
```

## Visitors

The AST can be traversed using visitors. There are two visitors included in the library: `PrintVisitor` and `XMLWriterVisitor`. The `PrintVisitor` prints the AST to stdout and the `XMLWriterVisitor` writes the AST to an xml file.
Own visitors can be defined by inheriting from the `AstVisitor` class and implementing the `visit` methods for the different AST nodes.