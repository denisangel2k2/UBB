package airline.services;

import airline.model.Employee;
import airline.model.Ticket;

public interface IAirlineObserver {
    void ticketBought(Ticket ticket);
}
