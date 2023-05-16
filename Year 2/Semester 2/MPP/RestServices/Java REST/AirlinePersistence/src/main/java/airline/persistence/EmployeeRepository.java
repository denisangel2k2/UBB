package airline.persistence;



import airline.model.Employee;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class EmployeeRepository implements IEmployeeRepository {
    private static final Logger logger= LogManager.getLogger();
    private JdbcUtils dbUtils;

    public EmployeeRepository(Properties properties) {
        dbUtils=new JdbcUtils(properties);
    }

    public Iterable<Employee> getAll() {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        List<Employee> employeeList=new ArrayList<>();
        try(PreparedStatement ps=connection.prepareStatement("select * from employees")) {
            try (ResultSet resultSet = ps.executeQuery()) {
                while (resultSet.next()) {

                    Employee employee=extractEntity(resultSet);
                    employeeList.add(employee);
                }
            }
        }
        catch(SQLException ex) {
            logger.error(ex);
        }
        logger.traceExit();
        return employeeList;
    }

    public Employee getEmployee(String username, String password){
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        try(PreparedStatement ps=connection.prepareStatement("select * from employees where username=? and password=?")){
            ps.setString(1,username);
            ps.setString(2,password);
            try(ResultSet resultSet=ps.executeQuery()){
                resultSet.next();
                return extractEntity(resultSet);
            }
        }
        catch (SQLException ex){
            logger.error(ex);
        }
        return null;
    }
    private Employee extractEntity(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("employee_id");
        String first_name = resultSet.getString("first_name");
        String last_name = resultSet.getString("last_name");
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");
        Employee employee = new Employee(first_name, last_name, username, password);
        employee.setId(id);
        return employee;
    }


    public Employee findById(int id) {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        try(PreparedStatement ps=connection.prepareStatement("select * from employees where id=?")){
            ps.setInt(1,id);
            try(ResultSet resultSet=ps.executeQuery()){
                resultSet.next();
                return extractEntity(resultSet);
            }
        }
        catch (SQLException ex){
            logger.error(ex);
        }

        logger.traceExit();
        return null;
    }


    public void add(Employee entity) {
         logger.traceEntry();
         Connection connection= dbUtils.getConnection();
         try(PreparedStatement ps=connection.prepareStatement("insert into employees(first_name,last_name,username,password) values (?,?,?,?)")){
             ps.setString(1,entity.getFirst_name());
             ps.setString(2,entity.getLast_name());
             ps.setString(3,entity.getUsername());
             ps.setString(4,entity.getPassword());
             int result=ps.executeUpdate();
             logger.trace("Added {} instances",result);
         }
         catch (SQLException ex){
          logger.error(ex);
         }
         logger.traceExit();
    }
}
