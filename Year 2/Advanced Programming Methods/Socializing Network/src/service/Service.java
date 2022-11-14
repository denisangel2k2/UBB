package service;

import domain.Friendship;
import domain.User;
import exceptions.NetworkException;
import exceptions.RepoException;
import exceptions.ValidationException;

import java.util.HashMap;
import java.util.Vector;
import java.util.List;

public interface Service {

    void add(String firstName, String lastName, String email) throws Exception;
    void remove (int id) throws Exception;
    void addFriendship(int id1, int id2) throws NetworkException, RepoException, ValidationException;
    void removeFriendship(int id1, int id2) throws Exception;
    HashMap<User,String> getFriends(int id);
    int numberOfCommunities();
    void update(int idToChange, String firstName, String lastName, String email) throws RepoException, ValidationException;
    List<User> mostSociableCommunity();
    int sizeUsers();
    int sizeFriendships();
    Vector<User> getAllUsers();
    Iterable<Friendship> getAllFriendships();

}
