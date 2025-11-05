#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>
#include <map>  // Add this include for the map type

using namespace std;
using namespace chrono;

// Constants
const int MAX_QUEUE_SIZE = 10;
const vector<string> PACKET_TYPES = {"Video", "Audio", "Data"};
const map<string, int> PRIORITY_MAP = {{"Audio", 1}, {"Video", 2}, {"Data", 3}};

// Packet class
class Packet {
public:
    int packet_id;
    string packet_type;
    time_point<system_clock> arrival_time;
    int delay;

    Packet(int id, string type, time_point<system_clock> arrival)
        : packet_id(id), packet_type(type), arrival_time(arrival), delay(0) {}

    void calculate_delay(time_point<system_clock> current_time) {
        duration<int> diff = duration_cast<seconds>(current_time - arrival_time);
        delay = diff.count();
    }

    void display() const {
        cout << "Packet " << packet_id << " of type " << packet_type;
    }
};

// Packet Arrival and Queueing Simulation
Packet* packet_arrival(queue<Packet*>& queue_obj, vector<Packet*>& processed_packets, int& blocked_packets) {
    static int packet_id = 1;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 2);
    
    string packet_type = PACKET_TYPES[dis(gen)];
    auto arrival_time = system_clock::now();

    Packet* packet = new Packet(packet_id, packet_type, arrival_time);
    packet_id++;

    if (queue_obj.size() < MAX_QUEUE_SIZE) {
        queue_obj.push(packet);
        cout << packet_type << " arrived at " << system_clock::to_time_t(arrival_time) << " and placed in the queue." << endl;
    } else {
        blocked_packets++;  // Increment blocked packet counter
        cout << packet_type << " arrived at " << system_clock::to_time_t(arrival_time) << " and could not be enqueued (Queue is full)." << endl;
        return nullptr;
    }

    return packet;
}

// Packet Processing Simulation
void process_packets(queue<Packet*>& queue_obj, vector<Packet*>& processed_packets) {
    while (!queue_obj.empty()) {
        Packet* current_packet = queue_obj.front();
        queue_obj.pop();

        auto current_time = system_clock::now();
        current_packet->calculate_delay(current_time);
        processed_packets.push_back(current_packet);

        cout << current_packet->packet_type << " processed at " << system_clock::to_time_t(current_time)
             << " with delay " << current_packet->delay << " seconds." << endl;
    }
}

// Main Simulation Logic
void simulate_packet_processing() {
    queue<Packet*> queue_obj;
    vector<Packet*> processed_packets;
    int total_delay = 0;
    int total_packets = 0;
    int packet_count = 0;
    int blocked_packets = 0;
    int total_queue_size = 0;  // Track the total number of packets in the queue

    while (packet_count < 20) {  // Simulate for 20 packets
        Packet* packet = packet_arrival(queue_obj, processed_packets, blocked_packets);

        if (packet) {
            total_packets++;
            packet_count++;
        }

        // Track the number of packets in the queue
        total_queue_size += queue_obj.size();

        // Simulate the time between packet arrivals
        this_thread::sleep_for(chrono::milliseconds(500 + rand() % 1000));

        if (queue_obj.size() >= MAX_QUEUE_SIZE) {
            process_packets(queue_obj, processed_packets);
        }
    }

    // Final packet processing
    if (!queue_obj.empty()) {
        process_packets(queue_obj, processed_packets);
    }

    // Performance Metrics
    if (!processed_packets.empty()) {
        total_delay = 0;
        for (auto p : processed_packets) {
            total_delay += p->delay;
        }
        int avg_delay = total_delay / processed_packets.size();
        
        // Calculate Blocking Ratio
        double blocking_ratio = (static_cast<double>(blocked_packets) / 20.0) * 100;
        
        // Calculate Queue Utilization
        double average_queue_size = static_cast<double>(total_queue_size) / packet_count;
        double queue_utilization = (average_queue_size / MAX_QUEUE_SIZE) * 100;

        cout << "\nPerformance Metrics:" << endl;
        cout << "Total Packets Processed: " << processed_packets.size() << endl;
        cout << "Total Delay (seconds): " << total_delay << endl;
        cout << "Average Delay (seconds): " << avg_delay << endl;
        cout << "Blocking Ratio: " << blocking_ratio << "%" << endl;
        cout << "Queue Utilization: " << queue_utilization << "%" << endl;
    }
}

int main() {
    simulate_packet_processing();
    return 0;
}

