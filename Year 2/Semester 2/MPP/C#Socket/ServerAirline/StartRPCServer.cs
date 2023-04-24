using Server;
using Persistency;
using Services;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Networking.utils;

namespace Server
{
    internal static class StartRPCServer
    {
        [STAThread]
        private static string GetConnectionStringByName(string name)
        {
            string returnValue = null;
            var settings = ConfigurationManager.ConnectionStrings[name];
            if (settings != null)
                returnValue = settings.ConnectionString;
            return returnValue;
        }

        public static void Main(string[] args)
        {

            IDictionary<string, string> props = new SortedList<string, string>();
            props.Add("ConnectionString", GetConnectionStringByName("flightsDB"));
            IFlightRepository flightRepository=new FlightRepository(props);
            IEmployeeRepository employeeRepository = new EmployeeRepository(props);
            ITicketRepository ticketRepository = new TicketRepository(props);
            IService service = new AirlineServicesImpl(employeeRepository, ticketRepository, flightRepository);
            var server = new RpcConcurrentServer("127.0.0.1", 55557, service);
            try
            {
                server.Start();
                Console.WriteLine(@"Server started ...");
                Console.ReadLine();
            }
            catch (ServerException e)
            {
                Console.Error.WriteLine("Error starting the server" + e.Message);
            }
            finally
            {
                try
                {
                    server.Stop();
                }
                catch (ServerException e)
                {
                    Console.Error.WriteLine("Error stopping server " + e.Message);
                }
            }

        }
    }
}
