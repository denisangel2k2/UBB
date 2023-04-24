using log4net;
using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Data.SQLite;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Model;
using Persistency.utils;

namespace Persistency
{
    public class TicketRepository : ITicketRepository
    {
        private static readonly ILog log = LogManager.GetLogger("TicketRepository");
        private IDictionary<string, string> props;

        public TicketRepository(IDictionary<string, string> props)
        {
            log.Info("Creating TicketRepository");
            this.props = props;
        }
        private Ticket extractEntity(DbDataReader reader)
        {
            int id = reader.GetInt32(1);
            string client_name = reader.GetString(0);
            string address = reader.GetString(2);
            int flight_id = reader.GetInt32(3);
            Ticket ticket = new Ticket(client_name, address, flight_id);
            ticket.Id = id;
            return ticket;
        }
        public void add(Ticket entity)
        {
            log.Info("Entering add function");
            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "insert into tickets(client_name,address,flight_id) values (@client_name,@address,@flight_id)";


                var paramClientName = command.CreateParameter();
                paramClientName.ParameterName = "@client_name";
                paramClientName.Value = entity.Client_name;

                var paramAddress = command.CreateParameter();
                paramAddress.ParameterName = "@address";
                paramAddress.Value = entity.Address;

                var paramFlight_id = command.CreateParameter();
                paramFlight_id.ParameterName = "@flight_id";
                paramFlight_id.Value = entity.FlightId.ToString();

                command.Parameters.Add(paramClientName);
                command.Parameters.Add(paramAddress);
                command.Parameters.Add(paramFlight_id);

                var result = command.ExecuteNonQuery();
                if (result == 0)
                    log.Error("No entities were added in Ticket table");
                else
                    log.InfoFormat("{0} were added in Ticket table", result);
            }
        }

        public Ticket findById(int id)
        {
            log.InfoFormat("Entering findById with value {0}", id);
            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "select * from emplyoees where id=@id";
                IDbDataParameter paramId = command.CreateParameter();
                paramId.ParameterName = "@id";
                paramId.Value = id;
                command.Parameters.Add(paramId);
                using (var reader = command.ExecuteReader())
                {
                    Ticket ticket = extractEntity(reader);
                    log.InfoFormat("Exiting findById with value {0}", ticket);
                    return ticket;
                }
            }
            log.InfoFormat("Exiting findById with value {0}", null);
            return null;
        }

        public List<Ticket> GetAll()
        {

            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            List<Ticket> tickets = new List<Ticket>();
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "select * from tickets";
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        Ticket ticket = extractEntity(reader);
                        tickets.Add(ticket);
                    }
                }
            }
            return tickets;
        }
    }
}
