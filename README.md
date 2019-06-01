# Clint - Simple linter writen in C

This simple linter can convert spaces to tabs, and tabs to spaces!

<br>

## Install

```
git clone https://github.com/WestleyR/clint
cd clint/
make
sudo make install
```

<br>

## Usage

To convert tabs to spaces in this go file:

```bash
$ clint -s hello.go
```

*Note: This will **NOT** mess up your gofmt assied from changing the tabs.*

<br>

To convert spaces to tabs in this file:

```bash
$ clint -t hello.c
```

Again, this wont screw-up any formatting you have.

You can also add the `-v, --verbose` flag to be more verbose:

```bash
$ clint -vs hello.go 
VERBOSE: Converting tabs to 4 spaces.
Done: hello.go
VERBOSE: Total tabs replaced: 519
```

<br>
