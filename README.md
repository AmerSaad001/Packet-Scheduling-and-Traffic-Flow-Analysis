# Packet Scheduling and Traffic Flow Simulation

This project simulates basic packet scheduling algorithms in C++ to study how different queueing disciplines affect network performance.

---

## 🧩 Algorithms Implemented
- **FIFO (First In, First Out):** Packets are processed in arrival order.  
- **SPQ (Strict Priority Queue):** High-priority packets (e.g., video/audio) are served before low-priority ones.  
- **PAQD (Priority Adaptive Queueing Discipline):** Dynamically adjusts packet priority based on network conditions.  

---

## 📁 Files
| File | Description |
|------|--------------|
| `FIFO.cpp` | Implements the FIFO scheduling algorithm |
| `SPQ.cpp` | Implements Strict Priority Queuing |
| `Traffic.cpp` | Simulates random traffic for different packet types |
| `P-analysis.cpp` | Calculates delay, blocking ratio, and queue utilization |
| `PAQD.cpp` | Handles packet arrival, queuing, and departure logic |

---

## ⚙️ How to Compile and Run
In your terminal:

```bash
g++ FIFO.cpp -o FIFO
./FIFO

g++ SPQ.cpp -o SPQ
./SPQ

g++ PAQD.cpp -o PAQD
./PAQD

g++ Traffic.cpp -o Traffic
./Traffic

g++ P-analysis.cpp -o Panalysis
./Panalysis
