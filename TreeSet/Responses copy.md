# Sample Runs

Paste the results of running these commands below: 

        ./minispell -d ../data/ispell.words -b ../data/smalldict.words

```
Reading words from ../data/ispell.words... done!
Inserting into dictionary (in perfect-balance order)... done!
 - insertion took 0.0687673 seconds
 - 34831 nodes, height 15, average depth 13.1189
 - median word in dictionary: 'intentness'

Reading words from ../data/smalldict.words... done!
Looking up these words in the dictionary... done!
 - looking up took 0.000345041 seconds
 - 341 words read, 325 in dictionary
```

        ./minispell -d ../data/ispell.words -s ../data/smalldict.words
        
```
Reading words from ../data/ispell.words... done!
Inserting into dictionary (in shuffled order)... done!
 - insertion took 0.0873386 seconds
 - 34831 nodes, height 36, average depth 17.1009
 - median word in dictionary: 'intentness'

Reading words from ../data/smalldict.words... done!
Looking up these words in the dictionary... done!
 - looking up took 0.00421604 seconds
 - 341 words read, 325 in dictionary
```

        ./minispell -d ../data/ispell.words ../data/smalldict.words
        
```
Reading words from ../data/ispell.words... done!
Inserting into dictionary (in order read)... done!
 - insertion took 38.7099 seconds
 - 34831 nodes, height 34830, average depth 17415
 - median word in dictionary: 'intentness'

Reading words from ../data/smalldict.words... done!
Looking up these words in the dictionary... done!
 - looking up took 0.333899 seconds
 - 341 words read, 325 in dictionary
```

# Comparisons

By what multiplicative factor was the average depth of the tree
worse for the in-file-order insertion (which was sorted order)
compared to the carefully chosen insertion-order that made a
well-balanced tree?

> Answer: 1327.47 times worse

By what multiplicative factor was the average depth of the tree
worse for the shuffled insertion (which was random order) compared
to the carefully chosen insertion-order that made a well-balanced
tree?

> Answer: 1.3 times worse

The file `../data/web2` has 234,937 words, rather than the 34,831
words found in `../data/ispell.words`.

Would you expect the multiplicative factor for in-file-order insertion
(which is sorted order) compared to balanced insertion to be better,
worse, or the same for this file? (delete the words that don't apply)

> Answer: Worse

Would you expect the multiplicative factor for shuffled-order
insertion compared to balanced insertion to be better, worse, or
the same for this file? (delete the words that don't apply)

> Answer: Same

Briefly explain these two answers.

> The in-order insertion multiplicative factor gets even worse as the number of words increases because
the height of the tree is linearly related to number of words while for the balanced tree the height of the tree
is logarithmically related to the number of words. 
For the comparison between balanced and shuffled, they are roughly the same because both trees are relatively 
balanced (trees do a good job balancing randomly shuffled values). So both have O(logn) height.

# Worst-Case Behavior

A random tree with n nodes has a worst-case average depth of (n-1)/2
and a worst-case height of n-1.  How close were you able to get to
this worst-case with shuffled insertion?

> Not close at all! Shuffled insertion was usually close to the balanced insertion. 
