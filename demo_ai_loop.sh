#!/bin/sh

count=0
max_processes=40
pids=""

cleanup() {
    for pid in $pids; do
        kill $pid 2>/dev/null
    done
    wait
    echo "All processes stopped."
    exit 0
}

trap 'cleanup' INT

while [ $count -lt $max_processes ]; do
    ./zappy_ai -p 12345 -n name1 &
    pids="$pids $!" 
    pid1=$!
    count=$((count + 1))
    ./zappy_ai -p 12345 -n name2 &
    pids="$pids $!" 
    pid2=$!
    count=$((count + 1))
    
done

while true; do
wait -n
if [ $? -eq 0 ]; then
    if [ $((count % 2)) -eq 1 ]; then
        ./zappy_ai -p 12345 -n name1 &
        pids="$pids $!" 
        pid1=$!
        count=$((count + 1))
    elif [ $((count % 2)) -eq 0 ]; then
        ./zappy_ai -p 12345 -n name2 &
        pids="$pids $!" 
        pid2=$!
        count=$((count + 1))
    fi
fi
done

wait

echo "All AIs are done"
