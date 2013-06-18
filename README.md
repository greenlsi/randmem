Random Memory Benchmark Readme file
===================================

RandMem is a random memory benchmark originally developed by Roy Longbottom
(http://www.roylongbottom.org.uk/). This benchmark has been modified and some
features have been added to it in order to develop some memory power/energy
models for enterprise servers.

The bechmark supports various architectures (Linux 32 bit, Linux 64bit and
Solaris). It has been tested on Ubuntu 32bit, CentOS 6.4 and Solaris 10.

Feel free to contribute to it, but bear in mind that the original author would like 
any money ever made from this benchmark go to charity.

Installation instructions
-------------------------

To install the benchmark, just run the makefile:

For solaris systems
    $ make solaris

For 32 bit systems
    $ make 32bit 

For 64bit systems (default)
    $ make all

Once compiled, just run ./randmem.out
If you need some help:
    $ ./randmem.out --help

More about RandMem
------------------

RandMem can be used to stress the system memory in some different ways. 
The benchmark executes with the following parameters:

* pattern: test to run, can be 'serial' or 'random'
* data: type of data to run, can be 'integer' or 'intfp'
* access: type of access to memory, can be 'r' or 'rw'
* memsize: memory size in GB to use. Note that the maximum amount of per-process
  memory in a Linux/Solaris server is 2GB
* blocksize: maximum size of each memory block (in KB). This indicates the
  malloc size of the benchmark 
* runtime: minimum time for benchmark to run (in secs)
* numexecs: number of times the benchmark is executed

On startup, the benchmark will try to allocate as much memory as asked by the
user ('memsize') in chunks of size 'blocksize'. If it cannot, it will allocate
the maximum amount of memory possible.

If you need more than 2GB of memory, launch multiple instances of randmem 

