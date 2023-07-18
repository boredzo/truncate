# truncate
## A tool for creating empty files

This tool uses the POSIX `ftruncate` function to set the length of a file.

- If the file exists and is longer than that, it will be truncated (bytes after that length cut off).
- If the file exists and is shorter than that, it will be extended and the new bytes zero-filled. (Whether this actually consists of writing zero-bytes to disk is dependent on your operating system's implementation.)
- If the file doesn't already exist, it will be created, then extended to the desired length.

This is a very handy way to instantly create raw disk images for emulators. You can do things like `truncate 1G oneBEELLIONbytes.img` to create a blank disk image that you can then format with either host tools (like `newfs_hfs` or `newfs_msdos`) or guest tools (like the built-in Initialize alert in classic Mac OS).

Sizes can be specified as either whole numbers of bytes or whole numbers followed by a suffix:

<dl>
<dt>B (or no suffix)</dt>
<dd>Bytes</dd>
<dt>S</dt>
<dd>Sectors of 512 bytes each)</dd>
<dt>K</dt>
<dd>Kibibytes (KiB) of 1024 bytes each</dd>
<dt>M</dt>
<dd>Mebibytes (MiB): 1024**2 = 1048576 bytes</dd>
<dt>G</dt>
<dd>Gibibytes (GiB): 1024**3 = >1 billion bytes</dd>
<dt>T</dt>
<dd>Tebibytes (TiB): 1024**4 = >1 triillion bytes</dd>
<dt>P</dt>
<dd>Pebibytes (PiB): 1024**5 = 1024 tebibytes</dd>
<dt>E</dt>
<dd>Exbibytes (EiB): 1024**6 = 1048576 tebibytes</dd>
<dt>Z</dt>
<dd>Zebibytes (ZiB): 1024**7</dd>
<dt>Y</dt>
<dd>Yobibytes (YiB): 1024**8</dd>
</dl>

### Compatibility
This works on macOS. It should work on, or at least be portable to, Linux-based operating systems.