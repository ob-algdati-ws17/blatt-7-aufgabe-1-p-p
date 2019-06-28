## AVLTree [![Build Status](https://travis-ci.org/ob-algdati-ws17/blatt-7-aufgabe-1-p-p.svg?branch=master)](https://travis-ci.org/ob-algdati-ws17/blatt-7-aufgabe-1-p-p) [![Coverage Status](https://coveralls.io/repos/github/ob-algdati-ws17/blatt-7-aufgabe-1-p-p/badge.svg?branch=master)](https://coveralls.io/github/ob-algdati-ws17/blatt-7-aufgabe-1-p-p?branch=master)
Implementation of an [AVL Tree](https://en.wikipedia.org/wiki/AVL_tree). This is a self-balancing tree with fast search, insert and delete complexities of O(log(n)). In our implementation we don't save the 'parent' of a node in the node but retrieve the parent by traversing the tree. This saves us the O(n) space-complexity in favour of the O(log n) time-complexity.

[Documentation](https://ob-algdati-ws17.github.io/blatt-7-aufgabe-1-p-p/docs/html/)

Authors: *[J. Behrmann](https://github.com/jjxxs), [J. Kluoné](https://github.com/JustinaKluone)*

Visual representation of an AVLTree, made with [GraphViz](https://graphviz.gitlab.io/):
![Example tree](https://hobbystudent.de/img/tree.png)
