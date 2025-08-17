# Hospital Patient Queue (Priority + Normal Queue)

**Data Structures:** `std::priority_queue` (critical), `std::queue` (regular).  
**Concept:** Always serve **critical** patients first; otherwise serve the next **regular** patient.  
**Extras:** Estimated wait time = queue length × average service minutes.

## Features
- Add patient (name, age, severity 1–10, or mark as regular).
- Serve next patient with correct priority.
- Display current queue status and **estimated wait time**.
- Average service time adjustable from menu.

## Build & Run
```bash
g++ -std=c++17 -O2 -o HospitalQueue main.cpp
./HospitalQueue
```

## Sample Flow
1. Add critical (severity 9), add regular, add critical (7).  
2. Display queues → critical queue shows [9,7]; regular shows arrival order.  
3. `Serve Next` → serves severity 9 first.  
