package airline.persistence;


import airline.model.Ticket;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class TicketRepository implements ITicketRepository {
    private static final Logger logger= LogManager.getLogger();
    private JdbcUtils dbUtils;

    public TicketRepository(Properties properties) {
        dbUtils=new JdbcUtils(properties);
    }
    @Override
    public Iterable<Ticket> getAll() {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        List<Ticket> ticketList=new ArrayList<>();
        try(PreparedStatement ps=connection.prepareStatement("select * from tickets")) {
            try (ResultSet resultSet = ps.executeQuery()) {
                while (resultSet.next()) {
                    Ticket flight=extractEntity(resultSet);
                    ticketList.add(flight);

                }
            }
        }
        catch(SQLException ex) {
            logger.error(ex);
        }
        logger.traceExit();
        return ticketList;
    }

    private Ticket extractEntity(ResultSet resultSet) throws SQLException {
        int id=resultSet.getInt("ticket_id");
        String client_name=resultSet.getString("client_name");
        String address=resultSet.getString("address");
        int flight_id=resultSet.getInt("flight_id");
        Ticket ticket=new Ticket(client_name,address,flight_id);
        ticket.setID(id);
        return ticket;
    }

    @Override
    public Ticket findById(int id) {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        try(PreparedStatement ps=connection.prepareStatement("select * from tickets where ticket_id=?")){
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

    @Override
    public void add(Ticket entity) {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        try(PreparedStatement ps=connection.prepareStatement("insert into tickets (client_name,address,flight_id)values (?,?,?)")){
            ps.setString(1,entity.getClient_name());
           // ps.setInt(2,entity.getId());
            ps.setString(2,entity.getAddress());
            ps.setInt(3,entity.getFlightId());
            int result=ps.executeUpdate();
            logger.trace("Added {} instances",result);
        }
        catch (SQLException ex){
            logger.error(ex);
        }
        logger.traceExit();
    }
}
