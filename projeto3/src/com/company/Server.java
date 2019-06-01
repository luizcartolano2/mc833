package com.company;

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileWriter;

public class Server extends UnicastRemoteObject implements RMIInterface{

    private static final long serialVersionUID = 1L;

    protected Server() throws RemoteException {

        super();

    }

    private static String[][] read_db() {
        BufferedReader reader;
        String [][] db = new String[5][8];
        try {
            reader = new BufferedReader(new FileReader("db.txt"));

            String line = reader.readLine();
            int count_pessoa = 0;
            int count_linha = 0;

            while (line != null) {
                while (count_linha < 8) {
                    if (count_linha == 6) {
                        int temp_conta = Integer.parseInt(line);
                        db[count_pessoa][count_linha] = line;
                        line = reader.readLine();
                        count_linha = count_linha + 1;
                        db[count_pessoa][count_linha] = line;
                        db[count_pessoa][count_linha] = db[count_pessoa][count_linha].concat("&");
                        for (int i = 1; i < temp_conta; i++) {
                            line = reader.readLine();
                            db[count_pessoa][count_linha] = db[count_pessoa][count_linha].concat(line).concat("&");
                        }
                    }
                    else {
                        db[count_pessoa][count_linha] = line;
                        line = reader.readLine();
                    }
                    count_linha = count_linha + 1;
                }
                line = reader.readLine();
                count_pessoa = count_pessoa + 1;
                count_linha =0;
            }

        } catch (IOException e) {
            System.out.println("Exiting..." + e);
            System.exit(1);
        }

        return db;

    }

    private static void writeFile(String[][] db) throws IOException {
        FileWriter fw = new FileWriter("db.txt");


        for (int i = 0; i < db.length; i++) {
            for (int j = 0; j < db[i].length; j++) {
                if (j == 7) {
                    String[] parts = db[i][j].split("&");
                    for (int k = 0; k < parts.length; k++) {
                        fw.write(parts[k]);
                        fw.write("\n");
                    }
                } else {
                    fw.write(db[i][j]);
                    fw.write("\n");
                }
            }
        }

        fw.close();
    }

    @Override
    public String handleOperation(String serverRequest) throws RemoteException{

        String [][] db = read_db();

        int operation = 0;
        String message = "ODEIO JAVA PQP";
        String message2 = "ODEIO JAVA PQP";

        String[] parts = serverRequest.split("&");
        if (parts.length == 1) {
            operation = Integer.parseInt(parts[0]);
        }
        else if (parts.length == 2) {
            operation = Integer.parseInt(parts[0]);
            message = parts[1];
        }
        else {
            operation = Integer.parseInt(parts[0]);
            message = parts[1];
            message2 = parts[2];
        }

        try {
            writeFile(db);
        } catch (IOException e) {
            System.out.println(e + "Exiting...");
            System.exit(1);
        }

        return "Server says hello to " + message;

    }

    public static void main(String[] args){

        try {

            Naming.rebind("//localhost/MyServer", new Server());
            System.err.println("Server ready");

        } catch (Exception e) {

            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();

        }

    }

}