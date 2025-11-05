#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>

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

    string getFormattedTime() const {
        char buffer[26];
        struct tm* tm_info;
        tm_info = localtime(&arrivalTime);
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        return string(buffer);
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
            cout << "Packet " << pkt.id << " of type " << pkt.type << " arrived at time " << pkt.getFormattedTime() << " and placed in high priority queue." << endl;
        } else if (pkt.type == "Video") {
            mediumPriorityQueue.push(pkt);
            cout << "Packet " << pkt.id << " of type " << pkt.type << " arrived at time " << pkt.getFormattedTime() << " and placed in medium priority queue." << endl;
        } else if (pkt.type == "Data") {
            lowPriorityQueue.push(pkt);
            cout << "Packet " << pkt.id << " of type " << pkt.type << " arrived at time " << pkt.getFormattedTime() << " and placed in low priority queue." << endl;
        }
    }

    // Function to process the highest priority packet first
    void dequeue() {
        if (!highPriorityQueue.empty()) {
            Packet pkt = highPriorityQueue.front();
            highPriorityQueue.pop();
            cout << "Packet " << pkt.id << " of type " << pkt.type << " processed from high priority queue at time " << pkt.getFormattedTime() << endl;
        } else if (!mediumPriorityQueue.empty()) {
            Packet pkt = mediumPriorityQueue.front();
            mediumPriorityQueue.pop();
            cout << "Packet " << pkt.id << " of type " << pkt.type << " processed from medium priority queue at time " << pkt.getFormattedTime() << endl;
        } else if (!lowPriorityQueue.empty()) {
            Packet pkt = lowPriorityQueue.front();
            lowPriorityQueue.pop();
            cout << "Packet " << pkt.id << " of type " << pkt.type << " processed from low priority queue at time " << pkt.getFormattedTime() << endl;
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

// Function to generate random traffic for Audio, Video, and Data packets
void generateRandomTraffic(SPQQueue &spqQueue) {
    srand(time(0));  // Seed for random number generation
    int packetId = 1;
    
    // Generate random traffic for 20 packets (can be changed based on need)
    for (int i = 0; i < 20; i++) {
        // Randomly pick a packet type (Audio, Video, or Data)
        int randType = rand() % 3;
        string packetType;
        
        if (randType == 0) packetType = "Audio";
        else if (randType == 1) packetType = "Video";
        else packetType = "Data";
        
        // Create a new packet and enqueue it
        Packet pkt(packetId++, packetType);
        spqQueue.enqueue(pkt);
        
        // Simulate random interval between packet arrivals (between 1 and 3 seconds)
        this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));
    }
}

// Main function to simulate the SPQ and Traffic
int main() {
    SPQQueue spqQueue;
    
    // Simulate traffic generation
    generateRandomTraffic(spqQueue);

    // Process the packets in the SPQ queue (Priority Order)
    while (!spqQueue.isEmpty()) {
        spqQueue.dequeue();
        
        // Simulate processing time for each packet (1 second)
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}

