//
//  block.h
//  Mini Blockchain
#pragma once
#include <string>

// A Block holds one piece of data in the chain.
// Think of it like a page in a ledger book.
class Block {
public:
    int      index;          // Position of this block in the chain (0, 1, 2, ...)
    std::string data;        // The actual content stored (e.g. "Alice sent Bob $10")
    std::string timestamp;   // When this block was created
    std::string prevHash;    // The hash of the block BEFORE this one (links them together)
    std::string hash;        // This block's own unique fingerprint

    // Constructor: called when we create a new Block
    Block(int idx, const std::string& blockData, const std::string& previousHash);

    // Computes this block's hash from its contents
    std::string calculateHash() const;
};
