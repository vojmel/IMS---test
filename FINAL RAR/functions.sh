#!/bin/bash

# rm -f output.txt; 
# touch output.txt;
rm ./output/*.csv;
rm ./output/*.log;

extention=".csv";

# arrayType=("JAVA" "DB")
arrayType=("ALL") 

# likeArray=("LIKE" "LIKEE")
likeArray=("LIKEE")

likeNumberArray=( 1000 )
# likeNumberArray=( 1000 100 10 1 )


# Tables ---------------------
arrayLines=( 	
				100 
				# 200 
				500 
				1000 
				2000
				5000 
				7500 
				10000
				# 15000  
				20000 
				# 25000 
				30000 
				# 40000 
				50000 
				75000 
				100000 
				# 150000
				200000
				250000
				# 500000 
				# 1000000 
				# 2000000
				# 5000000
				# 10000000
)

# Ram ---------------------
arrayRam=( 		

				2048
				# # 256 
				# # 512 
				# 1024 
				# # 1536
				# 2048 
				# # 3072 
				# 4048
				# # 6144
				# # 8096 
)

# IP ADRESS SETTING ---------------------
# matej 192.168.70.128
serverip=192.168.70.128;
# # vojta 192.168.0.51
# serverip="192.168.0.51";

columns="seq, first, last, age, street, city, state, zip, dollar, pick, date, email, digid, latitude, longitude, pick2, string, domain, float, ccnumber, bool, yn";

searchRow="seq";

for like in "${likeArray[@]}"
do
	for likeNumber in "${likeNumberArray[@]}"
	do
		for r in "${arrayRam[@]}"
		do
			m='M' 
			ram="-Xmx$r$m"

			for type in "${arrayType[@]}"
			do
				outfile="./output/$type-$like-$likeNumber-$r$extention";
				touch $outfile;

				echo "File $outfile"

				for currentTable in "${arrayLines[@]}"
				do
					for i in {1..5}
					do
						echo "clearing cache";
						# ./clearcache.sh
						./sshclear.sh
						
						echo "$outfile - current table is: $currentTable";
						# echo "Executing with: $ram current table is: $currentTable" >> output.txt;
						java $ram -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar $currentTable "$searchRow" $like $likeNumber "$columns" $type $serverip postgres postgres postgres $r >> $outfile  2>> $outfile.log ;
					done
				done
			done
		done
	done
done

spd-say task-completed
