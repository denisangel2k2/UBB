
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
    public class FlightRepository : IFlightRepository
    {
        private static readonly ILog log = LogManager.GetLogger("EmployeeRepository");
        private IDictionary<string, string> props;

        public FlightRepository(IDictionary<string, string> props)
        {
            this.props = props;
        }

        public void add(Flight entity)
        {
            log.Info("Entering add function");
            var connection = DBUtils.GetConnection(props);
            using (var command = new SQLiteCommand("insert into flights values (@id, @date, @hour, @no_seats, @destination, @available_seats)", connection as SQLiteConnection))
            {
                command.Parameters.AddWithValue("@id", null);
                command.Parameters.AddWithValue("@date", entity.Date);
                command.Parameters.AddWithValue("@available_seats", entity.AvailableSeats);
                var parameter = command.CreateParameter();
                parameter.ParameterName = "@hour";
                string chestie = entity.Hour;
                parameter.Value = entity.Hour;
                command.Parameters.Add(parameter);
                //command.Parameters.AddWithValue("@hour", entity.Hour);
                command.Parameters.AddWithValue("@no_seats", entity.NumberOfSeats);
                command.Parameters.AddWithValue("@destination", entity.Destination);
                command.ExecuteNonQuery();
            }
        }

        public void updateNumberOfSeats(int flightId)
        {
            var connection= DBUtils.GetConnection(props);
            using(var command=new SQLiteCommand("update flights set available_seats=available_seats-1 where flight_id=@flight_id",connection as SQLiteConnection))
            {
                command.Parameters.AddWithValue("@flight_id", flightId);
                command.ExecuteNonQuery();
            }
            
        }

        private Flight extractEntity(DbDataReader reader)
        {
            int id = reader.GetInt32(0);
            string destination = reader.GetString(4);
            string data = reader.GetString(1);
            string hour = reader.GetString(2);
            int no_seats = reader.GetInt32(3);
            int available_seats=reader.GetInt32(5);
            Flight flight = new Flight(destination, data, hour, no_seats,available_seats);
            flight.Id = id;
            return flight;

        }
        public Flight findById(int id)
        {
            log.InfoFormat("Entering findById with value {0}", id);
            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "select flight_id,data,hour,no_seats,destination,available_seats from flights where id=@id";
                IDbDataParameter paramId = command.CreateParameter();
                paramId.ParameterName = "@id";
                paramId.Value = id;
                command.Parameters.Add(paramId);
                using (var reader = command.ExecuteReader())
                {
                    Flight flight = extractEntity(reader);
                    log.InfoFormat("Exiting findById with value {0}", flight);
                    return flight;
                }
            }
            log.InfoFormat("Exiting findById with value {0}", null);
            return null;
        }

        public List<Flight> GetAll()
        {
            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            List<Flight> flights = new List<Flight>();
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "select flight_id,data,hour,no_seats,destination,available_seats from flights";
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        Flight flight = extractEntity(reader);
                        flights.Add(flight);
                    }
                }
            }
            return flights;
        }
        
    }
}
