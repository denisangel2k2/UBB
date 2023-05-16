package airline.persistence;

import airline.model.Employee;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;

import java.util.List;

public class EmployeeORMRepository implements IEmployeeRepository{
    private  static SessionFactory sessionFactory;
    public EmployeeORMRepository(){
        initialize();
    }
    public void initialize() {
        // A SessionFactory is set up once for an application!
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                .configure() // configures settings from hibernate.cfg.xml
                .build();
        try {
            sessionFactory = new MetadataSources(registry).buildMetadata().buildSessionFactory();
        } catch (Exception e) {
            System.out.println("Exceptie " + e);
            StandardServiceRegistryBuilder.destroy(registry);
        }
    }

    public Employee getEmployee(String username, String password) {
        try(Session session=sessionFactory.openSession()){
            Transaction tx=null;
            System.out.println("Session: "+session);
            try{
                tx=session.beginTransaction();
                Employee employee=session.createQuery("from Employee where username=:username and password=:password",Employee.class)
                        .setParameter("username",username)
                        .setParameter("password",password)
                        .setMaxResults(1)
                        .uniqueResult();
                tx.commit();
                return employee;
            }
            catch (RuntimeException ex){
                if(tx!=null)
                    tx.rollback();
            }
        }
        return null;
    }


    public Iterable<Employee> getAll() {
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try{
                transaction=session.beginTransaction();
                List<Employee> employees=session.createQuery("from Employee",Employee.class)
                        .list();
                transaction.commit();
                return employees;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
            }

        }
        return null;
    }


    public Employee findById(int id) {
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try {
                transaction=session.beginTransaction();
                Employee employee=session.createQuery("from Employee where id=:id",Employee.class)
                        .setParameter("id",id)
                        .setMaxResults(1)
                        .uniqueResult();
                transaction.commit();
                return employee;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
            }

        }
        return null;
    }


    public void add(Employee entity) {
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try{
                transaction=session.beginTransaction();
                session.save(entity);
                transaction.commit();
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
            }
        }
    }
}
