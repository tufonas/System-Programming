#!/bin/bash
gcc -o jms_coord jms_coord.c
gcc -o jms_console jms_console.c
gcc -o pool pool.c
gcc -o job job.c
gcc -o try try.c
./jms_coord -l /home/user/folder/ -n 3 -w pipe_in -r pipe_out &
bash jms_script.sh -l /home/user/folder/ -c purge


