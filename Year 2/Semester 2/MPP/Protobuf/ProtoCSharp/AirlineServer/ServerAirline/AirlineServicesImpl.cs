using Model;
using Persistency;
using Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    public class AirlineServicesImpl : IService
    {
        private readonly IEmployeeRepository employeeRepository;
        private readonly ITicketRepository ticketRepository;
        private readonly IFlightRepository flightRepository;

        private readonly IDictionary<int, IObserver> loggedEmployees;



        public AirlineServicesImpl(IEmployeeRepository employeeRepository, ITicketRepository ticketRepository, IFlightRepository flightRepository)
        {
            this.employeeRepository = employeeRepository;
            this.ticketRepository = ticketRepository;
            this.flightRepository = flightRepository;

            loggedEmployees=new Dictionary<int, IObserver>();
        }


        public void buyTicket(int flightId, string tourist_name, string client_address)
        {
            Ticket ticket = new Ticket(tourist_name, client_address, flightId);
            ticketRepository.add(ticket);
            flightRepository.updateNumberOfSeats(flightId);
            foreach (var loggedEmployee in loggedEmployees.Values)
            {
                Task.Run(() => loggedEmployee.TicketBought(ticket));
            }
            
            
            

        }

        public List<Flight> getAllFlights()
        {
            List<Flight> flights = flightRepository.GetAll().Where(f => f.NumberOfSeats - getNumberOfTicketsForFlights(f.Id) > 0).ToList();
            return flights;

        }

        public Employee getEmployee(string username, string password)
        {
            List<Employee> employees = employeeRepository.GetAll().ToList();
            Employee employee = employees.Where(e => e.Username == username && e.Password == password).FirstOrDefault();
            if (employee != default)
            {
                return employee;
            }
            else return null;

        }

        public List<Flight> getFlights(string destination, string date)
        {
            List<Flight> flights = flightRepository.GetAll().ToList();
            return flights.Where(f => f.Destination.StartsWith(destination) && f.Date == date && f.NumberOfSeats - getNumberOfTicketsForFlights(f.Id) > 0).ToList();

        }

        public int getNumberOfTicketsForFlights(int flightId)
        {
            List<Ticket> tickets = ticketRepository.GetAll().ToList();
            return tickets.Where(t => t.FlightId == flightId).Count();
        }

        public Employee login(Employee employee, IObserver client)
        {
            List<Employee> employees = employeeRepository.GetAll().ToList();
            Employee employee1 = employees.Where(e => e.Username == employee.Username && e.Password == employee.Password).FirstOrDefault();

            if (employee1 != null)
            {
                if (loggedEmployees.ContainsKey(employee1.Id))
                    throw new Exception("Already logged in");
                loggedEmployees[employee1.Id] = client;
            }
            else throw new Exception("Failed login");
            return employee1;
        }

        public void logout(Employee employee)
        {
            var Client = loggedEmployees[employee.Id];
            if (Client == null)
                throw new Exception("User " + employee.Id +" is not logged in!");
            loggedEmployees.Remove(employee.Id);
        }

        
    }
}
