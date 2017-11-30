/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testapp;

/**
 *
 * @author Meluzin
 */
public class TestApp {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // rows_num    columnName   operace_porovnani   hodnota   vycet_vsech_sloupcu  [DB|JAVA]  host dbName user pass
        //vojta.java 10000 "col1" LIKE "1" [DB|JAVA] localhost postgres postgres postgres 

        int rowNum = new Integer(args[0]);
        String coloumn = args[1];
        String operation = args[2];
        String value = args[3];
        String coloumns = args[4];
        String by = args[5];
        String host = args[6];
        String dbName = args[7];
        String user = args[8];
        String pass = args[9];
        int pocetOpakovani = 15;
        
        // Get typ filtrace
        testFilterSpeed.conditionType filterType = null;
        if (operation.equalsIgnoreCase("LIKE")) {
            filterType = testFilterSpeed.conditionType.like;
        }
        if (operation.equalsIgnoreCase("LIKES")) {
            filterType = testFilterSpeed.conditionType.likeS;
        }
        if (operation.equalsIgnoreCase("LIKEE")) {
            filterType = testFilterSpeed.conditionType.likeE;
        }
        if (operation.equalsIgnoreCase("EQEUALS")) {
            filterType = testFilterSpeed.conditionType.eqeuals;
        }
        if (filterType == null) {
            System.out.println("Wrong compare operation type. Use LIKE, LIKES, LIKEE, EQEUALS");
            return;
        }
        
        // Connect to DB
        testFilterSpeed tester = new testFilterSpeed(host, 5432, dbName, user, pass);
        if (tester.getDbConnection() == null) {
            System.out.println("Can't connect to db.");
            return;
        }
        
        // Porovnova db
        if (by.equalsIgnoreCase("DB")) {
            
            // Ziskani dat z db poprve
            long time = tester.getDataFromDb("rows"+rowNum, coloumns);
            
            long firstTime = tester.filterByDb(coloumn, filterType, value);
            long numOfItems = tester.getItemsCnt();
            
            long avgTime = 0;
            for (int i = 0; i < pocetOpakovani; i++) {
                avgTime += tester.filterByDb(coloumn, filterType, value);
                if (numOfItems != tester.getItemsCnt()) {
                    System.out.println("!!!!!!!!!!!!!!NESOUHLASI POCET FILTROVAY ITEMU!!!!!!!!!!");
                    return;
                }
            }
            avgTime = avgTime/pocetOpakovani;
            
            
            // odpojeni db
            tester.disconectDb();

            System.out.println("DB;"+rowNum+";"+coloumn+";"+operation+";"+value+";"+numOfItems+";"+firstTime+";"+avgTime);
        }
        // Porovnava JAVA
        else if (by.equalsIgnoreCase("JAVA")) {
            
            // Ziskani dat z db
            long time = tester.getDataFromDb("rows"+rowNum, "id, name");
            
            long firstTime = tester.filterByJava(coloumn, filterType, value);
            long numOfItems = tester.getJavaFiltredItemsCnt();
            
            long avgTime = 0;
            for (int i = 0; i < pocetOpakovani; i++) {
                avgTime += tester.filterByJava(coloumn, filterType, value);
                if (numOfItems != tester.getJavaFiltredItemsCnt()) {
                    System.out.println("!!!!!!!!!!!!!!NESOUHLASI POCET FILTROVAY ITEMU!!!!!!!!!!");
                    return;
                }
            }
            avgTime = avgTime/pocetOpakovani;

            
            // odpojeni db
            tester.disconectDb();
        
            System.out.println("JAVA;"+rowNum+";"+coloumn+";"+operation+";"+value+";"+numOfItems+";"+firstTime+";"+avgTime);
        }
        else {
            System.out.println("Wrong filtration type: "+by+" use DB or JAVA");
            return; 
        }
        
    }
    
}
