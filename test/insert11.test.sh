echo "Insert test 11"

export FILE_PREFIX="insert11"
export COMMAND="insert 2 12345678890"

./file_command.template.sh
exit $?
