package airline.services;


import airline.model.Employee;
import airline.model.Flight;

public interface IService {

    Employee login(Employee employee, IAirlineObserver client) throws Exception;
    void logout(Employee employee, IAirlineObserver client) throws Exception;
    Iterable<Flight> getFlights(String destination, String date) throws Exception;
    Employee getEmployee(String username, String password);
    void buyTicket(int flightId,String tourist_name, String client_address) throws Exception;
    int getNumberOfTicketsForFlight(Integer flightId) throws Exception;
    Iterable<Flight> getAllFlights() throws Exception;
}
