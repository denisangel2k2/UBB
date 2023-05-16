package rest.client;

import airline.model.Flight;
import org.springframework.web.client.RestTemplate;
import rest.services.ServiceException;

import java.util.concurrent.Callable;

public class FlightClient {
    public static final String URL="http://localhost:8080/airline/flights";

    private RestTemplate restTemplate=new RestTemplate();

    private <T> T execute(Callable<T> callable){
        try{
            return callable.call();
        }catch(Exception ex){
            throw new ServiceException(ex);
        }
    }

    public Flight[] getFlights(){
        return execute(()->restTemplate.getForObject(URL, Flight[].class));
    }

    public Flight getFlightById(Integer id){
        return execute(()->restTemplate.getForObject(String.format("%s/%d", URL, id), Flight.class));
    }

    public Flight addFlight(Flight flight){
        return execute(()->restTemplate.postForObject(URL, flight, Flight.class));
    }
    public void updateFlight(Flight flight){
        execute(()->{
           restTemplate.put(String.format("%s/%d", URL, flight.getId()), flight);
           return null;
        });
    }
    public void deleteFlight(Integer id){
        execute(()->{
            restTemplate.delete(String.format("%s/%d", URL, id));
            return null;
        });
    }


}
