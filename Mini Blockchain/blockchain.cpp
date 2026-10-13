//
//  blockchain.cpp
//  Mini Blockchain


#include "blockchain.h"
#include <iostream>
#include <iomanip>

// ── Constructor ────────────────────────────────────────────────────────────────
// Every blockchain starts with a "Genesis Block" — block #0, born from nothing.
Blockchain::Blockchain() {
    chain.push_back(createGenesisBlock());
}

// ── createGenesisBlock ─────────────────────────────────────────────────────────
// The first block has no previous hash, so we use "0" as a placeholder.
Block Blockchain::createGenesisBlock() {
    return Block(0, "Genesis Block", "0");
}

// ── addBlock ───────────────────────────────────────────────────────────────────
// Creates a new Block and appends it to the chain.

void Blockchain::addBlock(const std::string& data) {
    const Block& lastBlock = chain.back();          // Get the current last block
    Block newBlock(static_cast<int>(chain.size()), data, lastBlock.hash); // Link to it via its hash
    chain.push_back(newBlock);
}


// Walks through every block and prints its details.
void Blockchain::printChain() const {
    std::cout << "\n╔══════════════════════════════════════════════════╗\n";
    std::cout << "║              M I N I   B L O C K C H A I N       ║\n";
    std::cout << "╚══════════════════════════════════════════════════╝\n";

    for (const Block& b : chain) {
        std::cout << "\n┌─ Block #" << b.index << " ─────────────────────────────\n";
        std::cout << "│  Data      : " << b.data      << "\n";
        std::cout << "│  Time      : " << b.timestamp << "\n";
        std::cout << "│  Prev Hash : " << b.prevHash  << "\n";
        std::cout << "│  Hash      : " << b.hash      << "\n";
        std::cout << "└────────────────────────────────────────────────\n";
    }
}

// ── isValid ────────────────────────────────────────────────────────────────────
// Verifies the chain by checking two things for every block (except Genesis):
//   1. Its stored hash still matches what recalculating it gives us.
//   2. Its prevHash matches the actual hash of the block before it.
// If either check fails → someone tampered with the data!
bool Blockchain::isValid() const {
    for (int i = 1; i < (int)chain.size(); ++i) {
        const Block& current  = chain[i];
        const Block& previous = chain[i - 1];

        // Check 1: has this block's data been changed?
        if (current.hash != current.calculateHash()) {
            std::cout << "  [!] Block #" << i << " hash is INVALID (data was tampered!)\n";
            return false;
        }

        // Check 2: is this block actually linked to the correct previous block?
        if (current.prevHash != previous.hash) {
            std::cout << "  [!] Block #" << i << " is NOT linked to the correct previous block!\n";
            return false;
        }
    }
    return true;
}
