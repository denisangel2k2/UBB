package rest.services;


import airline.model.Flight;
import airline.persistence.FlightRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Comparator;
import java.util.List;

@RestController
@RequestMapping("/airline/flights")
public class FlightController {

    @Autowired
    private FlightRepository flightRepository;

    @RequestMapping(method= RequestMethod.GET)
    public List<Flight> getFlights(){
        System.out.println("Get all flights ...");
        var flights = (List<Flight>) flightRepository.getAll();
        Flight[] flightsArray = new Flight[flights.size()];
        flightsArray = flights.toArray(flightsArray);
        return flights;
    }

    @RequestMapping(value="/{id}", method=RequestMethod.GET)
    public ResponseEntity<?> getFlightById(@PathVariable Integer id){
        System.out.println("Get flight by id "+id);
        Flight flight = flightRepository.findById(id);


        if (flight==null){
            return new ResponseEntity<String>("Flight not found", HttpStatus.NOT_FOUND);
        }
        else

            return new ResponseEntity<Flight>(flight, HttpStatus.OK);
    }

    @PostMapping
    public Flight addFlight(@RequestBody Flight flight){
        System.out.println("Adding flight ...");
        flightRepository.add(flight);
        System.out.println("Flight added");
        Flight flightFound=((List<Flight>) flightRepository.getAll()).stream()
                .max(Comparator.comparing(Flight::getId)).get();
        System.out.println("Flight found: "+flightFound.getDestination());
        return flightFound;
    }


    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    public Flight updateFlight(@PathVariable Integer id) {
        flightRepository.updateNumberOfSeats(id);
        Flight flight = flightRepository.findById(id);
        return flight;
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<?> deleteFlight(@PathVariable Integer id){
        flightRepository.delete(id);
        return new ResponseEntity<String>("Flight deleted succesfully!",HttpStatus.OK);
    }
    @ExceptionHandler(Exception.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    //@ResponseStatus(HttpStatus.NOT_FOUND)
    public String flightError(Exception e) {
        return e.getMessage();
    }



}
