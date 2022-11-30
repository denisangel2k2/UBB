package domain;

import java.util.Objects;

public class User extends Entity<Integer> {

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

    public User(String nume, String prenume, String email) {
        this.lastName = nume;
        this.firstName = prenume;
        this.email = email;
    }


    @Override
    public String toString() {
        return "id=" + getId() +
                ", lastName='" + lastName + '\'' +
                ", firstName='" + firstName + '\'' +
                ", email='" + email + '\'';
    }

    /**
     * @return String print format
     */
    public String printPatternString() {
        return "ID: " + getId() + " First Name: " + firstName + " Last Name: " + lastName + " Email: " + email;
    }

    /**
     * @return String csv format
     */
    @Override
    public String fileCsvPatternString() {
        return getId() + ";" + lastName + ";" + firstName + ";" + email + "\n";
    }


    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * @param other
     */
    @Override
    public void set(Entity other) {
        this.email = ((User) other).email;
        this.firstName = ((User) other).firstName;
        this.lastName = ((User) other).lastName;
    }
}
