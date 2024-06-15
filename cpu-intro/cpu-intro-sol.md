1. CPU utilisation is 100% as all instructions are CPU instructions (no I/O).

2. Default I/O take 5 cycles. So first program finishes after 4 cycles, followed by 7 cycles (2+5) in second program, total 11 cycles.

3. Now first program take 1 cycle to load before being blocked for I/O. Second program is run and finishes during I/O block. So total time is time of second program, so 7 cycles.

4. Now the scheduler does waits for process 1 to finish between starting process 2. We are back to the same runtime in question 2.

5. Now the scheduler will switch to another ready process when the running process is blocked by I/O. We are back to the same runtime in question 3.

6. The first process, when finished with I/O, is put to the back of the queue. So the execution fails to take advantage of doing I/O in parallel with other CPU heavy processes.

7. This would allow process 1 to interrupt the running process at end of I/O finish. The execution can take full advantage of doing I/O in parallel with other CPU heavy processes, which is why this scheduling is a good idea here. Although in general it's unclear to me if `IO_RUN_IMMEDIATE` is better. If the programs are: `(1:0,10:100), 5:100, 1:0, 1:0` then we end up waiting for I/O for the last 2 processes while CPU is idle.

8. I'd expect it to run a little longer than the average time to run one of the programs (1.5 * 7 + 1.5 * 1 = 12). In this case `IO_RUN_IMMEDIATE` and `SWITCH_ON_IO` are strictly better. `IO_RUN_IMMEDIATE` is better if the running process is blocked on I/O, same in other cases. `SWITCH_ON_IO` is better if the running process becomes blocked, same in other cases.