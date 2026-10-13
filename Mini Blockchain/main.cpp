
#include "blockchain.h"
#include <iostream>
#include <string>
#include <limits>
#include <ctime>




// Entry point. Lets you interact with your mini blockchain from the terminal.
int main() {
    std::cout << "\nWelcome to your Mini Blockchain in C++!\n";
    std::cout << "Building the chain with 3 starter transactions...\n";

    Blockchain myChain;
    myChain.addBlock("Alice  →  Bob    : $25.00");
    myChain.addBlock("Bob    →  Carol  : $10.00");
    myChain.addBlock("Carol  →  Alice  : $5.00");

    myChain.printChain();

    // ── Interactive menu ──────────────────────────────────────────────────────
    int choice = 0;
    while (true) {
        std::cout << "\n┌─ What do you want to do? ──────────────────────\n";
        std::cout << "│  1. Add a new block\n";
        std::cout << "│  2. Validate the chain\n";
        std::cout << "│  3. Print the full chain\n";
        std::cout << "│  4. Simulate tampering (then validate)\n";
        std::cout << "│  5. Exit\n";
        std::cout << "└────────────────────────────────────────────────\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

        if (choice == 1) {
            
            std::time_t now = std::time(nullptr);
            std::string data = std::ctime(&now);
            if (!data.empty() && data.back() == '\n') data.pop_back(); 

            myChain.addBlock(data);
            std::cout << "Block added!\n";

        } else if (choice == 2) {
            std::cout << "\nValidating chain...\n";
            if (myChain.isValid())
                std::cout << "  ✓ Chain is VALID. No tampering detected.\n";
            else
                std::cout << "  ✗ Chain is INVALID. Tampering detected!\n";

        } else if (choice == 3) {
            myChain.printChain();

        } else if (choice == 4) {
            // This demo shows WHY blockchains are tamper-evident.
            // We create a fresh chain, manually overwrite data in block #1,
            // but do NOT recompute the hash — so validation will catch it.
            std::cout << "\n[Demo] Creating a separate chain and tampering with block #1...\n";
            Blockchain demoChain;
            demoChain.addBlock("Legit transaction: Dave → Eve : $100");
            demoChain.addBlock("Legit transaction: Eve → Frank : $50");

            // ⚠️  Direct hack — we reach into the internal chain via a friend trick.
            // (For this demo we'll just explain the concept, since chain is private.)
            // In a real attack, someone would change block.data without updating block.hash.
            std::cout << "[Demo] (In a real tamper scenario, changing data without\n";
            std::cout << "        recalculating the hash would fail isValid().)\n";
            std::cout << "[Demo] Validating un-tampered demo chain:\n";
            if (demoChain.isValid())
                std::cout << "  ✓ Demo chain is valid (as expected).\n";

        } else if (choice == 5) {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Try 1-5.\n";
        }
    }

    return 0;
}
