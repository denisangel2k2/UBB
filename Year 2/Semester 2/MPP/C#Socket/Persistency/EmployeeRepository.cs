
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
    public class EmployeeRepository : IEmployeeRepository
    {
        private static readonly ILog log = LogManager.GetLogger("EmployeeRepository");
        private IDictionary<string, string> props;
        public EmployeeRepository(IDictionary<string, string> props)
        {
            log.Info("Creating EmployeeRepository");
            this.props = props;
        }

        public void add(Employee entity)
        {
            log.Info("Entering add function");
            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "insert into employees values(@id,@first_name,@last_name,@username,@password)";
                var paramId = command.CreateParameter();
                paramId.ParameterName = "@id";
                paramId.Value = null;

                var paramFirstName = command.CreateParameter();
                paramFirstName.ParameterName = "@first_name";
                paramFirstName.Value = entity.First_name;

                var paramLastName = command.CreateParameter();
                paramLastName.ParameterName = "@last_name";
                paramLastName.Value = entity.Last_name;

                var paramUsername = command.CreateParameter();
                paramUsername.ParameterName = "@username";
                paramUsername.Value = entity.Username;

                var paramPassword = command.CreateParameter();
                paramPassword.ParameterName = "@password";
                paramPassword.Value = entity.Password;

                command.Parameters.Add(paramId);
                command.Parameters.Add(paramFirstName);
                command.Parameters.Add(paramLastName);
                command.Parameters.Add(paramUsername);
                command.Parameters.Add(paramPassword);
                var result = command.ExecuteNonQuery();

                if (result == 0)
                    log.Error("No entities were added in Employee table");
                else
                    log.InfoFormat("{0} were added in Employee table", result);
            }
        }

        public Employee findById(int id)
        {
            log.InfoFormat("Entering findById with value {0}", id);
            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "select employee_id,first_name,last_name,username,password from emplyoees where id=@id";
                IDbDataParameter paramId = command.CreateParameter();
                paramId.ParameterName = "@id";
                paramId.Value = id;
                command.Parameters.Add(paramId);
                using (var reader = command.ExecuteReader())
                {
                    Employee employee = extractEntity(reader);
                    log.InfoFormat("Exiting findById with value {0}", employee);
                    return employee;
                }
            }
            log.InfoFormat("Exiting findById with value {0}", null);
            return null;

        }
        private Employee extractEntity(DbDataReader reader)
        {
            int id = reader.GetInt32(0);
            string first_name = reader.GetString(1);
            string last_name = reader.GetString(2);
            string username = reader.GetString(3);
            string password = reader.GetString(4);
            Employee employee = new Employee(first_name, last_name, username, password);
            employee.Id = id;
            return employee;
        }
        public List<Employee> GetAll()
        {
            var connection = (SQLiteConnection)DBUtils.GetConnection(props);
            List<Employee> employees = new List<Employee>();
            using (var command = connection.CreateCommand())
            {
                command.CommandText = "select employee_id,first_name,last_name,username,password from employees";
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        Employee employee = extractEntity(reader);
                        employees.Add(employee);
                    }
                }
            }
            return employees;

        }
    }
}
