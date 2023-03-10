# MacDirtyCow

Example of CVE-2022-46689 aka MacDirtyCow.

## What?

MacDirtyCow is a privilege escalation vulnerability in macOS, similar to the Dirty COW vulnerability in Linux. The vulnerability resides in the copy-on-write (COW) mechanism used by macOS's XNU kernel. The vulnerability allows an attacker to modify read-only root-owned files, which could lead to an attacker gaining root privileges on the affected system.

The vulnerability is caused by a race condition in the way macOS's XNU kernel handles copy-on-write (COW) operations on memory pages. When a memory page is marked read-only, but also marked as copy-on-write, the kernel will create a new copy of the page when a write operation is performed on the page. However, there is a small window of time between the read-only page being checked and the new copy being created where an attacker could modify the page in memory, effectively bypassing the read-only restriction.

## PoC

This code (`poc.c`) opens a file specified as a command line argument and maps it into memory using mmap(). It then creates a copy of the file and modifies the memory-mapped copy of the file by filling it with the character 'A'. Finally, the original file is overwritten with the modified copy of the file.
