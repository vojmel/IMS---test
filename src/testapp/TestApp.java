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
        // TODO code application logic here
        System.out.println("test");
        
        
        testFilterSpeed tester = new testFilterSpeed();
        
        if (tester.getDbConnection() == null) {
            System.err.println("No db connection");
            return;
        }
        
        long time;
        
        // Prvni nacteni tabulky
        time = tester.getDataFromDb("tableName", "col1, col2, col3");
        System.out.println("Time for aelect all: "+time);
        
    
        // Filtrace pres DB
        time = tester.filterByDb("col1", testFilterSpeed.conditionType.like, "1");
        System.out.println("Time filter by db: "+time);
        
        // Filter pres JAVA
        time = tester.filterByJava("col1", testFilterSpeed.conditionType.like, "1");
        System.out.println("Time filter by JAVA: "+time);
        
        
        
        // odpojeni db
        tester.disconectDb();
        
        return;
    }
    
}
