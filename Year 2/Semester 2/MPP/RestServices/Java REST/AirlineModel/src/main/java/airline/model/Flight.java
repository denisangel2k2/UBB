package airline.model;

import java.io.Serializable;

public class Flight extends Entity<Integer> implements Serializable {
    private final String destination;
    private String date;
    private String hour;
    private int numberOfSeats;
    private int availableSeats;

    public Flight() {
        this.destination = "";
        this.date = "";
        this.hour = "";
        this.numberOfSeats = 0;
        this.availableSeats=0;
    }
    public Flight(String destination, String date, String hour, int numberOfSeats) {
        this.destination = destination;
        this.date = date;
        this.hour = hour;
        this.numberOfSeats = numberOfSeats;
        this.availableSeats=numberOfSeats;
    }

    public Flight(String destination, String date, String hour, int numberOfSeats, int availableSeats) {
        this.destination = destination;
        this.date = date;
        this.hour = hour;
        this.numberOfSeats = numberOfSeats;
        this.availableSeats=availableSeats;
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
