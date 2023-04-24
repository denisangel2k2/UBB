using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using log4net;
using System.Net.Sockets;
using Services;
using Model;

namespace Networking
{
    public class ClientWorker : IObserver 
    {

        private static readonly ILog Logger = LogManager.GetLogger("ClientWorker");

        private readonly IService service;
        private readonly TcpClient connection;
        private readonly NetworkStream stream;
        private readonly IFormatter formatter;
        private volatile bool connected;
        public ClientWorker(IService service, TcpClient connection)
        {
            this.service = service;
            this.connection = connection;
            try
            {
                stream = connection.GetStream();
                formatter = new BinaryFormatter();
                connected = true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }


        public virtual void Run()
        {
            while (connected)
            {
                try
                {
                    var request = formatter.Deserialize(stream);
                    object response = HandleRequest((Request)request);
                    if (response != null)
                    {
                        SendResponse((Response)response);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }

                try
                {
                    Thread.Sleep(1000);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }
            try
            {
                stream.Close();
                connection.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine("Error " + e);
            }

            
        }
        private Response HandleRequest(Request request)
        {
            Response response = null;
            var handlerName = "Handle" + request.Type;
            Console.WriteLine("HandlerName " + handlerName);
            try
            {
                var method = this.GetType().GetMethod(handlerName, new[] { typeof(Request) });
                response = (Response)method.Invoke(this, new[] { request });
                Console.WriteLine("Method " + handlerName + " invoked");
            }
            catch (TargetInvocationException ex)
            {
                Console.WriteLine(ex.InnerException);
            }
            catch (AmbiguousMatchException ex)
            {
                Console.WriteLine(ex.Message);
            }
            catch (TargetParameterCountException ex)
            {
                Console.WriteLine(ex.Message);
            }
            catch (TargetException ex)
            {
                Console.WriteLine(ex.Message);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            return response;
        }

        public Response HandleLOGIN(Request request)
        {
            Employee employee = (Employee)request.Data;
            try
            {
                var foundEmployee = service.login(employee, this);
                Logger.Info("Logged in");
                return new Response.Builder().Type(ResponseType.OK).Data(foundEmployee).Build();

            }
            catch (Exception ex)
            {
                connected = false;
                Logger.Error("Error in worker, handleLOGIN");
                return new Response.Builder().Type(ResponseType.ERROR).Data(ex.Message).Build();
            }
        }

        public Response HandleLOGOUT(Request request)
        {
            Employee employee=(Employee)request.Data;
            try
            {
                service.logout(employee);
                connected = false;
                return new Response.Builder().Type(ResponseType.OK).Build();
            }
            catch (Exception ex)
            {
                return new Response.Builder().Type(ResponseType.ERROR).Data(ex.Message).Build();
            }
        }

        public Response HandleBUY_TICKET(Request request)
        {
            Ticket ticketToBuy=(Ticket)request.Data;
            try
            {
                service.buyTicket(ticketToBuy.FlightId, ticketToBuy.Client_name, ticketToBuy.Address);
                return new Response.Builder().Type(ResponseType.OK).Build();
            }
            catch(Exception ex)
            {
                return new Response.Builder().Type(ResponseType.ERROR).Data(ex.Message).Build();
            }
        }

        public Response HandleGET_FLIGHTS(Request request)
        {
            Flight likeFlights=(Flight)request.Data;
            try
            {
                List<Flight> flights = (List<Flight>)service.getFlights(likeFlights.Destination, likeFlights.Date);
                return new Response.Builder().Type(ResponseType.GET_FLIGHTS).Data(flights).Build();

            }
            catch (Exception ex)
            {
                return new Response.Builder().Type(ResponseType.ERROR).Data(ex.Message).Build();
            }
        }

        public Response HandleGET_ALL_FLIGHTS(Request request)
        {
            try
            {
                List<Flight> flights = (List<Flight>)service.getAllFlights();
                return new Response.Builder().Type(ResponseType.GET_ALL_FLIGHTS).Data(flights).Build();
            }
            catch (Exception ex)
            {
                return new Response.Builder().Type(ResponseType.ERROR).Data(ex.Message).Build();
            }
        }

        public Response HandleGET_NUMBER_OF_TICKETS(Request request)
        {
            int flightId=(int)request.Data;
            try
            {
                int numberOfTickets = service.getNumberOfTicketsForFlights(flightId);
                return new Response.Builder().Type(ResponseType.GET_NUMBER_OF_TICKETS_FOR_FLIGHT).Data(numberOfTickets).Build();
            }
            catch (Exception ex)
            {
                return new Response.Builder().Type(ResponseType.ERROR).Data(ex.Message).Build();
            }
        }


        private void SendResponse(Response response)
        {
            Console.WriteLine("sending response " + response);
            lock (stream)
            {
                formatter.Serialize(stream, response);
                stream.Flush();
            }
        }

        public void TicketBought(Ticket ticket)
        {
            var response=new Response.Builder().Type(ResponseType.BUY_TICKET).Data(ticket).Build();
            Logger.Info("Sold ticket {ticket}");
            try
            {
                SendResponse(response);

            }
            catch(Exception ex)
            {
                Console.WriteLine(@"Error in worker (sending response): {0}", ex);
            }

        }

        
    }
}
