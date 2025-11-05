#include <iostream>
#include <queue>
#include <cstdlib>  // For generating random packet sizes
#include <ctime>    // For simulating arrival times

using namespace std;

// Packet structure
struct Packet {
    int id;            // Unique packet ID
    int arrivalTime;   // When the packet arrives
    int size;          // Packet size in bytes

    Packet(int i, int t, int s) : id(i), arrivalTime(t), size(s) {}
};

// Network Node class
class NetworkNode {
private:
    queue<Packet> packetQueue;  // FIFO queue for packets
    int maxQueueSize;           // Maximum queue capacity

public:
    NetworkNode(int maxSize) : maxQueueSize(maxSize) {}

    // Function to add a packet to the queue
    bool addPacket(Packet p) {
        if (packetQueue.size() >= maxQueueSize) {
            cout << "Queue full! Packet " << p.id << " dropped.\n";
            return false;  // Packet is dropped
        }
        packetQueue.push(p);
        cout << "Packet " << p.id << " added to queue.\n";
        return true;
    }

    // Function to process (remove) packets from the queue
    void processPacket() {
        if (!packetQueue.empty()) {
            Packet p = packetQueue.front();
            packetQueue.pop();
            cout << "Processing Packet " << p.id << " (Arrived at: " << p.arrivalTime 
                 << ", Size: " << p.size << " bytes)\n";
        } else {
            cout << "No packets to process.\n";
        }
    }

    // Function to check if queue is empty
    bool isQueueEmpty() {
        return packetQueue.empty();
    }
};

// Main simulation
int main() {
    srand(time(0));  // Seed random number generator

    NetworkNode node(5);  // Node with queue size limit of 5

    // Simulating packet arrivals
    for (int i = 1; i <= 7; i++) {
        int arrivalTime = rand() % 10;  // Random arrival time between 0-9
        int packetSize = (rand() % 500) + 100;  // Packet size between 100-600 bytes
        Packet p(i, arrivalTime, packetSize);
        node.addPacket(p);
    }

    // Simulating packet processing
    cout << "\nProcessing Packets:\n";
    while (!node.isQueueEmpty()) {
        node.processPacket();
    }

    return 0;
}

