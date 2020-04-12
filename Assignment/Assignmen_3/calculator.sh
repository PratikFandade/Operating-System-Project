#!/bin/bash

echo "******************Calculator*******************"
echo "1. ADD	2.SUB	3.MUL	4.DIV	5.EXIT"

choice=0

while [ $choice -ne 5 ]
do
	echo "Enter your choice:"
	read choice

	case $choice in
		1)  echo "Enter 2 no.s"
			read n1 n2
			n3=`expr $n1 + $n2`;;
		2)  echo "Enter 2 no.s"
			read n1 n2
			n3=`expr $n1 - $n2`;;
		3)  echo "Enter 2 no.s"
			read n1 n2
			n3=`expr $n1 \* $n2`;;
		4)  echo "Enter 2 no.s"
			read n1 n2
			n3=`expr $n1 / $n2`;;
		5)  exit;;
		*)  echo "Enter a correct value";;
	esac
	echo "Answer is $n3"
done