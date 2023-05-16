package airline.networking.rpcprotocol;

import airline.model.Employee;
import airline.model.Flight;
import airline.model.Ticket;
import airline.services.IAirlineObserver;
import airline.services.IService;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class AirlineServicesRpcProxy implements IService {
    private String host;
    private int port;
    private IAirlineObserver client;
    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;
    private BlockingQueue<Response> qresponses;
    private volatile boolean finished;

    public AirlineServicesRpcProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses=new LinkedBlockingQueue<>();
    }

    public Employee login(Employee employee, IAirlineObserver client) throws Exception {
        initConnection();
        Request req=new Request.Builder().type(RequestType.LOGIN).data(employee).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()==ResponseType.OK){
            this.client=client;
            Employee employee_to_connect=(Employee) response.data();
            return employee_to_connect;
        }
        if (response.type()==ResponseType.ERROR){
            String err=response.data().toString();
            closeConnection();
            throw new Exception(err);
        }

        return null;
    }
    public void logout(Employee employee, IAirlineObserver client) throws Exception {
        Request req=new Request.Builder().type(RequestType.LOGOUT).data(employee).build();
        sendRequest(req);
        Response response=readResponse();
        closeConnection();
        if (response.type()==ResponseType.ERROR){
            String err=response.data().toString();
            throw new Exception(err);
        }
    }

    @Override
    public Iterable<Flight> getFlights(String destination, String date) throws Exception{
        Flight flight=new Flight(destination,date,"0",0);
        Request req=new Request.Builder().type(RequestType.GET_FLIGHTS).data(flight).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()==ResponseType.GET_FLIGHTS){
            Iterable<Flight> flights=(Iterable<Flight>) response.data();
            return flights;
        }
        else
            throw new Exception("Error getting flights");
    }

    @Override
    public Employee getEmployee(String username, String password) {
        return null;
    }

    @Override
    public void buyTicket(int flightId, String tourist_name, String client_address) throws Exception{
        Ticket ticket=new Ticket(tourist_name,client_address,flightId);
        Request req=new Request.Builder().type(RequestType.BUY_TICKET).data(ticket).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new Exception(err);
        }

    }

    @Override
    public int getNumberOfTicketsForFlight(Integer flightId) throws Exception{
        Request req=new Request.Builder().type(RequestType.GET_NUMBER_OF_TICKETS).data(flightId).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()==ResponseType.GET_NUMBER_OF_TICKETS_FOR_FLIGHT){
            int numberOfTickets=(int) response.data();
            return numberOfTickets;
        }
        else
            throw new Exception("Error getting number of tickets");

    }

    @Override
    public Iterable<Flight> getAllFlights() throws Exception{
        Request request=new Request.Builder().type(RequestType.GET_ALL_FLIGHTS).data(null).build();
        sendRequest(request);
        Response response=readResponse();
        if (response.type()==ResponseType.GET_ALL_FLIGHTS){
            Iterable<Flight> flights=(Iterable<Flight>) response.data();
            return flights;
        }
        else
            throw new Exception("Error getting flights");


    }

    private void initConnection() throws Exception {
        connection=new Socket(host,port);
        output=new ObjectOutputStream(connection.getOutputStream());
        output.flush();
        input=new ObjectInputStream(connection.getInputStream());
        finished=false;
        startReader();
    }
    private void closeConnection(){
        finished=true;
        try{
            input.close();
            output.close();
            connection.close();
            client=null;

        }
        catch (IOException ex){
            ex.printStackTrace();
        }
    }
    private void startReader(){
        Thread tw=new Thread(new ReaderThread());
        tw.start();
    }
    private boolean isUpdate(Response response){
        return response.type()==ResponseType.BUY_TICKET;
    }

    private void handleUpdate(Response response){
        if (response.type()==ResponseType.BUY_TICKET){
            System.out.println("Bought ticket update"+response.data());
            Ticket ticket=(Ticket) response.data();
            client.ticketBought(ticket);
        }
    }
    private class ReaderThread implements Runnable{
        @Override
        public void run() {
            while(!finished){
                try{
                    Object response=input.readObject();
                    System.out.println("Response received"+response);
                    if (isUpdate((Response) response)){
                        handleUpdate((Response) response);
                    }
                    else{
                        try{
                            qresponses.put((Response) response);
                        }
                        catch (InterruptedException ex){
                            System.out.println("Error "+ex);
                        }
                    }

                }
                catch (IOException | ClassNotFoundException ex){
                    //ex.printStackTrace();
                    System.out.println("Reading error "+ex);
                }
            }
        }
    }

    private void sendRequest(Request request) throws Exception{
        try{
           output.writeObject(request);
           output.flush();
        }
        catch (IOException ex){
            throw new Exception("Error sending object "+ex);
        }
    }

    private Response readResponse() throws Exception{
        Response response=null;
        try{
            response=qresponses.take();
        }
        catch (InterruptedException ex){
            ex.printStackTrace();
        }
        return response;
    }
}
