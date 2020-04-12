#!/bin/bash
echo "Enter a String:"
read str
len=${#str}
i=1
flag=0

while [ $i -le $len ]
do
ch1=`echo $str | cut -c $i`
ch2=`echo $str | cut -c $len`
if [ $ch1 != $ch2 ]
then 
flag=1
break
fi

i=`expr $i + 1`
len=`expr $len - 1`
done

if [ $flag -eq 0 ]
then
	echo "No. entered is palindrome"
else
	echo "No. entered is not palindrome"
fi

