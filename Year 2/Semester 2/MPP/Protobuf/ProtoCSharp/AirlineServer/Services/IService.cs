using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Services
{
    public interface IService
    {
        Employee login(Employee employee, IObserver client);
        void logout(Employee employee);
        List<Flight> getFlights(string destination, string date);
        Employee getEmployee(string username, string password);
        void buyTicket(int flightId, string tourist_name, string client_address);
        int getNumberOfTicketsForFlights(int flightId);
        List<Flight> getAllFlights();
    }
}
