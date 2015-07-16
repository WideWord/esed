echo "Removing line test 3"

export FILE_PREFIX="remove3"
export COMMAND="remove 5"

./file_command.template.sh
exit $?
