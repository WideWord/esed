echo "Removing line test 11"

export FILE_PREFIX="remove11"
export COMMAND="remove 1"

./file_command.template.sh
exit $?
