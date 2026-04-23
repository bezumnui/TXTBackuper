#!/bin/bash

TARGET="txt_backuper"
LOG_DIR="logs"
REPORT="$LOG_DIR/report.txt"
timestamp=$(date +%Y-%m-%d_%H-%M-%S)

if [ ! -d "$LOG_DIR" ]; then
    mkdir "$LOG_DIR"
fi

if make; then
  echo "Assembled"
  echo "-------- START OF REPORT BY $timestamp --------" >> "$REPORT"
  if ./"$TARGET" $1 >> "$REPORT" 2>&1; then
    echo "Logged."
  else
    echo "Error while executing. Check $REPORT for detailed information"
  fi
else
  echo "Failed to assemble"
fi

