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

./zappy_server -p 12345 -x 5 -y 5 -n name1 name2 -c 10 -f 7 &
pids="$pids $!"

echo "Everything started successfully"

wait

echo "Demo done."