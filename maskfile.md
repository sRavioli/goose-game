# Tasks

> Useful project tasks.

## build

```bash
mkdir -p bin
gcc $(find . -regex '.*/.*\.\(c\)$') -o bin/main
echo "Built  main.c"
```

```pwsh
[System.IO.Directory]::CreateDirectory("./bin/")
gcc $(Get-ChildItem -Recurse -Path . -Filter *.c -Exclude .\tests\).fullname `
    -o ./bin/main.exe
```

## run

> Build the given files and output to `bin/` folder, then execute it.

Searches for `src/main.c` and builds it.

```bash
mask build && ./bin/main
```
