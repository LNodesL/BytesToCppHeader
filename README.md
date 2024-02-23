# BytesToCppHeader
BTCH is a small utility tool that will take any file (any type) and convert to an array of bytes &amp; save it to a new C++ formatted header file, for inclusion in another program.

## Compiling Example
```
g++ main.cpp -o BTCH -static
```

## Usage Example
```
./BTCH original.exe payloadData.h
```
- This will then save a new file to the current directory 'payloadData.h' which holds the bytes array of data.
- BTCH has a quick test function that then loads the bytes back to a file and creates TEST-* where -* is your original filename (ex: TEST-original.exe) so you can ensure no data loss.

## Notes
This is a simple tool that does not handle encryption/decryption of original data. It is only intended for taking a file and converting to bytes array and creating a header file dynamically.
