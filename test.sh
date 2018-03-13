#!/bin/bash

if [ -z $1 ]; then
    echo "Usage: $0 <mysort_binary_name>"
    echo "mysort binary should be located in the top-level directory of the project"
    echo "  (in which the subdirectory tests/ is located)"
    echo "Please consider using \`make check' instead of this script"
    exit 1
fi

export execname="../../$1"

function die() {
    echo "Error: $@" >&2
    exit 1

    # If bash still continues to run
    kill $$
}

function warn() {
    echo "Warning: $@" >&2
}

{

tests_count=0
passed_tests_count=0

cd tests || die "tests/ directory not found"
for i in test*; do
    cd "$i" || { warn "unable to access directory '$i'"; continue; }

    options="`cat options.txt 2>/dev/null`"
    input="input.txt"
    real_output="output.txt"
    real_stderr="stderr.txt"
    ground_truth_output="gt-output.txt"

    passed="no"

    cat "$input" | "$execname" $options >"$real_output" 2>"$real_stderr"

    if diff "$real_output" "$ground_truth_output" &>/dev/null; then
        passed="yes"
        (( ++passed_tests_count ))
    fi
    (( ++tests_count ))
    echo -e "Test: $i Passed: $passed"

    cd ..
done

# FIXME: Не работает
#echo "=== Summary ==="
#echo "$tests_count tests total, $passed_tests_count passed, $(($tests_count-$passed_tests_count)) failed"

} | column -t
exit 0
