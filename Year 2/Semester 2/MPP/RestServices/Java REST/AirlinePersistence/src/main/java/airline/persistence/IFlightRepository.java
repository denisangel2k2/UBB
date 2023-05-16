package airline.persistence;


import airline.model.Flight;

public interface IFlightRepository extends IRepository<Flight> {
    void updateNumberOfSeats(int flightId);
    void delete(int flightId);
}
