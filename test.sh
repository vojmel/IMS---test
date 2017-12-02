#!/bin/bash
# rm -f output.txt; 
# touch output.txt;
rm ./output/*.csv;
extention=".csv";

arrayType=("DB" "JAVA")


# Tables ---------------------
arrayLines=( 	
				100 
				# 200 
				# 500 
				# 1000 
				# 2000 
				# 5000 
				# 7500 
				# 10000 
				# 15000 
				# 20000 
				# 25000 
				# 30000 
				# 40000 
				# 50000 
				# 75000 
				# 100000 
				# 150000 
				# 200000 
				# 250000 
				# 500000 
				# 1000000 
				# 10000000
)

# Ram ---------------------
arrayRam=( 		
				# 256 
				# 512 
				# 1024 
				# 1536 
				2048 
				# 3072 
				# 4048 
				# 6144
				# 8096 
)

# IP ADRESS SETTING ---------------------
# matej 192.168.70.128
serverip=192.168.70.128;
# # vojta 192.168.0.51
# serverip="192.168.0.51";

columns="seq, first, last, age, street, city, state, zip, dollar, pick, date, email, digid, latitude, longitude, pick2, string, domain, float, ccnumber, bool, yn";

searchRow="seq";





for r in "${arrayRam[@]}"
do
	m='M' 
	ram="-Xmx$r$m"

	for type in "${arrayType[@]}"
	do
		outfile="./output/$type-output-$r$extention";
		touch $outfile;

		echo "File $outfile"

		for currentTable in "${arrayLines[@]}"
		do
			echo "clearing cache";
			./clearcache.sh

			echo "$outfile - current table is: $currentTable";
			# echo "Executing with: $ram current table is: $currentTable" >> output.txt;
			java $ram -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar $currentTable "$searchRow" LIKE 1 "$columns" $type $serverip postgres postgres postgres >> $outfile;
		done
	done
done

