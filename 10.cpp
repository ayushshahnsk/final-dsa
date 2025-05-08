#include<iostream>
#include<string>
using namespace std;

const int MAX_SIZE = 10;  

string patientQueue[MAX_SIZE];
int priorityQueue[MAX_SIZE];
int rear = -1, front = -1;

void enqueuePatient(string name, int priority) {
    
    if((front == 0) && (rear == MAX_SIZE-1)) {
        cout << "Queue is full. Cannot add more patients." << endl;
        return;
    }
    
    
    if(front == -1) {
        front = rear = 0;
        patientQueue[rear] = name;
        priorityQueue[rear] = priority;
    }
    else {
        
        int i;
        for(i = rear; i >= front; i--) {
            if(priority > priorityQueue[i]) {
                patientQueue[i+1] = patientQueue[i];
                priorityQueue[i+1] = priorityQueue[i];
            }
            else {
                break;
            }
        }
       
        patientQueue[i+1] = name;
        priorityQueue[i+1] = priority;
        rear++;
    }
}

void displayQueue() {
    if(front == -1) {
        cout << "Queue is empty. No patients to display." << endl;
        return;
    }
    
    cout << "\nCurrent Patient Queue:" << endl;
    cout << "----------------------" << endl;
    for(int i = front; i <= rear; i++) {
        cout << "Patient: " << patientQueue[i] << " | Priority: ";
        switch(priorityQueue[i]) {
            case 3:
                cout << "Serious (Immediate attention needed)";
                break;
            case 2:
                cout << "Non-serious (Urgent)";
                break;
            case 1:
                cout << "General Checkup";
                break;
            default:
                cout << "Unknown Priority";
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
}

void processNextPatient() {
    if(front == -1) {
        cout << "Queue is empty. No patients to process." << endl;
        return;
    }
    
    cout << "\nNow processing: " << patientQueue[front] << endl;
    cout << "Priority: ";
    switch(priorityQueue[front]) {
        case 3:
            cout << "Serious - Emergency case!";
            break;
        case 2:
            cout << "Non-serious - Urgent care needed";
            break;
        case 1:
            cout << "General Checkup - Routine examination";
            break;
        default:
            cout << "Unknown priority level";
    }
    cout << endl;
    
    
    if(front == rear) {
        front = rear = -1; 
    }
    else {
        front++;  
    }
}

int main() {
    int choice, numPatients;
    string patientName;
    int priority;
    
    cout << "HOSPITAL PATIENT MANAGEMENT SYSTEM" << endl;
    cout << "----------------------------------" << endl;
    
    do {
        cout << "\nMAIN MENU:\n";
        cout << "1. Add Patients\n";
        cout << "2. View Patient Queue\n";
        cout << "3. Process Next Patient\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter number of patients to add: ";
                cin >> numPatients;
                if(numPatients <= 0 || numPatients > MAX_SIZE) {
                    cout << "Invalid number of patients. Please enter between 1 and " << MAX_SIZE << endl;
                    break;
                }
                for(int i = 0; i < numPatients; i++) {
                    cout << "\nPatient #" << i+1 << ":\n";
                    cout << "Enter patient name: ";
                    cin >> patientName;
                    cout << "Enter priority (3-Serious, 2-Non-serious, 1-General Checkup): ";
                    cin >> priority;
                    if(priority < 1 || priority > 3) {
                        cout << "Invalid priority! Setting to General Checkup (1)\n";
                        priority = 1;
                    }
                    enqueuePatient(patientName, priority);
                }
                break;
                
            case 2:
                displayQueue();
                break;
                
            case 3:
                processNextPatient();
                break;
                
            case 0:
                cout << "Exiting system. Goodbye!" << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while(choice != 0);
    
    return 0;
}