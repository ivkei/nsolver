# nsolver
If you have played the 24-game to sharpen your math skills, you know what this is!  
Long story short, I came across this game when reading [Introduction to Algebra, one of the AoPS books, by Rusczyk](https://artofproblemsolving.com/store/book/intro-algebra),
and clearly, I thought, that it wouldn't take me more than 20 minutes to go through all examples in the book and construct 24 using 4 basic operations out of the following groups of number:  
- 1, 1, 5, 8
- 4, 4, 5, 6
- 1, 5, 5, 5
- 1, 3, 4, 6
- 3, 3, 8, 8
- There's much more!

* Note that all 4 numbers have to be used exactly once, but your imagination is unbound by the signs (just the 4 basic ones).

But at the end it took me 2 hours to solve, and not even all of them!  
So I, like anyone would do in my situation, settled to create a program that will solve not just those for me, but also some groups of the following format:
- 18, 15, 15, 16, 2 to get 1890
- 11, 6, 12, 3, 10 to get 11
- 423847, 973472, 123, 837432, 823974292 to get 703823651
- 1.5, 0.5, 3, 7 to get 0.75
- (And obviously the hardest one) 10, 2 to get 5

## Usage example
```shell
Enter the target number (e.g. 24): 1890
Enter construction values (e.g. 1 5 5 5): 18 15 15 16 2
Your target number is 1890
Your construction values are { 18 15 15 16 2 }
1890 = (18)*15*(15-16/2)
```

Or another one with numbers from the list: 
```shell
Enter the target number (e.g. 24): 703823651
Enter construction values (e.g. 1 5 5 5): 423847 973472 123 837432 823974292
Your target number is 703823651
Your construction values are { 423847 973472 123 837432 823974292 }
703823651 = (423847-973472*123+837432-(823974292))
```

Or one with floats:
```shell
Enter the target number (e.g. 24): 0.75
Enter construction values (e.g. 1 5 5 5): 0.5 1.5 7 8
Your target number is 0.75
Your construction values are { 0.5 1.5 7 8 }
Started!
0.75 = ((0.5)-1.5+7.0)/8.0
```

## Use
I organized everything, probably not in the most optimal way, so that it can be used in any project as a library, if you wish (without the main.cpp).
* Note that if you are using `nsolver::BruteForce`, please don't put numbers higher than 2 for the precision (especially with more than 4 construction numbers), it will be safer for your PC.

### Logging
* To disable logging just define `NSOLVER_DISABLE_LOGGER`.

## Compilation
I just scribbled into the terminal:
```sh
clang++ calc.cpp nsolver.cpp main.cpp -o nsolver
```

## Time complexity for the curious
* It's either O($n^n$) or O($n!$), depends on `precision` in `nsolver::BruteForce`.

## Thanks
* [Introduction to Algebra by Rusczyk](https://artofproblemsolving.com/store/book/intro-algebra) for informing me of this puzzle, that was forever awaiting my program to be made.
