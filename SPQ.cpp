#include <iostream>
#include <queue>
#include <ctime>
#include <string>

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

// SPQ Queue Implementation
class SPQQueue {
private:
    queue<Packet> highPriorityQueue; // High priority queue (e.g., Audio)
    queue<Packet> mediumPriorityQueue; // Medium priority queue (e.g., Video)
    queue<Packet> lowPriorityQueue; // Low priority queue (e.g., Data)
    
public:
    // Function to enqueue a packet based on its type
    void enqueue(const Packet& pkt) {
        if (pkt.type == "Audio") {
            highPriorityQueue.push(pkt);
            cout << "Packet " << pkt.id << " of type " << pkt.type << " arrived at time " << ctime(&pkt.arrivalTime) << " and placed in high priority queue." << endl;
        } else if (pkt.type == "Video") {
            mediumPriorityQueue.push(pkt);
            cout << "Packet " << pkt.id << " of type " << pkt.type << " arrived at time " << ctime(&pkt.arrivalTime) << " and placed in medium priority queue." << endl;
        } else if (pkt.type == "Data") {
            lowPriorityQueue.push(pkt);
            cout << "Packet " << pkt.id << " of type " << pkt.type << " arrived at time " << ctime(&pkt.arrivalTime) << " and placed in low priority queue." << endl;
        }
    }

    // Function to process the highest priority packet first
    void dequeue() {
        if (!highPriorityQueue.empty()) {
            Packet pkt = highPriorityQueue.front();
            highPriorityQueue.pop();
            cout << "Packet " << pkt.id << " of type " << pkt.type << " processed from high priority queue at time " << ctime(&pkt.arrivalTime) << endl;
        } else if (!mediumPriorityQueue.empty()) {
            Packet pkt = mediumPriorityQueue.front();
            mediumPriorityQueue.pop();
            cout << "Packet " << pkt.id << " of type " << pkt.type << " processed from medium priority queue at time " << ctime(&pkt.arrivalTime) << endl;
        } else if (!lowPriorityQueue.empty()) {
            Packet pkt = lowPriorityQueue.front();
            lowPriorityQueue.pop();
            cout << "Packet " << pkt.id << " of type " << pkt.type << " processed from low priority queue at time " << ctime(&pkt.arrivalTime) << endl;
        } else {
            cout << "No packets in the queue to process." << endl;
        }
    }

    // Function to check if the queues are empty
    bool isEmpty() {
        return highPriorityQueue.empty() && mediumPriorityQueue.empty() && lowPriorityQueue.empty();
    }
    
    // Function to get the size of all the queues
    int getTotalQueueSize() {
        return highPriorityQueue.size() + mediumPriorityQueue.size() + lowPriorityQueue.size();
    }
};

// Function to simulate packet traffic with different types
void generateTraffic(SPQQueue &spqQueue) {
    // Simulate generating 5 packets of different types
    spqQueue.enqueue(Packet(1, "Data"));
    spqQueue.enqueue(Packet(2, "Audio"));
    spqQueue.enqueue(Packet(3, "Video"));
    spqQueue.enqueue(Packet(4, "Data"));
    spqQueue.enqueue(Packet(5, "Audio"));
}

// Main function to simulate SPQ processing
int main() {
    SPQQueue spqQueue;
    
    // Generate traffic
    generateTraffic(spqQueue);

    // Process the packets in the SPQ queue (Priority Order)
    while (!spqQueue.isEmpty()) {
        spqQueue.dequeue();
    }

    return 0;
}

