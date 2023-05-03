
using Model;
using Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AirlineClient
{
    public class AirlineClientController : IObserver
    {

        public IService Service { get; }
        public Employee LoggedEmployee { get; private set; }

        public event EventHandler<EmployeeEventArgs> UpdateEvent;
        public AirlineClientController(IService service)
        {
            this.Service = service;
            LoggedEmployee = null;
        }

        public void login(string username, string password)
        {
            var employeeToLogin= new Employee("","",username,password);
            var employee = Service.login(employeeToLogin, this);
            LoggedEmployee = employee;
        }

        public void logout()
        {
            Service.logout(LoggedEmployee);
            LoggedEmployee= null;
        }

        protected virtual void OnUserEvent(EmployeeEventArgs e)
        {
            if (UpdateEvent == null) return;
            Console.WriteLine(@"Update Event called");
            UpdateEvent(this, e);
        }

        



        public void TicketBought(Ticket ticket)
        {
            var userArgs=new EmployeeEventArgs(EmployeeEvent.BUY_TICKET,ticket);
            OnUserEvent(userArgs);
        }


    }
}
