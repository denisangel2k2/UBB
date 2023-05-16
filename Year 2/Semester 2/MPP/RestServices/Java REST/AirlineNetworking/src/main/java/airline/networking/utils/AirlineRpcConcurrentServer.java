package airline.networking.utils;

import airline.networking.rpcprotocol.AirlineClientRpcWorker;
import airline.services.IService;

import java.net.Socket;


public class AirlineRpcConcurrentServer extends AbsConcurrentServer {
    private IService service;
    public AirlineRpcConcurrentServer(int port, IService service) {
        super(port);
        this.service = service;
        System.out.println("Chat- ChatRpcConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        AirlineClientRpcWorker worker=new AirlineClientRpcWorker(service, client);

        Thread tw=new Thread(worker);
        return tw;
    }

    @Override
    public void stop(){
        System.out.println("Stopping services ...");
    }
}
