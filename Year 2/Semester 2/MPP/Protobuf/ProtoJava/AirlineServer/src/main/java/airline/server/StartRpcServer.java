package airline.server;

import airline.networking.utils.AbstractServer;
import airline.networking.utils.AirlineRpcConcurrentServer;
import airline.networking.utils.ServerException;
import airline.persistence.*;
import airline.server.impl.AirlineServicesImpl;
import airline.services.IService;
import java.io.IOException;
import java.util.Properties;

public class StartRpcServer {
    private static int defaultPort=55555;
    public static void main(String[] args) {
        // UserRepository userRepo=new UserRepositoryMock();
        Properties serverProps=new Properties();
        try {
            serverProps.load(StartRpcServer.class.getResourceAsStream("/bd.config"));
            System.out.println("Server properties set. ");
            serverProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find chatserver.properties "+e);
            return;
        }
        IFlightRepository flightRepository=new FlightRepository(serverProps);
        ITicketRepository ticketRepository=new TicketRepository(serverProps);
        IEmployeeRepository employeeRepository=new EmployeeRepository(serverProps);

        IService service=new AirlineServicesImpl(employeeRepository,ticketRepository,flightRepository);

        int ServerPort=defaultPort;
        try {
            ServerPort = Integer.parseInt(serverProps.getProperty("server.port"));
        }catch (NumberFormatException nef){
            System.err.println("Wrong  Port Number"+nef.getMessage());
            System.err.println("Using default port "+defaultPort);
        }
        System.out.println("Starting server on port: "+ServerPort);
        AbstractServer server = new AirlineRpcConcurrentServer(ServerPort, service);
        try {
            server.start();
        } catch (ServerException e) {
            System.err.println("Error starting the server" + e.getMessage());
        }finally {
            try {
                server.stop();
            }catch(ServerException e){
                System.err.println("Error stopping server "+e.getMessage());
            }
        }
    }
}
