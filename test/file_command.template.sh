FILE_IN="${FILE_PREFIX}.in"
FILE_OUT="${FILE_PREFIX}.out"


echo ""
echo "Input:"
cat $FILE_IN
echo ""
echo "Command: $ESED_BINARY $COMMAND"
echo ""
echo "Output must be:"
cat $FILE_OUT
echo ""
echo ""

$ESED_BINARY -i $FILE_IN -o tmp $COMMAND
diff $FILE_OUT tmp >/dev/null
RESULT=$?


echo "Outbut is:"
cat tmp
echo ""

exit $RESULT
