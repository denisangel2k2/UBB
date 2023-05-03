package JavaSocket.protobuffnet;

import airline.model.Employee;
import airline.model.Flight;
import airline.model.Ticket;
import airline.services.IAirlineObserver;
import airline.services.IService;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ProtoProxy implements IService {

    private String host;
    private int port;
    private IAirlineObserver client;
    private InputStream input;
    private OutputStream output;
    private Socket connection;
    private BlockingQueue<Protobuffs.Response> qresponses;
    private volatile boolean finished;

    public ProtoProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses=new LinkedBlockingQueue<>();
    }
    public Employee login(Employee employee, IAirlineObserver client) throws Exception {
        initConnection();
        Protobuffs.Request req=Converter.createLoginRequest(employee);
        sendRequest(req);
        Protobuffs.Response response=readResponse();
        if (response.getType()==Protobuffs.Response.Type.OK){
            this.client=client;
            Employee employee_to_connect=Converter.getEmployee(response);
            return employee_to_connect;
        }
        if (response.getType()==Protobuffs.Response.Type.ERROR){
            String err=Converter.getError(response);
            closeConnection();
            throw new Exception(err);
        }
        return null;
    }
    public void logout(Employee employee, IAirlineObserver client) throws Exception {
        Protobuffs.Request req=Converter.createLogoutRequest(employee);
        sendRequest(req);
        Protobuffs.Response response=readResponse();
        closeConnection();
        if (response.getType()==Protobuffs.Response.Type.ERROR){
            String err=Converter.getError(response);
            throw new Exception(err);
        }
        else{
            System.out.println("Logout successful");
        }
    }

    @Override
    public Iterable<Flight> getFlights(String destination, String date) throws Exception{
        Flight flight=new Flight(destination,date,"0",0);
        Protobuffs.Request req=Converter.createGetFlightsRequest(flight);
        sendRequest(req);
        Protobuffs.Response response=readResponse();
        if (response.getType()==Protobuffs.Response.Type.GET_FLIGHTS){
            Iterable<Flight> flights=Converter.getFlights(response);
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
        Protobuffs.Request req=Converter.createAddTicketRequest(ticket);
        sendRequest(req);
        Protobuffs.Response response=readResponse();
        if (response.getType()==Protobuffs.Response.Type.ERROR) {
            String err = Converter.getError(response);
            throw new Exception(err);
        }

    }
    @Override
    public int getNumberOfTicketsForFlight(Integer flightId) throws Exception{
        Protobuffs.Request req=Converter.createGetNumberOfTicketsRequest(flightId);

        sendRequest(req);
        Protobuffs.Response response=readResponse();
        if (response.getType()==Protobuffs.Response.Type.GET_NUMBER_OF_TICKETS_FOR_FLIGHT){
            int numberOfTickets=Converter.getNumberOfTickets(response);
            return numberOfTickets;
        }
        else
            throw new Exception("Error getting number of tickets");

    }

    @Override
    public Iterable<Flight> getAllFlights() throws Exception{
        Protobuffs.Request request=Converter.createGetAllFlightsRequest();
        sendRequest(request);
        Protobuffs.Response response=readResponse();
        if (response.getType()==Protobuffs.Response.Type.GET_ALL_FLIGHTS){
            Iterable<Flight> flights=Converter.getAllFlights(response);
            return flights;
        }
        else
            throw new Exception("Error getting flights");


    }

    private void initConnection() throws Exception {
        connection=new Socket(host,port);
        output=connection.getOutputStream();
        input=connection.getInputStream();
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
    private boolean isUpdate(Protobuffs.Response.Type response){
        return response== Protobuffs.Response.Type.BUY_TICKET;
    }

    private void handleUpdate(Protobuffs.Response response){
            //System.out.println("Bought ticket update"+response.data());
            Ticket ticket=Converter.getTicketBought(response);
            client.ticketBought(ticket);

    }
    private class ReaderThread implements Runnable{
        @Override
        public void run() {
            while(!finished){
                try{
                    Protobuffs.Response response=Protobuffs.Response.parseDelimitedFrom(input);
                    System.out.println("Response received"+response);
                    if (isUpdate(response.getType())){
                        handleUpdate(response);
                    }
                    else{
                        try{
                            qresponses.put(response);
                        }
                        catch (InterruptedException ex){
                            System.out.println("Error "+ex);
                        }
                    }

                }
                catch (IOException ex){
                    //ex.printStackTrace();
                    System.out.println("Reading error "+ex);
                }
            }
        }
    }

    private void sendRequest(Protobuffs.Request request) throws Exception{
        try{
            request.writeDelimitedTo(output);
            output.flush();
        }
        catch (IOException ex){
            throw new Exception("Error sending object "+ex);
        }
    }

    private Protobuffs.Response readResponse() throws Exception{
        Protobuffs.Response response=null;
        try{
            response=qresponses.take();
        }
        catch (InterruptedException ex){
            ex.printStackTrace();
        }
        return response;
    }
}
