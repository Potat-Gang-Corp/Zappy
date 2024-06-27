#!/bin/sh

# count=0
# max_processes=10
pids=""

# if [ $# -gt 0 ]; then
#     max_processes=$1
# fi

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

./zappy_gui -p 12345 -h 127.0.0.1 &
pids="$pids $!"

echo "Everything started successfully"

wait

echo "Demo done."
