#include <iostream>
#include <queue>
#include <ctime>

using namespace std;

// Define the packet structure
struct Packet {
    int id; // Unique identifier for each packet
    string type; // Type of the packet (e.g., Data, Audio, Video)
    time_t arrivalTime; // Arrival time of the packet
    
    Packet(int id, string type) {
        this->id = id;
        this->type = type;
        this->arrivalTime = time(0); // Set current time as arrival time
    }
};

// FIFO Queue Implementation
class FIFOQueue {
private:
    queue<Packet> packetQueue; // Standard C++ queue to simulate FIFO behavior
    
public:
    // Function to enqueue a packet
    void enqueue(const Packet& pkt) {
        packetQueue.push(pkt);
        cout << "Packet " << pkt.id << " of type " << pkt.type << " arrived at time " << ctime(&pkt.arrivalTime) << endl;
    }

    // Function to dequeue a packet (process the next packet in line)
    void dequeue() {
        if (!packetQueue.empty()) {
            Packet pkt = packetQueue.front(); // Get the first packet in the queue
            packetQueue.pop(); // Remove the packet from the queue
            cout << "Packet " << pkt.id << " processed at time " << ctime(&pkt.arrivalTime) << endl;
        } else {
            cout << "No packets in the queue to process." << endl;
        }
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return packetQueue.empty();
    }
    
    // Function to get the size of the queue
    int getQueueSize() {
        return packetQueue.size();
    }
};

// Function to simulate packet traffic
void generateTraffic(FIFOQueue &fifoQueue) {
    // Simulate generating 5 packets of different types
    fifoQueue.enqueue(Packet(1, "Data"));
    fifoQueue.enqueue(Packet(2, "Audio"));
    fifoQueue.enqueue(Packet(3, "Video"));
    fifoQueue.enqueue(Packet(4, "Data"));
    fifoQueue.enqueue(Packet(5, "Audio"));
}

// Main function to simulate FIFO processing
int main() {
    FIFOQueue fifoQueue;
    
    // Generate traffic
    generateTraffic(fifoQueue);

    // Process the packets in the queue (FIFO order)
    while (!fifoQueue.isEmpty()) {
        fifoQueue.dequeue();
    }

    return 0;
}

