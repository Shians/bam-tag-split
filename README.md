# Tools for working with BAM file tags

Utilities for working with tags in BAM files. This library requires Boost C++ libraries and a compiler supporting C++11. This software is work in progress, bug reports and feature requests welcomed.

## Installation

This software has successfully compiled on:

* GCC 9.3.0
* clang 6.0.0

To compile the program:

```
git clone https://github.com/Shians/bam-tag-tools.git
cd bam-tag-tools
cmake .
make
```

The executable binaries will be in the `dist` folder to install it to the default path run

```
make install
```

or for a custom path

```
cmake -DCMAKE_INSTALL_PREFIX=/custom/path .
make install
```

The executables will be created under the `bin` folder at the specified path.

## Usage

Basic usage:

```
bam-tag-split  -i input.bam -t RG // split samples by RG tag
bam-tag-extract  -i input.bam -o output.tsv -t RG // split samples by RG tag
```

See `bam-tag-split --help` and `bam-tag-extract --help` for details.

For `bam-tag-split` BAM files will be created for each unique tag found under the specified 2-character tag. By default the reads that are empty in the specified tag are not output, they can be output into an undetermined BAM file using `--all`.

For `bam-tag-extract` a tab-separated file containing two columns will be created with columns `read_name` and the name of the tag. (e.g. `read_name RG`)

## Warnings

* On MacOS the number of files that can be opened by `terminal` is limited to 256, this program will fail silently and output fewer than expected files.
    * Easiest way to fix this is by installing iTerm2 and running this program inside. **NOTE** iTerm versions after 3.2.9 have set the file limit to match the macOS default of 256. For more than 128 barcodes, you will need to use an older version from [here](https://www.iterm2.com/downloads.html).
    * Check your files open limit using `ulimit -n`.
* This is still a work in progress, please report any bugs you find using the issues tab.
