package service;

import domain.Friendship;
import domain.User;

import domain.validation.Validator;
import exceptions.NetworkException;
import exceptions.RepoException;
import exceptions.ValidationException;
import repository.FriendshipRepo;
import repository.Network;
import repository.UserRepo;

import java.security.KeyPair;
import java.util.*;

public class AppService implements Service {
    private  UserRepo repository_user;
    private final Validator<User> validator;
    private final Validator<Friendship> validator_fr;
    private  FriendshipRepo repository_friendship;



    public AppService(UserRepo repository_user,FriendshipRepo repository_friendship, Validator<User> validator, Validator<Friendship> validator2) {
        this.repository_user = repository_user;
        this.validator = validator;
        this.validator_fr=validator2;
        this.repository_friendship=repository_friendship;
    }


    /**
     * Adds a friendship between the users with given ids
     * @param id1 int
     * @param id2 int
     * @throws NetworkException if there already exists a friendship
     * @throws RepoException if the users do not exist
     */
    @Override
    public void addFriendship(int id1, int id2) throws NetworkException, RepoException, ValidationException {

        User u1 = repository_user.findElement(id1);
        User u2 = repository_user.findElement(id2);
        Friendship f1=new Friendship(u1,u2);
        Friendship f2=new Friendship(u2,u1);

        validator_fr.validate(f1);
        validator_fr.validate(f2);

        f1.setId(repository_friendship.getLastID()+1);
        f2.setId(repository_friendship.getLastID()+2);
        repository_friendship.add(f1);
        repository_friendship.add(f2);


    }

    /**
     * Removes a friendship from the system
     * @param id1 int
     * @param id2 int
     * @throws if friendship does not exist
     * @throws RepoException if the users do not exist
     */
    @Override
    public void removeFriendship(int id1,int id2) throws Exception {

        User u1= repository_user.findElement(id1);
        User u2= repository_user.findElement(id2);
        Friendship f1=new Friendship(u1,u2);
        Friendship f2=new Friendship(u2,u1);
        validator_fr.validate(f1);
        validator_fr.validate(f2);

        repository_friendship.remove(f1);
        repository_friendship.remove(f2);

    }


    @Override
    public HashMap<User,String> getFriends(int id) {

        HashMap<User,String> users=new HashMap<>();
        Vector<Friendship> friendships=repository_friendship.getAll();
        for (Friendship friendship : friendships){
            if (friendship.getUser1().getId()==id)
                users.put(friendship.getUser1(),friendship.getFriendsFrom());
        }
        return users;
    }


    /**
     *
     * @return number of communities
     */
    private Network createNetwork(){
        Network network=new Network(repository_friendship.getAll());
        return network;
    }
    @Override
    public int numberOfCommunities() {
        Network network=createNetwork();
        return network.getNumberOfCommunities();
    }

    /**
     *
     * @return list with the users from the most sociable community
     */
    @Override
    public List<User> mostSociableCommunity() {
        Network network=createNetwork();
        var lista = network.mostSociableCommunity();
        List<User> userList = new ArrayList<>();
        if (lista!=null) {
            for (int id : lista)
                try {
                    userList.add(repository_user.findElement(id));
                } catch (RepoException ex) {
                }
        }
        return userList;
    }

    /**
     *
     * @return the maximum id of a user from the system
     */


    /**
     * Removes a user by id
     * @param id int
     * @throws Exception if the user with given id does not exist
     */
    @Override
    public void remove(int id) throws Exception {
       // User user=repository_user.remove(id);
        User user=repository_user.findElement(id);
        repository_user.remove(user);
        repository_friendship.removeAllFriendshipsByUser(user);
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
        int id = repository_user.getLastID() + 1;
        User user = new User(lastName, firstName, email);
        user.setId(id);
        validator.validate(user);
        repository_user.add(user);

    }


    /**
     *
     * @return a list with all the users
     */
    @Override
    public Vector<User> getAll() {
        return repository_user.getAll();
    }
}
