#!/bin/bash

# echo $1
# PID="$1"
# LOGFILE="cpu_pulse_{$PID}.txt"

# echo $PID

# if ! ps -p "$PID" > /dev/null; then
#     echo "Process ${PID} is not running"
#     exit 1
# fi

# echo "Logging CPU and memory usage for PID $PID..."
# echo "Time, %CPU, %MEM" >> $LOGFILE

# while ps -p "$PID" > /dev/null; do
#     STATS=$(ps -p "$PID" -o %cpu,%mem=)
#     NOW=$(date +"%H:%M:%S")
#     echo "$NOW, $STATS" >> "$LOGFILE"
#     sleep 1
# done

# echo "Process $PID ended."
# echo "CPU/MEM log saved to $LOGFILE."
PID="$1"
# STATS=$(ps -p "$PID" -o %cpu,%mem=)
NOW=$(date +"%H:%M:%S")
# CPU=$(top -l 1 -pid "$PID" | awk -v pid="$PID" '$1==pid {print $3}')
CPU=$(top -l 2 -s 1 -pid "$PID")
echo "$NOW, $CPU"

# PID="$1"
# LOG="cpu_top_${PID}.txt"
# echo "Time, %CPU" > "$LOG"

# while ps -p "$PID" > /dev/null; do
#     NOW=$(date +"%H:%M:%S")
#     CPU=$(top -l 1 -pid "$PID" | grep "^$PID" | awk '{print $3}')
#     echo "$NOW, $CPU" >> "$LOG"
#     sleep 0.2
# done

# echo "Done logging CPU to $LOG"