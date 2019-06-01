package com.company;

import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

import java.util.Scanner;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileWriter;

public class Client {

    private static RMIInterface look_up;

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

    public static void main(String[] args)
            throws MalformedURLException, RemoteException, NotBoundException {

//        look_up = (RMIInterface) Naming.lookup("//localhost/MyServer");

        String [][] db = read_db();

        System.out.println(retorna_formandos_curso(db, "Ciência da Computação"));

        try {
            writeFile(db);
        } catch (IOException e) {
            System.out.println(e + "Exiting...");
            System.exit(1);
        }



        System.exit(0);

        Scanner scanner = new Scanner(System.in);

        // show operations
        System.out.print("(1) listar todas as pessoas formadas em um determinado curso\n(2) listar as habilidades dos perfis que moram em uma determinada cidade;\n(3) acrescentar uma nova experiência em um perfil;\n(4) dado o email do perfil, retornar sua experiência;\n(5) listar todas as informações de todos os perfis;\n(6) dado o email de um perfil, retornar suas informações.\n");

        String serverRequest = "0";
        try {
            serverRequest = scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Exiting...");
            System.exit(1);
        }

        if (Integer.parseInt(serverRequest) < 1 || Integer.parseInt(serverRequest) > 6) {
            System.out.println("Invalid Operation, exiting...");
            System.exit(1);
        }

        String message_to_send;

        if (Integer.parseInt(serverRequest) != 5){
            if (Integer.parseInt(serverRequest) == 1) {
                System.out.println("Qual curso você deseja ver as pessoas formadas?");
                message_to_send = scanner.nextLine();
                serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
            }
            else if (Integer.parseInt(serverRequest) == 2) {
                System.out.println("Qual cidade você deseja ver as habilidades?");
                message_to_send = scanner.nextLine();
                serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
            }
            else if (Integer.parseInt(serverRequest) == 3) {
                System.out.println("Em que perfil iremos acrescentar experiência (email)?");
                message_to_send = scanner.nextLine();
                System.out.println("Qual experiência você deseja acrescentar?");
                String temp2 = scanner.nextLine();
                serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&").concat(temp2).concat("&");
            }
            else if (Integer.parseInt(serverRequest) == 4) {
                System.out.println("Qual perfil você deseja ver as experiencias (email)?");
                message_to_send = scanner.nextLine();
                serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
            }
            else
            {
                System.out.println("Qual perfil você deseja ver as informacoes (email)?");
                message_to_send = scanner.nextLine();
                serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
            }
        } else {
            serverRequest = serverRequest.concat("&");
        }

        System.out.println("Operação solicitada ao servidor: " + serverRequest);


        System.exit(0);
//        String response = look_up.handleOperation(txt);
//        JOptionPane.showMessageDialog(null, response);

    }

}
