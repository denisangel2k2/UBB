using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AirlineClient
{
    public enum EmployeeEvent
    {
        BUY_TICKET
    };

    public class EmployeeEventArgs : EventArgs
    {
        public EmployeeEventArgs(EmployeeEvent employeeEvent, object data)
        {
            this.EmployeeEventType = employeeEvent;
            this.Data = data;
        }

        public EmployeeEvent EmployeeEventType { get; }

        public object Data { get; }
    }
}
