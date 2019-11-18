# Split BAM file by tag

Demultiplex paired end reads by fixed position barcodes. This library requires Boost C++ libraries and a compiler supporting C++11. This software is work in progress.

## Installation

This software has successfully compiled on:

* GCC 9.3.0
* clang 6.0.0

To compile the program:

```
git clone https://github.com/Shians/bam-tag-split.git
cd bam-tag-split
cmake .
make
```

The executable binaries will be in the `dist` folder.

## Usage

Basic usage:

```
dist/bam-tag-split  -i input.bam -t RG // split samples by RG tag
```

See `bam-tag-split --help` for details.

BAM files will be created for each unique tag found under the specified 2-character tag. By default the reads that are empty in the specified tag are not output, they can be output into an undetermined BAM file using `--all`.

## Warnings

* On MacOS the number of files that can be opened by `terminal` is limited to 256, this program will fail silently and output fewer than expected files.
    * Easiest way to fix this is by installing iTerm2 and running this program inside. **NOTE** iTerm versions after 3.2.9 have set the file limit to match the macOS default of 256. For more than 128 barcodes, you will need to use an older version from [here](https://www.iterm2.com/downloads.html).
    * Check your files open limit using `ulimit -n`.
* This is still a work in progress, please report any bugs you find using the issues tab.
