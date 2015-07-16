echo "Removing line test 2"

export FILE_PREFIX="remove2"
export COMMAND="remove 2"

./file_command.template.sh
exit $?
