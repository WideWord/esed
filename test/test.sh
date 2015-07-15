
export ESED_BINARY=esed

FAIL_CTR=0
PASS_CTR=0

for test in *.test.sh; do
	echo "Test $test"
	echo "-----------------------------"
	./$test
	TEST_STATUS=$?
	if [ "$TEST_STATUS" -eq "0" ]; then
		echo "+----+"
		echo "|PASS|" 
		echo "+----+"
		PASS_CTR=$((PASS_CTR + 1))
	else
		echo "*======*"
		echo "| FAIL |" 
		echo "*======*"
		FAIL_CTR=$((FAIL_CTR + 1))	
	fi
	echo "============================="
done

echo "/////////////////////////////"
echo "$PASS_CTR passed, $FAIL_CTR failed tests."
