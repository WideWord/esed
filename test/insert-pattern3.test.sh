echo "Insert near pattern test 3"

export FILE_PREFIX="insert-pattern3"
export COMMAND="insert-above 433 xoxo"

./file_command.template.sh
exit $?
