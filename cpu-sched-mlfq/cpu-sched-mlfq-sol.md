1. 

2. 

3. Have 1 queue

4. You can set quantum time to be 10 slices and job 1 to issue IO every 9 slices. Even though job 1 individually takes longer time because of extra IO, it ends up taking less turnaround time than job 2 because it stays on high priority while job 2 is on low priority

```sh
zaiyu@zaiyu-Vostro-5581:~/repo/ostep-homework/cpu-sched-mlfq$ ./mlfq.py -q 10 -a 1 -l 0,9000,9:0,9000,0 -c | tail
[ time 20489 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 9000) ]
[ time 20490 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 20490
  Job  1: startTime   0 - response   9 - turnaround 13509

  Avg  1: startTime n/a - response 4.50 - turnaround 16999.50


zaiyu@zaiyu-Vostro-5581:~/repo/ostep-homework/cpu-sched-mlfq$ ./mlfq.py -q 10 -a 1 -l 0,9000,9:0,9000,0 -c -S | tail
[ time 17999 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 9000) ]
[ time 18000 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 14000
  Job  1: startTime   0 - response   9 - turnaround 18000

  Avg  1: startTime n/a - response 4.50 - turnaround 16000.00
```

5. Here all jobs are scheduled at once. We can starve a single long-running job by adding an arbitrary number of small 10ms jobs. If we assume that boosted jobs are pushed to the front of the queue, then a 200ms boost frequency will guarantee a 5% CPU usage for a single long-running job.

6. 