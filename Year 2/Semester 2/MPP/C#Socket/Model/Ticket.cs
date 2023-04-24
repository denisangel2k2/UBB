using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    [Serializable]
    public class Ticket : Entity<int>
    {
        private string client_name;
        private string address;
        private int flightId;

        public Ticket(string client_name, string address, int flight)
        {
            this.client_name = client_name;
            this.address = address;
            this.flightId = flight;
        }
        public string Client_name { get { return client_name; } }
        public string Address { get { return address; } }
        public int FlightId { get { return flightId; } }
        
        public override string ToString()
        {
            return "Ticket: " + client_name + " " + address + " " + flightId;
        }
    }
}
