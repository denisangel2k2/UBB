using log4net;
using Model;
using Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Networking
{
    public class ServiceProxy : IService
    {
        private static readonly ILog Logger = LogManager.GetLogger("ServicesRpcProxy");
        private readonly string host;
        private readonly int port;
        private IObserver employeeObserver;
        private NetworkStream stream;
        private IFormatter formatter;
        private TcpClient connection;
        private readonly Queue<Response> responses;
        private volatile bool finished;
        private EventWaitHandle waitHandle;

        public ServiceProxy(string host, int port)
        {
            this.host = host;
            this.port = port;
            responses = new Queue<Response>();
        }

        private void CloseConnection()
        {
            finished = true;
            try
            {
                stream.Close();
                connection.Close();
                waitHandle.Close();
                employeeObserver = null;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        private void SendRequest(Request request)
        {
            try
            {
                formatter.Serialize(stream, request);
                stream.Flush();
            }
            catch (Exception e)
            {
                throw new Exception("Error sending object " + e);
            }
        }

        private void InitializeConnection()
        {
            try
            {
                connection = new TcpClient(host, port);
                stream = connection.GetStream();
                formatter = new BinaryFormatter();
                finished = false;
                waitHandle = new AutoResetEvent(false);
                StartReader();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        private void HandleUpdate(Response response)
        {
            if (response.Type != ResponseType.BUY_TICKET) return;
            var ticket = (Ticket)response.Data;
            Logger.Info("Ticket sold " + ticket);
            try
            {
                employeeObserver.TicketBought(ticket);
            }
            catch (Exception e)
            {
                Logger.Error("Error handle update: " + e);
            }
        }

        private static bool IsUpdate(Response response)
        {
            return response.Type == ResponseType.BUY_TICKET;
        }

        protected virtual void Run()
        {
            while (!finished)
            {
                try
                {
                    var response = formatter.Deserialize(stream);
                    Console.WriteLine("response received " + response);
                    if (IsUpdate((Response)response))
                    {
                        HandleUpdate((Response)response);
                    }
                    else
                    {
                        lock (responses)
                        {
                            responses.Enqueue((Response)response);
                        }
                        waitHandle.Set();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Reading error " + e);
                }
            }
        }
        private void StartReader()
        {
            var tw = new Thread(Run);
            tw.Start();
        }


        private Response ReadResponse()
        {
            Response response = null;
            try
            {
                waitHandle.WaitOne();
                lock (responses)
                {
                    response = responses.Dequeue();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
            return response;
        }


        public void buyTicket(int flightId, string tourist_name, string client_address)
        {
            Ticket ticket=new Ticket(tourist_name, client_address,flightId);
            Request request=new Request.Builder().Type(RequestType.BUY_TICKET).Data(ticket).Build();
            SendRequest(request);
            Response response = ReadResponse();
            if (response.Type == ResponseType.ERROR)
            {
                string err=response.Data.ToString();
                throw new Exception(err);
            }
        }

        public List<Flight> getAllFlights()
        {
            Request request=new Request.Builder().Type(RequestType.GET_ALL_FLIGHTS).Data(null).Build();
            SendRequest(request);
            Response response = ReadResponse();
            if (response.Type == ResponseType.GET_ALL_FLIGHTS)
            {
                var flights = (List<Flight>)response.Data;
                return flights;
            }
            else throw new Exception("Error getting flights");
        }

        public Employee getEmployee(string username, string password)
        {
            throw new NotImplementedException();
        }

        public List<Flight> getFlights(string destination, string date)
        {
            Flight flight = new Flight(destination, date, "0", 0,0);
            Request request=new Request.Builder().Type(RequestType.GET_FLIGHTS).Data(flight).Build();
            SendRequest(request);
            Response response=ReadResponse();
            if (response.Type == ResponseType.GET_FLIGHTS)
            {
                List<Flight> flights = (List<Flight>)response.Data;
                return flights;
            }
            else throw new Exception("Error getting flights");
        }

        public int getNumberOfTicketsForFlights(int flightId)
        {
            Request request=new Request.Builder().Type(RequestType.GET_NUMBER_OF_TICKETS).Data(flightId).Build();
            SendRequest(request);
            Response response=ReadResponse();
            if (response.Type == ResponseType.GET_NUMBER_OF_TICKETS_FOR_FLIGHT)
            {
                int numberOfTickets = (int)response.Data;
                return numberOfTickets;
            }
            else throw new Exception("Error getting number of tickets");
        }

        public Employee login(Employee employee, IObserver client)
        {
            InitializeConnection();
            Request request=new Request.Builder().Type(RequestType.LOGIN).Data(employee).Build();
            SendRequest(request);
            Response response = ReadResponse();
            if (response.Type == ResponseType.OK)
            {
                this.employeeObserver = client;
                return (Employee)response.Data;
            }
            if (response.Type == ResponseType.ERROR)
            {
                string err=response.Data.ToString();
                CloseConnection();
                throw new Exception(err);
            }
            return null;
        }

        public void logout(Employee employee)
        {
            Request request=new Request.Builder().Type(RequestType.LOGOUT).Data(employee).Build();
            SendRequest(request);
            Response response = ReadResponse();
            CloseConnection();
            if (response.Type == ResponseType.ERROR)
            {
                string err=response.Data.ToString();
                throw new Exception(err);
            }
        }

       
    }
}
