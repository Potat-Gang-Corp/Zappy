#!/bin/sh

count=0
max_processes=10
pids=""

if [ $# -gt 0 ]; then
    max_processes=$1
fi

cleanup() {
    for pid in $pids; do
        kill $pid 2>/dev/null
    done
    wait
    echo "All processes stopped."
    exit 0
}

trap cleanup INT

echo "Start of the demo"

while [ $count -lt $max_processes ]; do
    ./zappy_ai -p 12345 -n name1 &
    pids="$pids $!" 
    count=$((count + 1))
    ./zappy_ai -p 12345 -n name2 &
    pids="$pids $!" 
    count=$((count + 1))
    sleep 0.1
done

echo "Everything started successfully"

wait

echo "Demo done."
