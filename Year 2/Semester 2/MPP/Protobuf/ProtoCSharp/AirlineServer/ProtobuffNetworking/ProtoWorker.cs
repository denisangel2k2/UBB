using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;

using System.Threading;

using System.Net.Sockets;
using Google.Protobuf;
using JavaSocket.Protocol;
using Services;
using Employee = Model.Employee;
using Flight = Model.Flight;
using Ticket = Model.Ticket;

namespace ProtobuffNetworking
{
    public class ProtoWorker : IObserver
    {
        private readonly IService service;
        private readonly TcpClient connection;
        private readonly NetworkStream stream;
        private readonly IFormatter formatter;
        private volatile bool connected;
        public ProtoWorker(IService service, TcpClient connection)
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
                    var request = Request.Parser.ParseDelimitedFrom(stream);
                    Response response = handleRequest(request);
                    if (response != null)
                    {
                        SendResponse(response);
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
        private Response handleRequest(Request request)
		{
			Response response = null;
			Request.Types.Type reqType = request.Type;
			switch (reqType)
			{
				case Request.Types.Type.Login:
				{
                    Console.WriteLine("Login request");
                    Employee employee = Converter.GetEmployee(request);
                    try
                    {
                        lock (service)
                        {
                            return Converter.CreateLoginResponse(service.login(employee, this));
                        }
                    }
                    catch(Exception ex)
                    {
                        connected = false;
                        return Converter.CreateErrorResponse(ex.Message);
                    }
                }
				case Request.Types.Type.Logout:
				{
					Console.WriteLine("Logout request");
                    Employee employee = Converter.GetEmployee(request);
                    try
                    {
                        lock (service)
                        {
                            service.logout(employee);
                        }
                        connected = false;
                        return Converter.CreateOkResponse();
                    }
                    catch (Exception ex)
                    {
                        return Converter.CreateErrorResponse(ex.Message);
                    }
                    
				}
                case Request.Types.Type.BuyTicket:
                {
                    Console.WriteLine("Buy ticket request");
                    Ticket ticketToBuy = Converter.GetTicket(request);
try
                    {
                        lock (service)
                        {
                            service.buyTicket(ticketToBuy.FlightId, ticketToBuy.Client_name, ticketToBuy.Address);
                        }
                        return Converter.CreateOkResponse();
                    }
                    catch (Exception ex)
                    {
                        return Converter.CreateErrorResponse(ex.Message);
                    }
                    
                }
                case Request.Types.Type.GetFlights:
                {
                    Console.WriteLine("Get flights request");
                    Flight flight=Converter.GetFlight(request);
                    try
                    {
                        lock (service)
                        {
                            var flights=service.getFlights(flight.Destination, flight.Date);
                            return Converter.CreateGetFlightsResponse(flights);
                        }
                    }
                    catch (Exception ex)
                    {
                        return Converter.CreateErrorResponse(ex.Message);
                    }
                }
                case Request.Types.Type.GetAllFlights:
                {
                    Console.WriteLine("Gett all flights request");
                    try
                    {
                        lock (service)
                        {
                            var flights = service.getAllFlights();
                            return Converter.CreateGetAllFlightsResponse(flights);
                        }
                    }
                    catch (Exception ex)
                    {
                        return Converter.CreateErrorResponse(ex.Message);
                    }
                }
            }

			return response;
		}
        private void SendResponse(Response response)
        {
            Console.WriteLine("sending response " + response);
            lock (stream)
            {
                response.WriteDelimitedTo(stream);
                stream.Flush();
            }
        }

        public void TicketBought(Ticket ticket)
        {
            var response= Converter.CreateTicketBoughtResponse(ticket);

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