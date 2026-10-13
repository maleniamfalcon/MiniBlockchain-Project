#include "block.h"
#include <sstream>
#include <ctime>
#include <functional>  // for std::hash

// Helper: get current time as a readable string
static std::string currentTime() {
    std::time_t now = std::time(nullptr);
    std::string t = std::ctime(&now);
    // Remove the trailing newline ctime adds
    if (!t.empty() && t.back() == '\n') t.pop_back();
    return t;
}

// Constructor: set all fields and immediately compute our hash
Block::Block(int idx, const std::string& blockData, const std::string& previousHash)
    : index(idx), data(blockData), prevHash(previousHash)
{
    timestamp = currentTime();
    hash      = calculateHash();   // Every block knows its own fingerprint
}

// calculateHash: combines all the block's fields into one string, then hashes it.
// This is a simplified hash (not SHA-256), but the concept is identical:
// change ANY part of the block → completely different hash.
std::string Block::calculateHash() const {
    // Pack everything into one long string
    std::ostringstream oss;
    oss << index << timestamp << data << prevHash;
    std::string combined = oss.str();

    // std::hash turns that string into a big number
    std::size_t hashValue = std::hash<std::string>{}(combined);

    // Convert the number to a hex string (looks like a real hash!)
    std::ostringstream hexStream;
    hexStream << std::hex << hashValue;
    return hexStream.str();
}
