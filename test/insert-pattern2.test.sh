echo "Insert near pattern test 2"
echo ""


FILE_IN="insert-pattern2.in"
FILE_OUT="insert-pattern2.out"

echo "Input:"
cat $FILE_IN
echo ""
echo "Command: $ESED_BINARY insert-below 'a*d' 5678"
echo ""
echo "Output must be:"
cat $FILE_OUT
echo ""
echo ""

$ESED_BINARY insert-below 'a*d' 5678 -o tmp -i $FILE_IN
diff $FILE_OUT tmp >/dev/null
RESULT=$?

echo "Output is:"
cat tmp
echo ""

exit $RESULT

