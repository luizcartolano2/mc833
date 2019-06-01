import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMIInterface extends Remote {

    String handleOperation(String message) throws RemoteException;

}