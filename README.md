# Huffman-Codes in C++
In this I have build a file compression algorithm that uses binary trees and min binary heaps (priority queues). My program will allow the user to compress and decompress files using the standard Huffman algorithm for encoding and decoding. I have also implemented my own hash table, which will be used in implementing the Huffman encoding.

# Step by Step Guide
The first step is to count the frequency of occurrence of each character (including space, punctuation marks
or any other printable character). Construct a hash table and the key value pair would be character and its
frequency.
Read a character from the file and search it in the hash table. If search is unsuccessful then insert
the character in the hash table with frequency 1. Otherwise increase the frequency of the character by 1.
This you will compute the frequency of occurrence of each printable character in linear time. Wisely select
the hash function and size of the table. Use chaining as collision resolution strategy. For chaining you can
use linked list from the standard template library. For hash table you can either use an array or vector from
standard template library

In step 2 you will create the encoding tree. For each character in the file, create a binary tree of size 1 where
root of the tree contains the character and its frequency of occurrence. Build a min heap of the roots of these
trees based on their frequency of occurrence. Follow the Huffman encoding algorithm to construct the
encoding tree as discussed in class.

In step 3 you will create an encoding map (hash table). For each character derive it code and save it in a
hash table. This time key value pair is character and its corresponding code. Use the same structures and
collision resolution strategy as used in step 1.

In step 4 you will encode the textual data using the codes derived above. Here each character must be
replaced with its binary code. Since each code may not be of length 8 bits, so you would need to compact
these codes in form of bytes and then implement byte input/output streams. For this purpose you may need
to use bit operators like shift left, bitwise OR and bitwise AND.

In step 5, you will decode the encoded file using the same encoding tree constructed in step 2.

(remember I have implemented my own data structures)
