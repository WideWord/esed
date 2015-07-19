echo "Insert near pattern test 4"

export FILE_PREFIX="insert-pattern4"
export COMMAND="insert-above acd 1234"

./file_command.template.sh
exit $?
