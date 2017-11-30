/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testapp;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Jeden radek
 * 
 * @author Meluzin
 */
public class Item {
    
    
    HashMap<String, String> attributes = new HashMap<String, String>();

    public Item(ResultSet rs) {
        
        attributes.clear();
        
        if (rs == null) {
            System.err.println("Rs is null.");
            return;
        }
        
        try {
            ResultSetMetaData rsmd = rs.getMetaData();
            int RowCnt = rsmd.getColumnCount();

            // for each coloumn
            for (int column = 1; column <= RowCnt; ++column) {

                final Object value = rs.getObject(column);
                String name = rsmd.getColumnName(column);

                attributes.put(name, String.valueOf(value));
            }
        } catch (SQLException ex) {
            Logger.getLogger(Item.class.getName()).log(Level.SEVERE, null, ex);
            System.err.println("Error create item.");
        }
    }
      
    //
    // Porovnani presne odpovidajici
    public boolean compareEquals(String coloumnName, String value) {
        if (attributes.get(coloumnName) == null) {
            return false;
        }
        
        return attributes.get(coloumnName).equalsIgnoreCase(value);
    }
    
    //
    // Zajima nas zacatek jedno je nam konec
    public boolean compareLikeStart(String coloumnName, String value) {
        if (attributes.get(coloumnName) == null) {
            return false;
        }
        
        return attributes.get(coloumnName).endsWith(value);
    }
    
    //
    // Zajima nas konec jedno je nam zacatek
    public boolean compareLikeEnd(String coloumnName, String value) {
        if (attributes.get(coloumnName) == null) {
            return false;
        }
        
        return attributes.get(coloumnName).startsWith(value);
    }
    
    //
    // Jen pokud obsahuje
    public boolean compareLike(String coloumnName, String value) {
        if (attributes.get(coloumnName) == null) {
            return false;
        }
        
        return (0 <= attributes.get(coloumnName).indexOf(value));
    }
    
    
}
