import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import java.util.Scanner;

public class Client {

//    private static RMIInterface look_up;

    public static void main(String[] args)
            throws MalformedURLException, RemoteException, NotBoundException {
        try {
            Registry registry = LocateRegistry.getRegistry();
            RMIInterface stub = (RMIInterface) registry.lookup("RMIInterface");

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

            if (Integer.parseInt(serverRequest) != 5) {
                if (Integer.parseInt(serverRequest) == 1) {
                    System.out.println("Qual curso você deseja ver as pessoas formadas?");
                    message_to_send = scanner.nextLine();
                    serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
                } else if (Integer.parseInt(serverRequest) == 2) {
                    System.out.println("Qual cidade você deseja ver as habilidades?");
                    message_to_send = scanner.nextLine();
                    serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
                } else if (Integer.parseInt(serverRequest) == 3) {
                    System.out.println("Em que perfil iremos acrescentar experiência (email)?");
                    message_to_send = scanner.nextLine();
                    System.out.println("Qual experiência você deseja acrescentar?");
                    String temp2 = scanner.nextLine();
                    serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&").concat(temp2).concat("&");
                } else if (Integer.parseInt(serverRequest) == 4) {
                    System.out.println("Qual perfil você deseja ver as experiencias (email)?");
                    message_to_send = scanner.nextLine();
                    serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
                } else {
                    System.out.println("Qual perfil você deseja ver as informacoes (email)?");
                    message_to_send = scanner.nextLine();
                    serverRequest = serverRequest.concat("&").concat(message_to_send).concat("&");
                }
            } else {
                serverRequest = serverRequest.concat("&");
            }

            System.out.println("Operação solicitada ao servidor: " + serverRequest);

            String response = stub.handleOperation(serverRequest);
            System.out.println(response);
        }
        catch (Exception e) {
            System.out.println("Exiting...");
            System.out.println(e);
            System.exit(1);
        }
    }

}
