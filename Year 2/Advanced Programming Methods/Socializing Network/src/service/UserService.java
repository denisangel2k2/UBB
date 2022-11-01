package service;

import domain.User;

import domain.validation.Validator;
import exceptions.NetworkException;
import exceptions.RepoException;
import repository.Network;
import repository.Repository;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Vector;

public class UserService implements Service {

    private final Network network = new Network();
    private final Repository<User> repository;
    private final Validator<User> validator;


    public UserService(Repository<User> repository, Validator<User> validator) {
        this.repository = repository;
        this.validator = validator;
    }


    /**
     * Adds a friendship between the users with given ids
     * @param id1 int
     * @param id2 int
     * @throws NetworkException if there already exists a friendship
     * @throws RepoException if the users do not exist
     */
    @Override
    public void addFriendship(int id1, int id2) throws NetworkException, RepoException {
        User u1 = repository.findElement(id1);
        User u2 = repository.findElement(id2);

        network.addFriendship(u1, u2);

    }

    /**
     * Removes a friendship from the system
     * @param id1 int
     * @param id2 int
     * @throws if friendship does not exist
     * @throws RepoException if the users do not exist
     */
    @Override
    public void removeFriendship(int id1,int id2) throws NetworkException,RepoException {
        User u1=repository.findElement(id1);
        User u2=repository.findElement(id2);
        network.removeFriendship(u1,u2);
    }

    /**
     *
     * @return number of communities
     */
    @Override
    public int numberOfCommunities() {
        return network.getNumberOfCommunities();
    }

    /**
     *
     * @return list with the users from the most sociable community
     */
    @Override
    public List<User> mostSociableCommunity() {
        var lista = network.mostSociableCommunity();
        List<User> userList = new ArrayList<>();
        if (lista!=null) {
            for (int id : lista)
                try {
                    userList.add(repository.findElement(id));
                } catch (RepoException ex) {
                }
        }
        return userList;
    }

    /**
     *
     * @return the maximum id of a user from the system
     */
    private int getLastID() {
        Vector<User> list = repository.getAll();
        int ID = -1;
        for (User user : list)
            ID = Math.max(ID, user.getId());
        if (ID == -1) return 1;
        else return ID;
    }

    /**
     * Removes a user by id
     * @param id int
     * @throws Exception if the user with given id does not exist
     */
    @Override
    public void remove(int id) throws Exception {
        repository.remove(id);
    }

    /**
     * Adds a user to the system with given information
     * @param firstName String
     * @param lastName String
     * @param email String
     * @throws Exception if the given paramaters are not valid
     */
    @Override
    public void add(String firstName, String lastName, String email) throws Exception {
        int id = getLastID() + 1;
        User user = new User(id, lastName, firstName, email);
        validator.validate(user);
        repository.add(user);
    }


    /**
     *
     * @return a list with all the users
     */
    @Override
    public Vector<User> getAll() {
        return repository.getAll();
    }
}
