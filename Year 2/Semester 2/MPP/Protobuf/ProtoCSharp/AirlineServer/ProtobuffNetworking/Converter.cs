using System.Collections.Generic;
using JavaSocket.Protocol;
using Employee = Model.Employee;
using Flight = Model.Flight;
using Ticket = Model.Ticket;

namespace ProtobuffNetworking
{
    public class Converter
    {
        public static Response CreateLoginResponse(Employee employee)
        {
            var emp=new JavaSocket.Protocol.Employee()
            {
                Id=employee.Id,
                FirstName = employee.First_name,
                LastName = employee.Last_name,
                Username = employee.Username,
                Password = employee.Password
            };
            return new Response { Type = Response.Types.Type.Ok, Employee = emp };
        }

        public static Employee GetEmployee(Request request)
        {
            Employee employee=new Employee(
                request.Employee.FirstName,
                request.Employee.LastName,
                request.Employee.Username,
                request.Employee.Password
                );
            employee.Id= request.Employee.Id;
            return employee;
        }
        public static Response CreateErrorResponse(string message)
        {
            return new Response { Type = Response.Types.Type.Error, Error = message};
        }
        public static Response CreateOkResponse()
        {
            return new Response { Type = Response.Types.Type.Ok };
        }

        public static Ticket GetTicket(Request request)
        {
            Ticket ticket = new Ticket(
                
                request.Ticket.ClientName,
                request.Ticket.Address,
                request.Ticket.FlightId
            );
            ticket.Id = request.Ticket.Id;
            return ticket;

        }

        public static Response CreateGetFlightsResponse(IEnumerable<Flight> flights)
        {
            var flightslist = new List<JavaSocket.Protocol.Flight>();
            foreach (var flight in flights)
            {
                flightslist.Add(new JavaSocket.Protocol.Flight
                {
                    Id = flight.Id,
                    Destination = flight.Destination,
                    AvailableSeats = flight.AvailableSeats,
                    Date = flight.Date,
                    Hour = flight.Hour,
                    NumberOfSeats = flight.NumberOfSeats
                });
            }

            return new Response{Type = Response.Types.Type.GetFlights, Flights = {flightslist}};
        }
        public static Response CreateGetAllFlightsResponse(IEnumerable<Flight> flights)
        {
            var flightslist = new List<JavaSocket.Protocol.Flight>();
            foreach (var flight in flights)
            {
                flightslist.Add(new JavaSocket.Protocol.Flight
                {
                    Id = flight.Id,
                    Destination = flight.Destination,
                    AvailableSeats = flight.AvailableSeats,
                    Date = flight.Date,
                    Hour = flight.Hour,
                    NumberOfSeats = flight.NumberOfSeats
                });
            }

            return new Response{Type = Response.Types.Type.GetAllFlights, Flights = {flightslist}};
        }
        public static Flight GetFlight(Request request)
        {
            Flight flight = new Flight(
                request.Flight.Destination,
                request.Flight.Date,
                request.Flight.Hour,
                request.Flight.NumberOfSeats,
                request.Flight.AvailableSeats
            );
            flight.Id = request.Flight.Id;
            return flight;
        }

        public static Response CreateTicketBoughtResponse(Ticket ticket)
        {
            JavaSocket.Protocol.Ticket tick=new JavaSocket.Protocol.Ticket()
            {
                Id = ticket.Id,
                ClientName = ticket.Client_name,
                Address = ticket.Address,
                FlightId = ticket.FlightId
            };
            return new Response { Type = Response.Types.Type.BuyTicket, Ticket = tick };
        }
        
    }
}