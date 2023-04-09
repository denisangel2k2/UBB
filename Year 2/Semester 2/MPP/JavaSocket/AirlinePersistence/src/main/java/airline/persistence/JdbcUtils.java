package airline.persistence;



import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class JdbcUtils {
    private static final Logger logger= LogManager.getLogger();
    private Properties properties;
    public JdbcUtils(Properties properties){
        this.properties=properties;
    }
    private Connection connection_instance=null;
    private Connection newConnection(){
        logger.traceEntry();
        String url=properties.getProperty("jdbc.url");
        String user=properties.getProperty("jdbc.user");
        String pass=properties.getProperty("jdbc.p.ass");
        logger.info("Trying to connect to database... {}",url);
        logger.info("user: {}",user);
        logger.info("pass: {}",pass);
        Connection con=null;
        try{
            if (user!=null && pass!=null)
                con=DriverManager.getConnection(url,user,pass);
            else con=DriverManager.getConnection(url);
        }
        catch (SQLException exception){
            logger.error(exception);
        }
        return con;
    }
    public Connection getConnection(){
        logger.traceEntry();
        try{
            if (connection_instance==null || connection_instance.isClosed())
                connection_instance=newConnection();
        }
        catch (SQLException exception){
            logger.error(exception);
        }
        logger.traceExit(connection_instance);
        return connection_instance;
    }

}
