# des-3des
A small implementation of DES and 3DES using C++
Confirmed to work on Windows 7 64-bit OS. I cannot guarantee anything else.

Usage instructions:
All input needs to be in hexadecimal.
DES accepts only keys of length 16.
3DES accepts only keys of length 32.
The length of input cipher text must be divisible by 16.

"-h" display help message

"-t"  unit test run

"-e" <key> <msg>  encrypt using DES

"-e3" <key> <msg> encrypt using 3DES

"-d" <key> <msg>  decrypt using DES

"-d3" <key> <msg> decrypt using 3DES

Examples:

-t

-e ABCDEF1234567890 A1B2C3D4E5F6A890

-d3 ABCDEF12345678901840EABC0173B7B1 A1B2C3D4E5F6A890

Note:
Please don't use this code for anything serious, it is not secure.
