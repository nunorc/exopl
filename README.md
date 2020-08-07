
# exopl

**A work in progress..**

A minimalistic tool to illustrate the use of the
[Y-Space](http://y-space.pw/) API in a C++ setting.

The `exopl` tool can be used to query the API and perform different
operations, specified using a command.
The goal is to build sequence of commands to perform more complex
operations, combined with some popular command line tools,
where the output of an operation is passed on as input to the
next using pipes.

To build the tool just clone the repository and:

    $ mkdir build ; cd build
	$ cmake ..
    $ make

[cmake](https://cmake.org/),
[libcurl](https://curl.haxx.se/libcurl/) and 
[jsoncpp](https://github.com/open-source-parsers/jsoncpp) are
required. The `exopl` binary should be available in the build
directory:

	$ ./exopl 

	Usage: exopl <command> [expr]

	Commands:
	 list	  list all exoplanets
	 filter	  filter exoplanets based on a given expreesion
	 select	  select parameters when exporting based on a given expression
	 as_txt	  print as text
	 as_csv	  print as CSV

For example to get a count of exoplanets by discovery method using a
combination of `exopl` and typical bash commands:

	$ exopl list | exopl select discoverymethod | exopl as_txt | grep -v '^$' | sort | uniq -c
	   1 discoverymethod: Astrometry
	   1 discoverymethod: Disk Kinematics
	  16 discoverymethod: Eclipse Timing Variations
	  50 discoverymethod: Imaging
	  96 discoverymethod: Microlensing
	   6 discoverymethod: Orbital Brightness Modulation
	   7 discoverymethod: Pulsar Timing
	   2 discoverymethod: Pulsation Timing Variations
	 810 discoverymethod: Radial Velocity
	3187 discoverymethod: Transit
	  21 discoverymethod: Transit Timing Variations

Or for example to get the count of exoplanets discovered by year with an orbital period
greater that 10 days:

	$ exopl list | exopl filter 'pl_orbper>10' | exopl select disc_year | exopl as_txt | grep -v '^$' | sort | uniq -c
	   1 disc_year: 1989
	   2 disc_year: 1992
	   1 disc_year: 1994
	   4 disc_year: 1996
	   1 disc_year: 1997
	   4 disc_year: 1998
	  11 disc_year: 1999
	  13 disc_year: 2000
	  11 disc_year: 2001
	  (...)

It is also useful to create CVS files that can later be imported in other programs.
For example to create a CSV file with a list of planets discovered after 2010 that contains
the planet name and the orbital period:

	$ exopl list | exopl filter 'disc_year>2000' | exopl select pl_name,pl_orbper | exopl as_csv > data.csv
	$ cat data.csv 
	11_com_b,11 Com b,326.02999999999997
	11_umi_b,11 UMi b,516.21996999999999
	14_and_b,14 And b,185.84
	14_her_b,14 Her b,1773.40002
	18_del_b,18 Del b,993.29999999999995
	(...)
