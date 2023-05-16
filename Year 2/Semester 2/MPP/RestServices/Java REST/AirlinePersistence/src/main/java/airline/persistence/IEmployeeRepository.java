package airline.persistence;


import airline.model.Employee;

public interface IEmployeeRepository extends IRepository<Employee>{
    Employee getEmployee(String username, String password);
}
