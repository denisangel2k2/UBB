package service;

import domain.User;
import exceptions.NetworkException;
import exceptions.RepoException;

import java.util.List;
import java.util.Vector;

public interface Service {

    void add(String firstName, String lastName, String email) throws Exception;
    void remove (int id) throws Exception;
    void addFriendship(int id1, int id2) throws NetworkException, RepoException;
    void removeFriendship(int id1, int id2) throws NetworkException, RepoException;
    int numberOfCommunities();
    List<User> mostSociableCommunity();
    Vector<User> getAll();

}
