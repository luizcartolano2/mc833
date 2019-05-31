package com.company;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMIInterface extends Remote {

    public String handleOperation(String message) throws RemoteException;

}