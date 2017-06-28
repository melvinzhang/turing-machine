# Turing Machine Emulator

A Turing Machine emulator written in C++ 11

## Building the binary

You'll need Make and g++ to compile the source code. Running

```
make
```

will produce the binary `tm`

## Command line options

The program takes two optional arguments. 

The first is the maximum number of steps to execute the machine.

The second the frames per second of the animation. A setting of zero means there is no animation.

The default is 1000 steps with no animation.

## Running the first program in Turing 1936

```
cat s3p1.tm | ./tm 30 5
```

The input is read from stdin. The above runs the program that prints `010101...` for 30 steps at 5 frames per second.

![Running s3p1.tm](http://melvinzh.sdf.org/s3p1e.gif)

## Running the second program in Turing 1936
```
cat s3p2.tm | ./tm 200 10
```

The above runs the program that prints `0010110111011110111110...` for 200 steps at 10 frames per second.

![Running s3p2.tm](http://melvinzh.sdf.org/s3p2.gif)

## Running the tests
```
make tests
```

This runs all the machines in the folder and compares the result with the output files.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
