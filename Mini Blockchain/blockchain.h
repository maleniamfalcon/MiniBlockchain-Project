//
//  blockchain.h
//  Mini Blockchain
//
#pragma once
#include "block.h"
#include <vector>

// Blockchain: a growing list of Blocks where each one is linked to the previous.
// If anyone tampers with a block, the chain of hashes breaks — we can detect it!
class Blockchain {
public:
    Blockchain();                            // Creates the chain with a Genesis block
    void addBlock(const std::string& data);   // Appends a new block to the end
    void printChain() const;                 // Prints every block neatly
    bool isValid() const;                    // Checks if the chain has been tampered with

private:
    std::vector<Block> chain;   // The actual list of blocks
    Block createGenesisBlock(); // The very first block (special-cased)
};

