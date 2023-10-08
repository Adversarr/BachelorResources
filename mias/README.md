# MInisys ASsembler

To build:

```
xmake b
```

To run:

```
xmake run mias
```

options:

1. `-c, -coe`: Generate COE files,
2. `-i ...`: Specifies input file, 0 for stdin, default: 0
3. `-o ...`: Specifies output file, 1 for stdout, default: 1
4. `-m`: Specifies Memory size in kb, default: 64
5. `-v, -verbose`: Verbose Mode
6. `-f, -fill`, fill with zero in generated binary code.

Demo:

```
xmake run mias  -i $(pwd)/testcpu.s -c -o out.txt -f
```

