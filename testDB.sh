#!/bin/bash
rm -f output.txt; 
touch output.txt;



# matej 192.168.70.128
serverip=192.168.70.128;

# # vojta 192.168.0.51
# serverip="192.168.0.51";

rowsNumber=1000;

columns="seq, first, last, age, street, city, state, zip, dollar, pick, date, email, digid, latitude, longitude, pick2, string, domain, float, ccnumber, bool, yn";

searchRow="seq";


./clearcache.sh


# java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar 1000 "seq" LIKE 1 "seq, first, last, age, street, city, state, zip, dollar, pick, date, email, digid, latitude, longitude, pick2, string, domain, float, ccnumber, bool, yn" DB 192.168.70.128 postgres postgres postgres >> output.txt
java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar $rowsNumber "$searchRow" LIKE 1 "$columns" DB $serverip postgres postgres postgres >> output.txt


java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar $rowsNumber "$searchRow" LIKE 1 "$columns" DB $serverip postgres postgres postgres >> output.txt

./clearcache.sh


java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar $rowsNumber "$searchRow" LIKE 1 "$columns" DB $serverip postgres postgres postgres >> output.txt

# ./clearcache.sh

# java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar $rowsNumber $searchRow LIKE 1 "$columns" JAVA $serverip postgres postgres postgres >> output.txt
# java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar $rowsNumber $searchRow LIKE 1 $columns JAVA $serverip postgres postgres postgres >> output.txt



