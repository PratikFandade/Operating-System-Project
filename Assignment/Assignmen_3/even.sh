min=50
for i in `ls `
do
if [ ! -d $i ]
then
len1=${#i}
fi
if [ $len1 -lt $min ]
then
min=$len1
filename=$i
fi
done
echo "Smallest Filename: $filename"
echo "File Size: $min"