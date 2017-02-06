1. Introduction
This program can encode and decode text by Huffman tree. 
It consists of three parts: basic.cpp, ahencode.cpp and ahdecode.cpp. 
basic.cpp contains functions that build the Huffman tree, which are relied by ahencode.cpp and ahdecode.cpp. 
ahencode.cpp acts as encoding text and ahdecode.cpp act as decoding text.
Those two files should be compiled with basic.cpp.

2. Principle
The program maintains a Huffman tree and a path list. The path list stores paths of nodes in the tree. 
And the Huffman tree is a type of binary tree hence its basic unit is node. 
The node has 6 attributes shown as below.
-- leftNode. If a node is internal node, it means its left child node. Otherwise it is NULL.
-- rightNode. If a node is internal node, it means its right child node. Otherwise it is NULL.
-- parentNode. This node’s parent node.
-- Id. The ID of this node.
-- Weight. The weight of the node, weight 0 means it is a NYT node.
-- Value. The character of this node. If a node is internal node, it is ‘\0’.

2.1 Procedure
Step 1. When a character is read, the program will look up in the path list, if the path can be found, the program will follow the path to the node, change its position with the block leader.
Otherwise, the program will create a new node at the NYT position.
Step 2. Go to its parent node and check if it is root node. If it is not a root node, slide and swap the node (i.e. Put this node at the top of the block). Repeat this procedure until reaching root node.
Step 3. Update the id and path list.

2.2 Swap and slide
The core function in this Huffman tree is sliding nodes to the top of the block to keep the tree balanced.
Two functions are used for implementation, which are slideAndIncrement() and getSlideBlock().
slideAndIncrement() slide the node to the top of the block that are found by getSlideBlock().
It rebuilds the relationship between those nodes and their previous parent nodes.
getSlideBlock() return a queue of pointers of nodes before the target node with identical weight by Breadth-First-Search in the tree.

