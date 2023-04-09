package airline.server.impl;

import airline.model.Employee;
import airline.model.Flight;
import airline.model.Ticket;
import airline.persistence.IEmployeeRepository;
import airline.persistence.IFlightRepository;
import airline.persistence.ITicketRepository;
import airline.services.IAirlineObserver;
import airline.services.IService;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class AirlineServicesImpl implements IService {
    private IEmployeeRepository employeeRepository;
    private ITicketRepository ticketRepository;
    private IFlightRepository flightRepository;

    private Map<Integer, IAirlineObserver> loggedEmployees;


    public AirlineServicesImpl(IEmployeeRepository employeeRepository, ITicketRepository ticketRepository, IFlightRepository flightRepository) {
        this.employeeRepository = employeeRepository;
        this.ticketRepository = ticketRepository;
        this.flightRepository = flightRepository;
        loggedEmployees =new ConcurrentHashMap<>();
    }

    public synchronized Employee login(Employee employee, IAirlineObserver client) throws Exception {
        Employee employeeToLogin=employeeRepository.getEmployee(employee.getUsername(),employee.getPassword());
        if (employeeToLogin!=null){
            if (loggedEmployees.get(employeeToLogin.getId())!=null)
                throw new Exception("Employee already logged in.");

            loggedEmployees.put(employeeToLogin.getId(),client);

        }
        else
            throw new Exception("Authentication failed.");
        return employeeToLogin;
    }

    public synchronized void logout(Employee employee, IAirlineObserver client) throws Exception {
        IAirlineObserver loggedEmployee= loggedEmployees.remove(employee.getId());
        if (loggedEmployee==null)
            throw new Exception("Employee "+String.valueOf(employee.getId())+" is not logged in.");
    }
    @Override
    public synchronized Iterable<Flight> getAllFlights() {
        return flightRepository.getAll();
    }

    public synchronized int getNumberOfTicketsForFlight(Integer flightId) throws Exception{
        List<Ticket> tickets = (List<Ticket>) ticketRepository.getAll();
        List<Ticket> filtered_tickets = tickets.stream()
                .filter(ticket -> ticket.getFlightId() == flightId)
                .collect(Collectors.toList());

        return filtered_tickets.size();
    }

    public synchronized Iterable<Flight> getFlights(String destination, String date) throws Exception{
        List<Flight> flights = (List<Flight>) flightRepository.getAll();
        List<Flight> filtered_flights = null;
        if (date.equals(""))
            filtered_flights = flights.stream()
                    .filter(flight -> {
                        try {
                            return flight.getDestination().equals(destination) && flight.getAvailableSeats() > 0;
                        } catch (Exception e) {
                            throw new RuntimeException(e);
                        }
                    })
                    .collect(Collectors.toList());
        else {
            filtered_flights = flights.stream()
                    .filter(flight -> {
                        try {
                            return flight.getDestination().equals(destination) && flight.getDate().equals(date) &&  flight.getAvailableSeats() > 0;
                        } catch (Exception e) {
                            throw new RuntimeException(e);
                        }
                    })
                    .collect(Collectors.toList());
        }
        return filtered_flights;
    }


    public synchronized Employee getEmployee(String username, String password) {
        Employee employee = employeeRepository.getEmployee(username, password);
        return employee;
    }

    public synchronized void buyTicket(int flightId, String tourist_name, String client_address) {
        Ticket ticket = new Ticket(tourist_name, client_address, flightId);
        ticketRepository.add(ticket);
        flightRepository.updateNumberOfSeats(flightId);
        for (IAirlineObserver loggedUser: loggedEmployees.values()) {
            loggedUser.ticketBought(ticket);
        }
    }
}
