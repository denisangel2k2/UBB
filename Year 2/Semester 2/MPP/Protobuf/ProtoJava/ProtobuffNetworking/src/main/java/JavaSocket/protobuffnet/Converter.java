package JavaSocket.protobuffnet;

import airline.model.Employee;
import airline.model.Flight;
import airline.model.Ticket;

import java.util.ArrayList;
import java.util.List;

public class Converter {
    public static Protobuffs.Request createLoginRequest(Employee employee){
        Protobuffs.Employee myEmployee = Protobuffs.Employee.newBuilder().
                setFirstName(employee.getFirst_name()).
                setLastName(employee.getLast_name()).
                setUsername(employee.getUsername()).
                setPassword(employee.getPassword()).build();
        return Protobuffs.Request.newBuilder().setType(Protobuffs.Request.Type.LOGIN)
                .setEmployee(myEmployee).build();
    }
    public static Protobuffs.Request createLogoutRequest(Employee employee) {
        Protobuffs.Employee myEmployee = Protobuffs.Employee.newBuilder().
                setId(employee.getId()).
                setFirstName(employee.getFirst_name()).
                setLastName(employee.getLast_name()).
                setUsername(employee.getUsername()).
                setPassword(employee.getPassword()).build();
        return Protobuffs.Request.newBuilder().setType(Protobuffs.Request.Type.LOGOUT)
                .setEmployee(myEmployee).build();
    }
    public static Protobuffs.Request createAddTicketRequest(Ticket ticket) {
        Protobuffs.Ticket myTicket = Protobuffs.Ticket.newBuilder().
                setClientName(ticket.getClient_name()).
                setAddress(ticket.getAddress()).
                setFlightId(ticket.getFlightId()).build();
        return Protobuffs.Request.newBuilder().setType(Protobuffs.Request.Type.BUY_TICKET)
                .setTicket(myTicket).build();
    }
    public static String getError(Protobuffs.Response response) {
        return response.getError();
    }
    public static Employee getEmployee(Protobuffs.Response response) {
        Employee employee=new Employee(response.getEmployee().getFirstName(), response.getEmployee().getLastName(), response.getEmployee().getUsername(), response.getEmployee().getPassword());
        employee.setID(response.getEmployee().getId());
        return employee;
    }
    public static Ticket getTicket(Protobuffs.Response response) {
        Ticket ticket=new Ticket(response.getTicket().getClientName(), response.getTicket().getAddress(), response.getTicket().getFlightId());
        ticket.setID(response.getTicket().getId());
        return ticket;

    }


    public static Protobuffs.Request createGetFlightsRequest(Flight flight){
        Protobuffs.Flight myFlight = Protobuffs.Flight.newBuilder().
                setDestination(flight.getDestination()).
                setDate(flight.getDate()).
                setHour(flight.getHour()).
                setNumberOfSeats(flight.getNumberOfSeats()).build();
        return Protobuffs.Request.newBuilder().setType(Protobuffs.Request.Type.GET_FLIGHTS)
                .setFlight(myFlight).build();
    }

    public static Iterable<Flight> getFlights(Protobuffs.Response response) {
        List<Flight> flights = new ArrayList<>();
        for (Protobuffs.Flight flight : response.getFlightsList()) {
            Flight flight1=new Flight(flight.getDestination(), flight.getDate(), flight.getHour(), flight.getNumberOfSeats());
            flight1.setAvailableSeats(flight.getAvailableSeats());
            flight1.setID(flight.getId());
            flights.add(flight1);
        }
        return flights;
    }


    public static Protobuffs.Request createGetNumberOfTicketsRequest(Integer flightId){
        return Protobuffs.Request.newBuilder().setType(Protobuffs.Request.Type.GET_NUMBER_OF_TICKETS)
                .setFlightId(flightId).build();
    }
    public static Integer getNumberOfTickets(Protobuffs.Response response) {
        return response.getNumberOfTickets();
    }
    public static Protobuffs.Request createGetAllFlightsRequest(){
        return Protobuffs.Request.newBuilder().setType(Protobuffs.Request.Type.GET_ALL_FLIGHTS)
                .build();
    }
    public static Iterable<Flight> getAllFlights(Protobuffs.Response response) {
        List<Flight> flights = new ArrayList<>();
        for (Protobuffs.Flight flight : response.getFlightsList()) {
            Flight flight1=new Flight(flight.getDestination(), flight.getDate(), flight.getHour(), flight.getNumberOfSeats());
            flight1.setAvailableSeats(flight.getAvailableSeats());
            flight1.setID(flight.getId());
            flights.add(flight1);
        }
        return flights;
    }
    public static Ticket getTicketBought(Protobuffs.Response response) {
        Ticket ticket=new Ticket(response.getTicket().getClientName(), response.getTicket().getAddress(), response.getTicket().getFlightId());
        ticket.setID(response.getTicket().getId());
        return ticket;

    }



}
