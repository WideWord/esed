echo "Removing line test 1"

export FILE_PREFIX="remove1"
export COMMAND="remove 1"

./file_command.template.sh
exit $?
