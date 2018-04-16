#!/bin/bash

declare -Ag lang

if locale | grep LC_MESSAGES | grep -q ru_RU; then
    lang[Usage]='Usage'
    lang[usage_info]='<исполняемый_файл_mysort>
Исполняемый файл mysort должен быть расположен в папке проекта
  (в которой расположен подкатолог tests/)
Советуем использовать "make check" вместо непосредственного выполнения этого скрипта'
    lang[Error]='Ошибка'
    lang[Warning]='Предепреждение'
    lang[Usage]='Использование'
    lang[tests_not_found]='папка tests/ не найдена'
    lang[unable_to_access_dir]='невозможно получить доступ к папке'
    lang[Test]='Тест'
    lang[Passed]='Пройден'
    lang[yes]='да'
    lang[no]='нет'
else
    lang[Usage]='Usage'
    lang[usage_info]='<mysort_binary_name>
mysort binary should be located in the top-level directory of the project
  (in which the subdirectory tests/ is located)
Please consider using "make check" instead of directly running this script'
    lang[Error]='Error'
    lang[Warning]='Warning'
    lang[Usage]='Usage'
    lang[tests_not_found]='tests/ directory not found'
    lang[unable_to_access_dir]='unable to access directory'
    lang[Test]='Test'
    lang[Passed]='Passed'
    lang[yes]='yes'
    lang[no]='no'
fi



if [ -z $1 ]; then
    echo "${lang[Usage]}: $0 ${lang[usage_info]}"
    exit 1
fi

export execname="../../$1"

function die() {
    echo "${lang[Error]}: $@" >&2
    exit 1

    # If bash still continues to run
    kill $$
}

function warn() {
    echo "${lang[Warning]}: $@" >&2
}

{

tests_count=0
passed_tests_count=0

cd tests || die "${lang[tests_not_found]}"
for i in test*; do
    cd "$i" || { warn "${lang[unable_to_access_dir]} '$i'"; continue; }

    options="`cat options.txt 2>/dev/null`"
    input="input.txt"

    if [ -f "config-output-file.txt" ]; then
        real_output="`cat config-output-file.txt`"
    else
        real_output="output.txt"
    fi
    real_stderr="stderr.txt"
    ground_truth_output="gt-output.txt"

    passed="no"

    cat "$input" | "$execname" $options >"$real_output" 2>"$real_stderr"

    if diff "$real_output" "$ground_truth_output" &>/dev/null; then
        passed="yes"
        (( ++passed_tests_count ))
    fi
    (( ++tests_count ))
    echo -e "${lang[Test]}: $i ${lang[Passed]}: ${lang[$passed]}"

    cd ..
done

} | column -t
exit 0
