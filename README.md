# Algo Projec 1

Since we only care about the execution time of `COMPARE()`, the solution is to call `COMPARE()` as less as possible, yet achieving our goal, which is targeting and sorting the first `k` largest numbers in a given set of `n` numbers

### Concept of the solution:

1. Iterate through `n` numbers: `i_1`, `i_2`,...,`i_n`
2. Compare them with the smallest number `k_smallest` in first `k` numbers
3. If `i` is larger than `k_smallest`, use binary search to find the best position in `k` for `i`, then push all numbers in `k` that are smaller than `i` one position forward, so that there will be a empty space for `i` to insert into.
4. Else if `i` is smaller `k_smallest`, skip it
5. Repeat steps above until all `n` numbers are examined.

From the steps we see above, only step 2 and 3 are required to use `COMPARE()`, therefore, we manage to dramatically reduce our calling times for `COMPARE()` and successfully complete our comparing tasks.