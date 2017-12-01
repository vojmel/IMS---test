#!/bin/bash
rm -f output.txt; 
touch output.txt;

# arrayLines=( 10 100 1000 2000 5000 10000 )
# arrayRam=( 256 512 1024 1536 2048)

# arrayLines=( 10 )
# arrayRam=( 1024 )

for r in "${arrayRam[@]}"
do
	# -Xms1024M -Xmx1024M
	m='M' 
	ram="-Xms$r$m -Xms$r$m"
	
	# echo $ram

	for l in "${arrayLines[@]}"
	do
		# java program $l >> output.txt

		java $ram program $l >> output.txt
		# ./clearcache.sh
	done
done
