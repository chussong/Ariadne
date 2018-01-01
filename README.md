# Ariadne
A simple program for finding the best route between multiple time-limited sites.
While intended to be used for Pokemon Go raids, it will solve any 
time-constrained traveling salesperson problem with the expected formatting.  

Copyright 2018 Charles Hussong  

Project homepage:	https://github.com/chussong/Ariadne  
Contact email:		charles.hussong@gmail.com  

## License

Ariadne is open source software licensed under the Apache License 2.0. See the
included LICENSE file for details.  

## Installation

To compile, get a terminal in this directory and type "make". If you have clang
available everything will ideally be handled automatically; if you'd rather use
another compiler, edit the top of the Makefile.  

Mac users can get a C++ compiler by running xcode-select --install to get the 
Command Line Tools.  

Ariadne uses Boost for multiplatform filesystem interactions; most systems have
Boost pre-installed, but you may have to install it separately. This dependency
could be eliminated by using C++17, but many default compiler installations do
not yet support this.  

## Usage

Ariadne expects lists of raids in the following format:  

name, decimal longitude, decimal latitude, expiration time  

Each raid should be on its own line, and each entry for a raid shuld be 
separated by a comma. The easiest way to produce this is probably to work in a 
spreadsheet editor and save the output as a CSV, in which case each raid is a 
row, with the first cell as the raid's name, second cell as its longitude, and 
so on.  

Even though I had a CSV in mind when implementing this, Ariadne works on plain 
text files as well; see the two provided "testraids" files for working examples.  

Expiration times are supported in both 12- and 24-hour formats. In the case of 
12-hour times, do not include the AM or PM; Ariadne will infer that you mean the
soonest future time with that name. Because of this inference, do not provide
the date at all; it will likely cause the program to throw an invalid\_argument
exception and crash.  

Note that the algorithm used for routing is quite naive and does not attempt to
be efficient. For the expected application, only small numbers of sites need to
be considered at a time, so the brute force approach should be perfectly 
sufficient. Just make sure you delete the raids you no longer need to consider.
In particular, any raids which have already expired will be interpreted as 
taking place 12 or 24 hours in the future, so they will still be included in
routing just like the non-expired ones.  
