package airline.model;

import java.io.Serializable;

public class Flight extends Entity<Integer> implements Serializable {
    private final String destination;
    private String date;
    private String hour;
    private int numberOfSeats;
    private int availableSeats;

    public Flight(String destination, String date, String hour, int numberOfSeats) {
        this.destination = destination;
        this.date = date;
        this.hour = hour;
        this.numberOfSeats = numberOfSeats;
        this.availableSeats=numberOfSeats;
    }

    public int getAvailableSeats() {
        return availableSeats;
    }

    public void setAvailableSeats(int availableSeats) {
        this.availableSeats = availableSeats;
    }

    @Override
    public String toString() {
        return "Flight{" +
                "destination='" + destination + '\'' +
                ", date='" + date + '\'' +
                ", hour='" + hour + '\'' +
                ", numberOfSeats=" + numberOfSeats +
                '}';
    }

    public String getDestination() {
        return destination;
    }

    public String getDate() {
        return date;
    }

    public String getHour() {
        return hour;
    }

    public int getNumberOfSeats() {
        return numberOfSeats;
    }
}
