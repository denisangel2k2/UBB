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
import java.util.Objects;

public class AirlineClientRpcWorker implements Runnable, IAirlineObserver {
    private IService service;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;

    private volatile boolean connected;

    public AirlineClientRpcWorker(IService service, Socket connection){
        this.service=service;
        this.connection=connection;
        try{
            output=new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection.getInputStream());
            connected=true;
        }
        catch (IOException ex){
            ex.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (connected){
            try{
                Object request=input.readObject();
                Response response=handleRequest((Request)request);
                if (response!=null)
                    sendResponse(response);
            }
            catch (IOException e){
                e.printStackTrace();
            }
            catch (ClassNotFoundException e){
                e.printStackTrace();
            }

            try{
                Thread.sleep(1000);
            }
            catch (InterruptedException ex){
                ex.printStackTrace();
            }
        }
    }

    @Override
    public void ticketBought(Ticket ticket) {
        try{
            sendResponse(new Response.Builder().type(ResponseType.BUY_TICKET).data(ticket).build());
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }



    private Response handleRequest(Request request){
        Response response=null;
        if (request.type()== RequestType.LOGIN){
            Employee employee=(Employee)request.data();
            try{
                Employee found_employee=service.login(employee,this);
                return new Response.Builder().type(ResponseType.OK).data(found_employee).build();
            }
            catch (Exception e){
                connected=false;
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }

        if (request.type()== RequestType.LOGOUT){
            Employee employee=(Employee)request.data();
            try{
                service.logout(employee,this);
                connected=false;
                return new Response.Builder().type(ResponseType.OK).build();
            }
            catch (Exception e){
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }

        if (request.type()== RequestType.BUY_TICKET){
           Ticket ticketToBuy=(Ticket)request.data();
           try{
               service.buyTicket(ticketToBuy.getFlightId(),ticketToBuy.getClient_name(),ticketToBuy.getAddress());
                return new Response.Builder().type(ResponseType.OK).build();
           }
           catch (Exception e){
               return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
           }

        }
        if (request.type()== RequestType.GET_FLIGHTS){
            Flight likeFlights=(Flight)request.data();
            try{
                Iterable<Flight> flights=service.getFlights(likeFlights.getDestination(),likeFlights.getDate());
                return new Response.Builder().type(ResponseType.GET_FLIGHTS).data(flights).build();
            }
            catch (Exception e) {
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }
        if (request.type()== RequestType.GET_ALL_FLIGHTS){
            try{
               Iterable<Flight> flights=service.getAllFlights();
               return new Response.Builder().type(ResponseType.GET_ALL_FLIGHTS).data(flights).build();
            }
            catch (Exception e){
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }
        /*
        if (request.type()== RequestType.GET_NUMBER_OF_TICKETS){
            Integer flightId=(Integer)request.data();
            try{
                Integer numberOfTickets=service.getNumberOfTicketsForFlight(flightId);
                return new Response.Builder().type(ResponseType.GET_NUMBER_OF_TICKETS_FOR_FLIGHT).data(numberOfTickets).build();
            }
            catch (Exception e){
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }

         */


        return response;
    }

    private void sendResponse(Response response) throws IOException{
        System.out.println("sending response "+response);
        output.writeObject(response);
        output.flush();
    }

}
