package airline.model;

import javax.persistence.*;
import java.io.Serializable;
@javax.persistence.Entity
@Table(name = "employees")
@AttributeOverride(name = "id", column = @Column(name = "employee_id"))
public class Employee extends Entity<Integer> implements Serializable {

    @Column(name = "first_name")
    private String first_name;
    @Column(name = "last_name")
    private String last_name;
    @Column(name = "username")
    private String username;
    @Column(name = "password")
    private String password;

    public Employee(String first_name, String last_name, String username, String password) {
        this.first_name = first_name;
        this.last_name = last_name;
        this.username = username;
        this.password = password;
    }
    public Employee(){
        this.first_name = null;
        this.last_name = null;
        this.username = null;
        this.password = null;
    }

    public String getFirst_name() {
        return first_name;
    }

    public String getLast_name() {
        return last_name;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }


    @Override
    public String toString() {
        return "Employee{" +
                "first_name='" + first_name + '\'' +
                ", last_name='" + last_name + '\'' +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }

    @Override
    public int hashCode() {
        return username != null ? username.hashCode() : 0;
    }
}
