#include "types.h"
#include "user.h"
// #include "defs.h"

// Function prototypes
void cpu_bound();
void s_cpu_bound();
void io_bound();

int main(int argc, char *argv[]) {
    if (argc != 2) {

        printf(1,"Usage: sanity <n>\n");
        exit();
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < 3 * n; i++) {
        int pid = fork();
        if (pid == 0) {
            // Child process
            if (i % 3 == 0)
                cpu_bound();
            else if (i % 3 == 1)
                s_cpu_bound();
            else
                io_bound();

            exit();
        }
    }

    // Parent process
    for (int i = 0; i < 3 * n; i++) {
        int retime, rutime, stime;
        int pid = wait2(&retime, &rutime, &stime);

        // Print statistics for each process
        printf(1,"Process %d (PID: %d)\n", i, pid);
        printf(1,"Type: %s\n", (i % 3 == 0) ? "CPU-Bound" : ((i % 3 == 1) ? "S-CPU" : "IO-Bound"));
        printf(1,"Waiting time: %d\nRunning time: %d\nSleeping time: %d\n", retime, rutime, stime);
    }

    // Print average statistics
    // ...

    exit();
}

void cpu_bound() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 1000000; j++) {
            // Empty loop
        }
    }
}

void s_cpu_bound() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 1000000; j++) {
            // Empty loop
        }
        yield();
    }
}

void io_bound() {
    for (int i = 0; i < 100; i++) {
        sleep(1);
    }
}
