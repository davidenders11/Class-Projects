# Part 3: Experimenting with Bloom Filters

In this part, you will run some small experiments using
your Bloom Filter implementation from Part 2.

## Background

It has been suggested that the traditional formula for computing the number
$m$ of bits to use in a hash table is over-optimistic, and might cause us 
to use fewer bits than we need in order to achieve a specific false-positive probability.

In particular,
when $m$ and $n$ are relatively small, some of the approximations we made
(that knowing some bits in the filter are set or not tells us
nothing about whether the remaining bits are likely to be set or not;
that we can replace $(1-1/m)^m$ by $e^{-m}$; etc.) introduce
larger errors.

Do we really need to worry? We can get some insight by investigating
the false-positive probabilities of different filters.

Specifically, suppose we create a Bloom Filter sized for $n$ items with desired false-positive
probability $p$, insert $n$ items, and check the actual false-positive
probability for that filter.

If we do this many times (30, 100, or more) and record the actual false-positive probability for each such filter, we
can get a feel for how well this size of filter works in practice. (We can even get away with using the same $n$ keys
each time, as long as the hash functions for each filter are different.)

## To Do

1. Investigate the empirical false-positive probabilities for the
   following situations:

   - $n = 1000000$ (one million), $p = 0.01$
   - $n = 1000$ (one thousand), $p = 0.01$.
   - $n = 5$ (five), $p = 0.01$.
   - At last one more scenario of your choice (involving a different $p$ and/or $n$)

2. Submit on [Gradescope](https://www.gradescope.com/courses/403793) a one-page (letter-size) poster describing your findings.
   It must include the following ingredients:

   - A title
   - A self-contained introduction explaining what question you are trying to answer.
     For this assignment, you may assume the reader already knows what a Bloom Filter is.
   - As a separate paragraph or section, enough explanation of what you measured that the reader can understand the data, along with
     any important parameters of the experiment (e.g, how many runs of the situations).
   - Plot(s) showing the range of observed false-positive probabilities for each of the 4+
     situations. (A scatter plot or jitter plot just showing the individual measurements is fine; histograms could work
     too.)

   - A conclusion paragraph containing at least three sentences that describes the takeaway(s).
     from your experiment. The conclusion must show that you thought about the
     results, i.e., it needs to be something more than just summarizing the plotted
     data in words.

   As always, your poster should be designed to be easily readable. It should use proper spelling and grammar, use
   complete sentences, and divide separate topics into separate paragraphs. Fonts (including text in your plots) should
   be large enough to be readable.
