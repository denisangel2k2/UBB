using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    [Serializable]
    public class Employee : Entity<int>
    {
        private string first_name;
        private string last_name;
        private string username;
        private string password;

        public Employee(string first_name, string last_name, string username, string password)
        {
            this.first_name = first_name;
            this.last_name = last_name;
            this.username = username;
            this.password = password;
        }
        public string First_name { get { return first_name; } }
        public string Last_name { get { return last_name; } }
        public string Username { get { return username; } }
        public string Password { get { return password; } }
        public override string ToString()
        {
            return first_name + " " + last_name;
        }
    }
}
