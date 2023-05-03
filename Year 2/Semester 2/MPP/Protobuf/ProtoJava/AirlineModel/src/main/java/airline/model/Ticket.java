package airline.model;

import java.io.Serializable;

public class Ticket extends Entity<Integer> implements Serializable{
    private String client_name;
    private final String address;
    private final int flightId;

    public Ticket(String client_name,String address, int flightId) {
        this.client_name = client_name;
        this.address = address;
        this.flightId=flightId;
    }

    public String getClient_name() {
        return client_name;
    }

    public String getAddress() {
        return address;
    }

    public int getFlightId(){
        return flightId;
    }

    @Override
    public String toString() {
        return "Ticket{" +
                "client_name='" + client_name + '\'' +
                ", address='" + address + '\'' +
                ", flightId=" + flightId +
                '}';
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }
}
