echo "Insert test 10"

export FILE_PREFIX="insert10"
export COMMAND="insert 2 abcd"

./file_command.template.sh
exit $?
