#!/bin/bash

export BENCHTIME=7

function doBench {
  TIMEFORMAT="%3U"
  (
    time (
      SIG=1
      NUM=0
      trap SIG=0 SIGALRM
      read PID REST </proc/self/stat
      (
        sleep $BENCHTIME
	kill -SIGALRM $PID
      ) &
      while [[ $SIG -gt 0 ]]; do
        "$@" >/dev/null 2>&1
        NUM=$(($NUM+1))
      done
      echo -n "$NUM "
    ) 2>&1
  ) | while read N T; do
    echo "$T/$N" | bc -ql
  done
}

doBench "$@"

