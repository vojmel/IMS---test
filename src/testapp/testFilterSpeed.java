/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testapp;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import org.postgresql.*;
/**
 *
 * @author Meluzin
 */
public class testFilterSpeed {
    
    
    private String host = "192.168.0.51";
    private int port = 5432;
    private String dbName = "postgres";
    private String user = "postgres";
    private String pass = "postgres";
    
    private long selectFirstTime = 0;
    private long selectNTime = 0;
    private long createObjTime = 0;
    private long filterTime = 0;
    
    
    Connection conn = null;
    
    private String tableName;
    private String coloumns;
    
    public enum conditionType {
        eqeuals, // ==
        like, // like '%...%'
        likeS, // like '%...'
        likeE  // like '...%'
    };
    
    ArrayList<Item> items = new ArrayList<Item>();
    
    
    ArrayList<Item> itemsFiltred = new ArrayList<Item>();

    
    public testFilterSpeed() {
    }
    
    public testFilterSpeed(String host, int port, String dbName, String user, String pass) {
        this.host = host;
        this.port = port;
        this.dbName = dbName;
        this.user = user;
        this.pass = pass;
    }

    public void setHost(String host) {
        this.host = host;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public void setDbName(String dbName) {
        this.dbName = dbName;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public void setPass(String pass) {
        this.pass = pass;
    }

    public void setConn(Connection conn) {
        this.conn = conn;
    }

    public void setTableName(String tableName) {
        this.tableName = tableName;
    }

    public void setColoumns(String coloumns) {
        this.coloumns = coloumns;
    }

    public void setItems(ArrayList<Item> items) {
        this.items = items;
    }

    public void setItemsFiltred(ArrayList<Item> itemsFiltred) {
        this.itemsFiltred = itemsFiltred;
    }

    public long getCreateObjTime() {
        return createObjTime;
    }

    public long getFilterTime() {
        return filterTime;
    }

    public long getSelectFirstTime() {
        return selectFirstTime;
    }

    public long getSelectNTime() {
        return selectNTime;
    }

    
    
    
    
    
    
    // connect to db
    public Connection getDbConnection() {
        
        if (conn == null) {
            //System.out.println("COnnectiong to DB.");
            try {
                try {
                    Class.forName("org.postgresql.Driver");
                } catch (ClassNotFoundException ex) {
                    Logger.getLogger(testFilterSpeed.class.getName()).log(Level.SEVERE, null, ex);
                }
                conn = DriverManager.getConnection("jdbc:postgresql://"+host+":"+port+"/"+dbName+"", user, pass);
                conn.setAutoCommit(false);
            } catch (SQLException e) {
                System.out.println("Connection Failed! Check output console");
                e.printStackTrace();
                return null;
            }
        }

        return conn;
    }
    
    
    public void executeComand(String comand) {
        
        if (getDbConnection() != null) {
            try {
                Statement stmt = null;
                stmt = conn.createStatement();
                stmt.executeUpdate(comand);
            } catch (SQLException ex) {
                Logger.getLogger(testFilterSpeed.class.getName()).log(Level.SEVERE, null, ex);
            } finally {
                System.out.println("Ok");
            }
        }
        
    }
    
    public void disconectDb() {
        
        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException ex) {
                Logger.getLogger(testFilterSpeed.class.getName()).log(Level.SEVERE, null, ex);
            }
            conn = null;
        }
    }
    
    
    /*
    *
    * tableName = nazev tabulky
    * coloumns = vycet sloupcu oddelenych ,
    */
    public long getDataFromDb(String tableName, String coloumns) {
        
        // test conn
        if (getDbConnection() == null) {
            System.out.println("Can't connect to db.");
            return 0;
        }
        this.tableName = tableName;
        this.coloumns = coloumns;
        
        // priprava sql
        String selectTableSQL = "SELECT "+coloumns+" from "+tableName;
        //System.out.println("SQL:"+selectTableSQL);
        
        Statement statement = null;
        
        long start_time = System.nanoTime(); // start time
        selectFirstTime = 0;
        
        try {
            
            statement = conn.createStatement();

            // execute select SQL stetement
            ResultSet rs = statement.executeQuery(selectTableSQL);
            
            // ulozeni casu
            selectFirstTime = (System.nanoTime() - start_time);
            
            // Process result
            processSQLResult(rs);

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            
        } finally {
            if (statement != null) {
                try {
                    statement.close();
                } catch (SQLException ex) {
                    Logger.getLogger(testFilterSpeed.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        
        long end_time = System.nanoTime();
        return (end_time - start_time);
    }
    

    
    
    //
    // Filtruje aktualni tabulku podle 
    public long filterByDb(String coloumn, conditionType condition, String value) {
        // test conn
        if (getDbConnection() == null) {
            System.out.println("Can't connect to db.");
            return 0;
        }
        
        if (coloumn.equalsIgnoreCase("")) {
            System.out.println("Wrong argument coloumn. Must be setted.");
            return 0;
        }
        if (value.equalsIgnoreCase("")) {
            System.out.println("Wrong argument value. Must be setted.");
            return 0;
        }
        
        // priprava sql
        String where = coloumn+"::text ";
        switch (condition) {
            case like:
                where += "LIKE '%"+value+"%'";
                break;
            case likeS:
                where += "LIKE '%"+value+"'";
                break;
            case likeE:
                where += "LIKE '"+value+"%'";
                break;
            case eqeuals:
                where += "= '"+value+"'";
                break;
        }
        
        String selectTableSQL = "SELECT "+coloumns+" from "+tableName+ " WHERE "+where;
        //System.out.println("SQL: "+selectTableSQL);
        
        Statement statement = null;
        
        long start_time = System.nanoTime(); // start time
        selectNTime = 0;
        
        try {
            
            statement = conn.createStatement();

            // execute select SQL stetement
            ResultSet rs = statement.executeQuery(selectTableSQL);
            
            // ulozeni casu
            selectNTime = (System.nanoTime() - start_time);
            
            // Process result
            processSQLResult(rs);

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            
        } finally {
            if (statement != null) {
                try {
                    statement.close();
                } catch (SQLException ex) {
                    Logger.getLogger(testFilterSpeed.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        
        long end_time = System.nanoTime();
        return (end_time - start_time);
    }
    
    public long filterByJava(String colounm, conditionType condition, String value) {
        
        long start_time = System.nanoTime(); // start time
        filterTime = 0;
        
        itemsFiltred.clear();
        
        for (Item item: items) {
            boolean add = false;
            switch (condition) {
                case like:
                    add = item.compareLike(colounm, value);
                    break;
                case likeS:
                    add = item.compareLikeStart(colounm, value);
                    break;
                case likeE:
                    add = item.compareLikeEnd(colounm, value);
                    break;
                case eqeuals:
                    add = item.compareEquals(colounm, value);
                    break;
            }
            if (add) {
                itemsFiltred.add(item);
            }
        }
        
        long end_time = System.nanoTime();
        filterTime = (end_time - start_time);
        return (end_time - start_time);
    }
    
    //
    // Projde RS a nacte ho do pameti
    private void processSQLResult(ResultSet rs) {
        
        items.clear();
        
        long start_time =  System.nanoTime();
        createObjTime = 0;
        
        try {
            // process result
            
            final ResultSetMetaData meta = rs.getMetaData();
            
            while (rs.next()) {
                items.add(new Item(rs));
            }
        } catch (SQLException ex) {
            Logger.getLogger(testFilterSpeed.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        // ulozeni casu
        createObjTime =  System.nanoTime() - start_time;
    }
    
    
    
    public long getItemsCnt() {
        return items.size();
    }
    
    public long getJavaFiltredItemsCnt() {
        return itemsFiltred.size();
    }
}
