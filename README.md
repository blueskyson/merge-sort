# merge-sort
```
$ gcc merge_sort.c -o merge_sort
$ ./merge_sort
enter amount and max value:
20 100
orig order: 84 70 35 77 48 35 23 4 9 67 88 32 29 92 63 28 92 3 91 67

sorted order: 3 4 9 23 28 29 32 35 35 48 63 67 67 70 77 84 88 91 92 92
```

# quick-sort
```
$ gcc quick_sort.c -o quick_sort
$ ./quick_sort
please input amounts of number and max value
20 100
orig order: 72  58  23   4  91  31  11  63  64  26  31  99  62  60  66  52  97  61  16   6 
new order:  4   6  11  16  23  26  31  31  52  58  60  61  62  63  64  66  72  91  97  99 
```

# heap-sort
```
$ gcc heap_sort.c -o heap_sort
$ ./heap_sort
please input amount and max value:20 500
orig order:
  176  308   53  101  181   97  492   35  290  328  273  378  292  230  335  199  489  244  228  416
sorted order:
   35   53   97  101  176  181  199  228  230  244  273  290  292  308  328  335  378  416  489  492
```

# radix-sort
```
$ gcc radix_sort.c -o radix_sort
$ ./radix_sort
Please input amount and max value: 20 500
orig order:
 251 236 75 231 348 355 305 251 263 121 381 473 312 438 246 435 18 59 190 220

sorted order:
 18 59 75 121 190 220 231 236 246 251 251 263 305 312 348 355 381 435 438 473
```

# external 2-way merge sort

Change the value the macro `PAGE_SIZE` to control the size of one page, 10 numbers per page by default.

```
$ g++ 2-way-merge-sort.cpp -o 2-way-merge-sort
$ ./2-way-merge-sort sample_input.txt output.txt
create tmp directory
--- PASS 0 ---
save tmp file: tmp/0_0
save tmp file: tmp/0_1
save tmp file: tmp/0_2
--- PASS 1 ---
save temporary file: tmp/1_0
remove temporary file: tmp/0_0
remove temporary file: tmp/0_1
rename tmp/0_2 as tmp/1_1
--- PASS 2 ---
save temporary file: tmp/2_0
remove temporary file: tmp/1_0
remove temporary file: tmp/1_1
rename tmp/2_0 as output.txt
remove temporary directory
```