using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    [Serializable]  
    public class Flight : Entity<int>
    {
        private string destination;
        private string date;
        private string hour;
        private int numberOfSeats;
        private int availableSeats;

        public Flight(string destination, string date, string hour, int numberOfSeats, int availableSeats)
        {
            this.destination = destination;
            this.date = date;
            this.hour = hour;
            this.numberOfSeats = numberOfSeats;
            this.availableSeats = availableSeats;
        }
        
        
        public string Destination { get { return destination; } }
        public string Date { get { return date; } }
        public string Hour { get { return hour; } }
        public int NumberOfSeats { get { return numberOfSeats; } }

        public int AvailableSeats
        {
            get { return availableSeats; }
            set { availableSeats = value; }
        }
        
        public override string ToString()
        {
            return "Flight{" +
                    "destination='" + destination + '\'' +
                    ", date='" + date + '\'' +
                    ", hour='" + hour + '\'' +
                    ", numberOfSeats=" + numberOfSeats +
                    '}';
        }

    }
}
