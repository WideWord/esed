echo "Insert near pattern test 1"

export FILE_PREFIX="insert-pattern1"
export COMMAND="insert-above acd 1234"

./file_command.template.sh
exit $?
