echo "Program compilation"
echo ""

(cd ../src && exec make clean >/dev/null)
(cd ../src && exec make >/dev/null)

if [ "$?" -ne "0" ]; then
	echo "Program does not compile"
	exit 1
fi

echo "Program does compile"
exit 0
