#ifndef CONSTS_H
#define CONSTS_H

#include <string>
using namespace std;

// the top k occurrence
int const TOPK = 100;
// assume the max length of a single url
int const MAX_URL_LENGTH = 256;
// assume the max memory usage of the program
int const MAX_MEMORY = (1 << 30) / 100;
// the partition number the original file should be divided
int const PARTITION_NUMBER = 256;
// the input file directory
string const INPUT_DIR = "input/input.txt";
// the output file directory
string const OUTPUT_DIR = "output/output.txt";
// the partition result directory
string const PARTITION_DIR = "partitions/";
// the count result directory
string const COUNT_DIR = "counts/";

#endif