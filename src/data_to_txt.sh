 #!/bin/bash
# for i in `seq 1 5`;
# do
# 	echo 3 | ./Solution data2/expo_$i | grep "(" >> data2/expo_$i.txt
# done 
for i in `seq 0 4`;
do
	for j in `seq 0 2`;
	do
		echo 3 | ./Solution painting_data/${i}_${j} | grep "(" >> painting_data/${i}_${j}.txt
	done
done
