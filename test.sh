#!/bin/bash

flags=(
dummy
""
"-n"
""
)

num_tests=3

failed_tests=0

for i in `seq 1 $num_tests`; do
    echo -n "Test $i: "
    cat tests/test"$i".txt | ./mysort ${flags[$i]} > tests/test"$i".out
    if diff tests/test"$i".out tests/test"$i".gt >/dev/null; then
        echo -e "\e[1;32mPass\e[0m"
    else
        echo -e "\e[1;31mFail\e[0m"
        failed_tests=$[$failed_tests + 1]
    fi
done

echo "***************"
echo "*** SUMMARY ***"
echo "***************"

echo "Total tests: $num_tests"
echo "Failed tests: $failed_tests"
echo "Passed tests: $[$num_tests - $failed_tests]"

return $failed_tests
