# karambabel
The repository for the test task for Karamba Bel

Here's the test coding problem for you to solve:

1. Write Linux command-line utility that:
 accepts multiple file paths as arguments,
 calculates their cryptographic hashes (please, use strong hasher!) and
 using hashes, finds duplicate files (differently named/located files that have identical content),
 finally, it should output file paths of all duplicates to console.

Note: Utility must be as RAM/CPU effective as possible, be written in plain C. However it is allowed to use standard helpers libraries that are commonly part of Linux distribution: libc, libcrypt.

- Also create Linux helper script (bash) that will recursively find all files from given root path and will call that utility, specifying all found files in its command line. Finally, script should analyze the output of utility and print total number of duplicate files found.
