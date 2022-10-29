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


    @Override
    public void addFriendship(int id1, int id2) throws NetworkException, RepoException {
        User u1 = repository.findElement(id1);
        User u2 = repository.findElement(id2);

        network.addFriendship(u1, u2);

    }

    @Override
    public void removeFriendship(int id1,int id2) throws NetworkException,RepoException {
        User u1=repository.findElement(id1);
        User u2=repository.findElement(id2);
        network.removeFriendship(u1,u2);
    }

    @Override
    public int numberOfCommunities() {
        return network.getNumberOfCommunities();
    }

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

    private int getLastID() {
        Vector<User> list = repository.getAll();
        int ID = -1;
        for (User user : list)
            ID = Math.max(ID, user.getId());
        if (ID == -1) return 1;
        else return ID;
    }

    @Override
    public void remove(int id) throws Exception {
        repository.remove(id);
    }

    @Override
    public void add(String firstName, String lastName, String email) throws Exception {
        int id = getLastID() + 1;
        User user = new User(id, lastName, firstName, email);
        validator.validate(user);
        repository.add(user);
    }


    @Override
    public Vector<User> getAll() {
        return repository.getAll();
    }
}
