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

    private static String retorna_formandos_curso(String[][] db, String curso) {
        String resposta = "";
        Boolean encontrou = Boolean.FALSE;

        for(int i = 0; i < db.length; i++) {
            if (db[i][4].equals(curso)) {
                encontrou = Boolean.TRUE;
                resposta = resposta.concat(db[i][1]).concat(" ").concat(db[i][2]).concat("\n");
            }
        }

        if (encontrou) {
            return resposta;
        } else {
            return "Curso não encontrado!";
        }

    }

    private static String retorna_habilidades_cidade(String[][] db, String cidade) {
        String resposta = "";
        Boolean encontrou = Boolean.FALSE;

        for(int i = 0; i < db.length; i++) {
            if (db[i][3].equals(cidade)) {
                encontrou = Boolean.TRUE;
                resposta = resposta.concat(db[i][5]).concat("\n");
            }
        }

        if (encontrou) {
            return resposta;
        } else {
            return "Cidade não encontrado!";
        }

    }

    private static String acrescenta_experiencia_perfil(String db[][], String email, String experiencia) {
        Boolean encontrou = Boolean.FALSE;

        for(int i = 0; i < db.length; i++) {
            if (db[i][0].equals(email)) {
                encontrou = Boolean.TRUE;
                db[i][6] =  Integer.toString(Integer.parseInt(db[i][6]) + 1);
                db[i][7] = db[i][7].concat(experiencia).concat("&");
            }
        }

        if (encontrou) {
            return "Operação bem sucedida!";
        } else {
            return "Operação não realizada";
        }

    }

    private static String retorna_experiencia_perfil(String[][] db, String email) {
        String resposta = "";
        Boolean encontrou = Boolean.FALSE;

        for(int i = 0; i < db.length; i++) {
            if (db[i][0].equals(email)) {
                encontrou = Boolean.TRUE;
                String[] parts = db[i][7].split("&");
                for (int k = 0; k < parts.length; k++) {
                    resposta = resposta.concat(parts[k]).concat("\n");
                }
            }
        }

        if (encontrou) {
            return resposta;
        } else {
            return "Perfil não encontrado!";
        }

    }

    private static String retorna_perfil(String db[][], String email) {

        Boolean encontrou = Boolean.FALSE;
        String resposta = "";
        for(int i = 0; i < db.length; i++) {
            if (db[i][0].equals(email)) {
                encontrou = Boolean.TRUE;
                resposta = resposta.concat("Email: ").concat(db[i][0]).concat("\n");
                resposta = resposta.concat("Nome: ").concat(db[i][1]).concat(" ").concat(db[i][2]).concat("\n");
                resposta = resposta.concat("Cidade: ").concat(db[i][3]).concat("\n");
                resposta = resposta.concat("Curso: ").concat(db[i][4]).concat("\n");
                resposta = resposta.concat("Habilidades: ").concat(db[i][5]).concat("\n");
                String[] parts = db[i][7].split("&");
                for (int k = 0; k < parts.length; k++) {
                    resposta = resposta.concat("Experiência " + Integer.toString(k+1) + ": ").concat(parts[k]).concat("\n");
                }
                resposta = resposta.concat("---------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }

        if (encontrou) {
            return resposta;
        } else {
            return "Perfil não encontrado!";
        }

    }

    private static String retorna_perfis(String db[][]) {
        Boolean encontrou = Boolean.FALSE;
        String resposta = "";
        for (int i = 0; i < db.length; i++) {
            encontrou = Boolean.TRUE;
            resposta = resposta.concat(retorna_perfil(db, db[i][0]));
        }

        if (encontrou) {
            return resposta;
        } else {
            return "Não existem perfis!";
        }
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

        String resposta = "";
        switch (operation) {
            case 1:
                resposta = resposta.concat(retorna_formandos_curso(db, message));
                break;
            case 2:
                resposta = resposta.concat(retorna_habilidades_cidade(db, message));
                break;
            case 3:
                resposta = resposta.concat(acrescenta_experiencia_perfil(db, message, message2));
                break;
            case 4:
                resposta = resposta.concat(retorna_experiencia_perfil(db, message));
                break;
            case 5:
                resposta = resposta.concat(retorna_perfis(db));
                break;
            case 6:
                resposta = resposta.concat(retorna_perfil(db, message));
                break;
        }

        return resposta;

    }

    public static void main(String[] args){

        while (Boolean.TRUE) {
            try {
                Naming.rebind("//localhost/MyServer", new Server());
                System.err.println("Server ready");

            } catch (Exception e) {

                System.err.println("Server exception: " + e.toString());
                e.printStackTrace();

            }
        }
    }

}