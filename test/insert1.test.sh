echo "Insert test 1"

export FILE_PREFIX="insert1"
export COMMAND="insert 1 aabb"

./file_command.template.sh
exit $?
