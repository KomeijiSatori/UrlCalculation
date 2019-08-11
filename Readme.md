# Introduction
This project aims at calculating top 100 urls that appear most in a 100GB file and the corresponding count.

# Assumptions
It is assumed that the program is run on a single machine with 1GB memory.

The url is all valid and has no get parameters, and the max length of a single url will not exceed 2048.(For IE explorer, it will not render a page if the url length exceeds 2048)
In a corner case, the 100GB file does not contain a single url, just a part of it, it will not make sense, so the length limit of a url is essential.
In other words, It should be guaranteed that we can safely load a url without exceeding the memory limit. In our case, We set max length to be 256, which is a reasonable number.

# Usage
## Compile, prepare and run
prepare data for demo
```
python generate.py
```
compile and run
```
bash prepare.sh
./main
```
## Compile, prepare and test
```
bash prepare.sh
./test
```

# The Implementation
We solve the problem in three parts. 

The first part is partition, it divide the origin 100GB file into several files, urls with same address will be partitioned into same file, although other urls may be put into the same file.

The second part is count, it will calculate every url's appearance in each partition file, then save the result to file.

The third part is getting topK, it will scan every file and calculate the topK urls in memory, then put the result to file.

## Partition
In order to make full use of our 1GB memory, we can equally divide the 100GB file into 100 parts, and each part has 1GB urls. 
Meanwhile, we should guarantee urls with same address should be in the same file. This makes partition quite difficult, since we may not equally partition the 100GB file.
It depends on our hash function that decides which partiton file the url should belong to. If the hash function is poor, one file may be 10GB and another may be 100M, and loading the 10GB file is likely to exceed the memory while counting.

So, in order to be safe, and not creating too many files, we decide to set partition number 256. We use hash function calculating the total sum of each character's square mod 256. After some experiments, we find this function can partition urls 
almost equally.

## Count
After partition, we can handle urls in a single partition file with our 1GB memory, then we use a hash map to store the url and its count, then create a result file for each partition.

## TopK
At last, we maintain a heap to store the topK occurrence of urls. We go through each file and compare the occurrence one by one, then at last we get the topK, then store to disk. 

# Experiment
We create a file of size 1GB, and limit out memory to 10MB by setting `MAX_MEMORY` in `consts.h` to (1 << 30) / 100, and the total runtime is 196 seconds.

Using top, we can see the physical memory usage is below 10MB, which means our program manages the memory well. The result is shown below.

| PID   | USER   | PR | NI | VIRT  | RES  | SHR  | S | %CPU  | %MEM | TIME+   | COMMAND |
| :---- | :----- | :- | :--| :---- | :--- | :--- | :-| :---- | :--- | :------ | :------ |
| 17470 | satori | 20 | 0  | 18952 | 7172 | 3176 | R | 100.0 | 0.0  | 0:27.80 | main    |
