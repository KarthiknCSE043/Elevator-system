#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FLOORS 10
#define QUEUE_SIZE 100

// Queue to manage elevator requests
typedef struct {
    int data[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Elevator structure
typedef struct {
    int currentFloor;
    bool directionUp; // true for up, false for down
    Queue requestQueue;
} Elevator;

// Function prototypes
void initQueue(Queue *q);
bool isQueueEmpty(Queue *q);
bool enqueue(Queue *q, int value);
int dequeue(Queue *q);
void initializeElevator(Elevator *elevator);
void addRequest(Elevator *elevator, int floor);
void processRequests(Elevator *elevator);

int main() {
    Elevator elevator;
    initializeElevator(&elevator);

    int choice, floor;

    printf("Elevator Simulation\n");
    printf("Max floors: %d\n", MAX_FLOORS);

    while (1) {
        printf("\n1. Add floor request\n");
        printf("2. Process requests\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter floor number (0-%d): ", MAX_FLOORS - 1);
            scanf("%d", &floor);
            if (floor < 0 || floor >= MAX_FLOORS) {
                printf("Invalid floor number. Try again.\n");
            } else {
                addRequest(&elevator, floor);
            }
            break;
        case 2:
            processRequests(&elevator);
            break;
        case 3:
            printf("Exiting simulation.\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

// Queue functions
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

bool isQueueEmpty(Queue *q) {
    return q->front == q->rear;
}

bool enqueue(Queue *q, int value) {
    if ((q->rear + 1) % QUEUE_SIZE == q->front) {
        printf("Queue is full. Cannot add more requests.\n");
        return false;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    return true;
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty. No requests to process.\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return value;
}

// Elevator functions
void initializeElevator(Elevator *elevator) {
    elevator->currentFloor = 0;
    elevator->directionUp = true;
    initQueue(&elevator->requestQueue);
    printf("Elevator initialized at floor 0.\n");
}

void addRequest(Elevator *elevator, int floor) {
    if (enqueue(&elevator->requestQueue, floor)) {
        printf("Request added for floor %d.\n", floor);
    }
}

void processRequests(Elevator *elevator) {
    if (isQueueEmpty(&elevator->requestQueue)) {
        printf("No requests to process.\n");
        return;
    }

    printf("\nProcessing requests:\n");
    while (!isQueueEmpty(&elevator->requestQueue)) {
        int targetFloor = dequeue(&elevator->requestQueue);
        printf("Moving from floor %d to floor %d.\n", elevator->currentFloor, targetFloor);

        if (targetFloor > elevator->currentFloor) {
            elevator->directionUp = true;
        } else if (targetFloor < elevator->currentFloor) {
            elevator->directionUp = false;
        }

        elevator->currentFloor = targetFloor;
        printf("Elevator is now at floor %d.\n", elevator->currentFloor);
    }
}
