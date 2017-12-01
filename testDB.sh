#!/bin/bash
rm -f output.txt; 
touch output.txt;


./clearcache.sh



java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar 100 "id" LIKE 1 "id, name" DB 192.168.0.51 postgres postgres postgres >> output.txt


java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar 100 "id" LIKE 1 "id, name" DB 192.168.0.51 postgres postgres postgres >> output.txt


./clearcache.sh


java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar 100 "id" LIKE 1 "id, name" DB 192.168.0.51 postgres postgres postgres >> output.txt


./clearcache.sh

java -cp ./lib/postgresql-9.4.1209.jar: -jar ./dist/testApp.jar 100 "id" LIKE 1 "id, name" JAVA 192.168.0.51 postgres postgres postgres >> output.txt
