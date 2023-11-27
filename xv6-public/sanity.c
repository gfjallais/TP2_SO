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

    for (int i = 0; i < 3*n; i++) {
		int j = i % 3;
		int pid = fork();
		if (pid == 0) {
			j = (getpid()) % 3;
			switch(j) {
				case 0:
                    for(int i = 0; i < 100; i++) {
                        for(int j = 0; j < 1000000; j++) {
                            asm("nop");
                        }
                    }
					break;
				case 1:
					for (int k = 0; k < 100; k++){
						for (double j = 0; j < 100000; j+=1){
				         double x =  x + 3.14 * 89.64 * j;

                        }
						yield();
					}
					break;
				case 2:
					for(int k = 0; k < 100; k++){
						sleep(1);
					}
					break;
			}
			exit(); // children exit here
		}
		continue; // father continues to spawn the next child
	}
    

    int sums[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			sums[i][j] = 0;

    for (int i = 0; i < 3*n; i++) {
        int retime, rutime, stime;
		int pid = wait2(&retime, &rutime, &stime);
		int res = (pid) % 3; // correlates to j in the dispatching loop
		switch(res) {
			case 0: // CPU bound processes
                printf(1,"Type: CPU-Bound\n");
                printf(1,"Waiting time: %d Running time: %d Sleeping time: %d Turnaround: %d\n", retime, rutime, stime, retime + rutime + stime);
                printf(1, "\n");
				sums[0][0] += retime;
				sums[0][1] += rutime;
				sums[0][2] += stime;
				break;
			case 1: // CPU bound processes, short tasks
                printf(1,"Type: S-CPU\n");
                printf(1,"Waiting time: %d Running time: %d Sleeping time: %d Turnaround: %d\n", retime, rutime, stime, retime + rutime + stime);
                printf(1, "\n");
				sums[1][0] += retime;
				sums[1][1] += rutime;
				sums[1][2] += stime;
				break;
			case 2: // simulating I/O bound processes
                printf(1,"Type: IO-BOUND\n");
                printf(1,"Waiting time: %d Running time: %d Sleeping time: %d Turnaround: %d\n", retime, rutime, stime, retime + rutime + stime);
                printf(1, "\n");
				sums[2][0] += retime;
				sums[2][1] += rutime;
				sums[2][2] += stime;
				break;
		}
	}
    
    printf(1,"cpu: %d scpu: %d io: %d\n", cpu, scpu, io);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			sums[i][j] /= n;

	printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[0][0], sums[0][1], sums[0][2], sums[0][0] + sums[0][1] + sums[0][2]);
	printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[1][0], sums[1][1], sums[1][2], sums[1][0] + sums[1][1] + sums[1][2]);
	printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[2][0], sums[2][1], sums[2][2], sums[2][0] + sums[2][1] + sums[2][2]);
	exit();

    exit();
}