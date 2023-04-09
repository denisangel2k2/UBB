package airline.persistence;


import airline.model.Flight;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import java.util.List;
import java.util.Properties;

public class FlightRepository implements IFlightRepository {
    private static final Logger logger= LogManager.getLogger();
    private JdbcUtils dbUtils;

    public FlightRepository(Properties properties) {
        dbUtils=new JdbcUtils(properties);
    }
    @Override
    public Iterable<Flight> getAll() {
        //logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        List<Flight> flightList=new ArrayList<>();
        try(PreparedStatement ps=connection.prepareStatement("select * from flights")) {
            try (ResultSet resultSet = ps.executeQuery()) {
                while (resultSet.next()) {
                    Flight flight=extractEntity(resultSet);
                    flightList.add(flight);

                }
            }
        }
        catch(SQLException ex) {
            logger.error(ex);
        }
        logger.traceExit();
        return flightList;
    }

    private Flight extractEntity(ResultSet resultSet) throws SQLException {
        int id=resultSet.getInt("flight_id");
        String destination=resultSet.getString("destination");
        String data=resultSet.getString("data");
        String hour=resultSet.getString("hour");
        int numberOfSeats=resultSet.getInt("no_seats");
        int availableSeats=resultSet.getInt("available_seats");
        Flight flight=new Flight(destination,data,hour,numberOfSeats);
        flight.setAvailableSeats(availableSeats);
        flight.setID(id);
        return flight;
    }

    @Override
    public Flight findById(int id) {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        try(PreparedStatement ps=connection.prepareStatement("select * from flights where id=?")){
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
    public void add(Flight entity) {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        try(PreparedStatement ps=connection.prepareStatement("insert into flights (data,hour,no_seats,destination,available_seats) values (?,?,?,?,)")){
            ps.setString(1,entity.getDate());
            ps.setString(2,entity.getHour());
            ps.setInt(3,entity.getNumberOfSeats());
            ps.setString(4,entity.getDestination());
            ps.setInt(5,entity.getAvailableSeats());
            int result=ps.executeUpdate();
            logger.trace("Added {} instances",result);
        }
        catch (SQLException ex){
            logger.error(ex);
        }
        logger.traceExit();
    }

    @Override
    public void updateNumberOfSeats(int flightId) {
        logger.traceEntry();
        Connection connection= dbUtils.getConnection();
        try(PreparedStatement ps=connection.prepareStatement("update flights set available_seats=available_seats-1 where flight_id=?")){
            ps.setInt(1,flightId);
            int result=ps.executeUpdate();
            logger.trace("Updated {} instances",result);
        }
        catch (SQLException ex){
            logger.error(ex);
        }
        logger.traceExit();
    }
}
