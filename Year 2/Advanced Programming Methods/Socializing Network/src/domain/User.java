package domain;

import java.util.Objects;

public class User {
    private final int id;

    public int getId() {
        return id;
    }

    public String getLastName() {
        return lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getEmail() {
        return email;
    }

    private String lastName;
    private String firstName;
    private String email;

    public User(int id, String nume, String prenume, String email) {
        this.id = id;
        this.lastName = nume;
        this.firstName = prenume;
        this.email = email;
    }

    @Override
    public String toString() {
        return "id=" + id +
                ", lastName='" + lastName + '\'' +
                ", firstName='" + firstName + '\'' +
                ", email='" + email + '\'';
    }
    public String printPatternString(){
        return "ID: " + id + " First Name: " + firstName + " Last Name: " + lastName + " Email: " + email;
    }
/*
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return id == user.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
    */
}
