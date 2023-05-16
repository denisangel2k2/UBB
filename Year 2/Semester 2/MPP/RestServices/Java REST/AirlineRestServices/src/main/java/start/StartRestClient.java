package start;

import airline.model.Flight;
import org.springframework.web.client.RestClientException;
import rest.client.FlightClient;

public class StartRestClient {

    private final static FlightClient flightClient=new FlightClient();

    public static void main(String[] args) {
        Flight flight=new Flight("Bucharest", "01.01.2018", "10:00", 100, 100);

        try{
            show(()-> System.out.println(flightClient.addFlight(flight)));
            show(()->{
                Flight[] res=flightClient.getFlights();
                for(Flight f:res){
                    System.out.println(f.getId()+": "+f.getDestination());
                }
            });
            show(()->{
                var flightt=flightClient.getFlightById(1);

                System.out.println("Found flight:"+ flightt.getId()+": "+flight.getDestination());
            });
            show(()->{
                Flight[] res=flightClient.getFlights();
                Integer id=res[res.length-1].getId();
                flight.setAvailableSeats(99);
                flight.setId(id);
                flightClient.updateFlight(flight);
                Flight flightFound=flightClient.getFlightById(id);
                if (flightFound.getAvailableSeats()==99)
                    System.out.println("Flight updated successfully with available seats: " + flightFound.getAvailableSeats());
            });
            show(()->{
                Flight[] res=flightClient.getFlights();
                Integer id=res[res.length-1].getId();
                System.out.println("Deleting flight with id "+id);
                flightClient.deleteFlight(id);

                res=flightClient.getFlights();
                if (res[res.length-1].getId()!=id)
                    System.out.println("Flight deleted successfully");

            });

        }
        catch (RestClientException ex){
            System.out.println("Error: "+ex.getMessage());
        }

    }
    private static void show(Runnable task){
        try{
            task.run();
        }catch(Exception ex){
            System.out.println("Service exception"+ ex);
        }
    }
}
