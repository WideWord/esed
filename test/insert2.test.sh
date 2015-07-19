echo "Insert test 2"

export FILE_PREFIX="insert2"
export COMMAND="insert 1 aabb"

./file_command.template.sh
exit $?
