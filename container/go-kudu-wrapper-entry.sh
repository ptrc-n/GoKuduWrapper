#!/bin/bash

set -e
. /etc/profile

if [[ "$1" == "tests" ]]; then
  # start kudu cluster
  bash /kudu-entrypoint.sh master &> kudu-master.log &
  bash /kudu-entrypoint.sh tserver &> kudu-tserver.log &
  # wait for tserver to register with master
  # sleep 20
  # run software tests
  pwd
  go run testing/kudu_tests.go
  exit 0
fi

exec "$@"