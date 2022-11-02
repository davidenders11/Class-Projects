# Part 2: A Bloom Filter Class

For this part, you may use whatever programming language seems appropriate!

Figuring out how you'll do hashing is the only tricky bit; otherwise, the code should be very straightforward.

## To Do

1. In a language of your choice, implement a Bloom Filter class.

   - The "keys" stored in the Bloom Filter can be integers or strings, your choice.
   - The class must have a constructor that takes (exactly) an integer number $n$ of values we plan to store, and the floating-point number $p$, the desired false-positive probability.
     Your code should use these values to calculate a recommended number $k$ of hash functions to use and a recommended number $m$ of total bits to store. (See below to be reminded of the formulas.)
   - The class must have `insert(x)` and `lookup(x)` methods; the former takes a key `x` and adds it to the set represented by the Bloom Filter, and the latter takes a key `x` and returns true or false
     according to whether it appears to be a member of the set. Both `insert` and `lookup` must be worst-case time $\Theta(k)$.
   - The class must have a `probFP()` method that takes no arguments and returns the current floating-point probability
     that a key not in the set would report a false positive; how to calculate this is described below. This method must run in worst-case
     time $O(m+k)$.
   - You can have other private (or public) methods if it seems appropriate.

2. Write a short test program and verify that:

   - You can `insert` lots of items to an (appropriately-sized) Bloom Filter;
   - If you look up the keys you did insert, `lookup` reports they're _all_ present;
   - If you look up a lot of keys that you didn't insert, `lookup` reports they're _mostly_
     not present.
   - The calculated false-positive probability of the Filter is in the neighborhood of the number you specified when creating the filter. (You'll investigate this more in Part 3).
   - Inserting the same collection of keys into two different Bloom Filter objects can give you two (slightly) different calculated
     false-positive probabilities (because different objects will use different hash functions, and end up with
     different bit patterns, even when the keys are the same in both cases).

   Your Bloom Filter must be coded so that programs other than this
   test can also make use of your class. (Don't define `main()`
   in the same `.cpp` file that contains your Bloom Filter code;
   a Python file containing your class should be able to be `import`ed
   from another file without automatically running your tests; etc.)

3. Push your code (the class and your test code!) to GitHub. I won't spellcheck your comments, but your code should at
   least be readable in terms of formatting, variable names, etc.

## Implementation Notes

- If you use C++, it's reasonable to use a `std::vector<bool>` for your bits, since boolean vectors in C++
  have a specialized bit-vector implementation. Just beware that (unlike any other C++ vector) vectors of booleans can act
  oddly if you try to take the address of an element or pass one of the elements by reference.
- If you use Python, you can use a list or array of booleans (which is really easy and will satisfy all the assignment
  requirements, although it uses one or two orders of magnitude extra space and isn't
  practical in general)
  or an `array.array` of bytes (which uses the right amount of space, but requires lots of low-level bit-twiddling).
- If you use another programming language, you can use an appropriate data structure, as long as you can access and
  update individual bits in $\Theta(1)$ time.
- Many languages (including
  C++ and Python) come with a built-in hash function for integers and a built-in hash function for strings,
  you usually get only one such function per type. So, you will need to think about how
  your class constructor will specify (and record for insert/lookup) $k$ random (and sufficiently independent) hash functions.
- If $P_\mathrm{FP}$ is the probability of false positives we can tolerate, the classical calculations for $k$ and $m$ are as follows. (Watch out for the bases of the different logarithms!)

  $$k := \left\lceil\log_2 \frac{~1~}{P_\mathrm{FP}}\right\rceil$$

  $$m := \left\lceil\frac{1}{\ln 2}\times \log_2 \frac{~1~}{P_\mathrm{FP}} \times n\right\rceil$$

## The False-Positive Probability of a Specific Bloom Filter.

The formulas for $k$ and $m$ above are intended to ensure that on average, inserting $n$ items into the Bloom
Filter will set half the bits and leave half the bits unset.

That way, if $x$ is not in the set, then picking $k$ random bits (by hashing $x$ in $k$ different ways) will find $k$
1's (a false positive) with probability $(1/2)^k$. In fact, the formula for $k$ above is nothing more than advice to
pick the smallest $k$ such that $(1/2)^k$ is smaller than our desired probability of false positives!

But that's just the average case. Depending on the $n$ specific keys and the $k$ specific hash functions, we could get
very lucky with our $n$ inserts, with the hashed keys repeatedly sending us to the same few bit locations. This is "lucky"
because if very few bits in the Bloom Filter are set, the probability of a false positive (picking $k$ random bits and
finding them all to be 1) approaches zero. 

Conversely, we could get very unlucky with our $n$ inserts, with very few of
the hashed keys reusing the same bit locations; if most of the bits in the Bloom Filter are set, the probability of a
a key not in the set being a false positive is nearly certain.

In general, the probability of false positives in any _specific_ Bloom Filter (with a specific pattern of bits) can be calculated as the
probability that $k$ randomly-chosen bits will bet set. In other words, it is the fraction of bits that are set, raised to the $k$-th
power.

[Alternatively, we could get the false-positive probability for a filter experimentally by taking millions of keys not
in the set, and checking what fraction of them are reported to be in the set. This is potentially more accurate in
practice if the hash functions are less-than-ideal and not behaving like random choices of bit positions. But doing
those millions of lookups is also much, much, much slower.]
