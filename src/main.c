#include <bits/stdc++.h>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    // severity 1..10; 0 = regular (goes to normal queue)
    int severity;
    long long timestamp; // for tie-breaker (earlier first when same severity)
};

struct CriticalCmp {
    bool operator()(const Patient& a, const Patient& b) const {
        if (a.severity == b.severity) return a.timestamp > b.timestamp; // min timestamp first
        return a.severity < b.severity; // higher severity has higher priority
    }
};

class HospitalQueue {
    priority_queue<Patient, vector<Patient>, CriticalCmp> criticalPQ;
    queue<Patient> regularQ;
    int nextId = 1;
    long long tick = 0;
    int avgServiceMins = 10;

    Patient makePatient(const string& name, int age, int severity) {
        Patient p{nextId++, name, age, severity, tick++};
        return p;
    }

public:
    void addPatient(bool critical) {
        string name; int age;
        cout << "Enter name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter age: ";
        while(!(cin >> age) || age<=0){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid age. Enter again: ";
        }
        if (critical) {
            int sev;
            cout << "Enter severity (1-10, 10 = most critical): ";
            while(!(cin >> sev) || sev<1 || sev>10){
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Invalid severity. Enter 1-10: ";
            }
            auto p = makePatient(name, age, sev);
            criticalPQ.push(p);
            cout << "Added CRITICAL patient ID " << p.id << " (sev " << sev << ")\n";
        } else {
            auto p = makePatient(name, age, 0);
            regularQ.push(p);
            cout << "Added regular patient ID " << p.id << "\n";
        }
    }

    void serveNext() {
        if (!criticalPQ.empty()) {
            auto p = criticalPQ.top(); criticalPQ.pop();
            cout << "Serving CRITICAL patient ID " << p.id << " - " << p.name << " (sev " << p.severity << ")\n";
        } else if (!regularQ.empty()) {
            auto p = regularQ.front(); regularQ.pop();
            cout << "Serving regular patient ID " << p.id << " - " << p.name << "\n";
        } else {
            cout << "No patients waiting.\n";
        }
    }

    int waitingCount() const {
        return (int)criticalPQ.size() + (int)regularQ.size();
    }

    void setAvgServiceTime() {
        int v; cout << "Current avg service time: " << avgServiceMins << " mins\n";
        cout << "Enter new average minutes per patient (>=1): ";
        while(!(cin >> v) || v<1){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid. Enter >=1: ";
        }
        avgServiceMins = v;
        cout << "Updated average service time.\n";
    }

    void display() {
        cout << "\n--- Queue Status ---\n";
        cout << "Critical waiting: " << criticalPQ.size() << "\n";
        // Print a snapshot of criticalPQ without popping
        vector<Patient> temp;
        auto pq = criticalPQ;
        while(!pq.empty()){ temp.push_back(pq.top()); pq.pop();}
        if(temp.empty()) cout << "(none)\n";
        else {
            cout << "Critical by priority (top first): ";
            for(size_t i=0;i<temp.size();++i){
                cout << "[ID " << temp[i].id << " sev " << temp[i].severity << "] ";
            } cout << "\n";
        }
        cout << "Regular waiting: " << regularQ.size() << "\n";
        if(regularQ.empty()) cout << "(none)\n";
        else {
            cout << "Regular order: ";
            auto q = regularQ;
            while(!q.empty()){ cout << "[ID " << q.front().id << "] "; q.pop(); }
            cout << "\n";
        }
        cout << "Total waiting: " << waitingCount() << "\n";
        cout << "Estimated wait time (mins) ≈ " << waitingCount() * avgServiceMins << "\n";
        cout << "---------------------\n\n";
    }

    void run() {
        while (true) {
            cout << "==== Hospital Patient Queue ====\n";
            cout << "1. Add CRITICAL patient\n";
            cout << "2. Add regular patient\n";
            cout << "3. Serve next patient\n";
            cout << "4. Display queues & ETA\n";
            cout << "5. Set average service time\n";
            cout << "0. Exit\n";
            cout << "Choose: ";
            int ch; if(!(cin >> ch)){ return; }
            switch(ch){
                case 1: addPatient(true); break;
                case 2: addPatient(false); break;
                case 3: serveNext(); break;
                case 4: display(); break;
                case 5: setAvgServiceTime(); break;
                case 0: cout << "Goodbye!\n"; return;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    HospitalQueue app;
    app.run();
    return 0;
}
