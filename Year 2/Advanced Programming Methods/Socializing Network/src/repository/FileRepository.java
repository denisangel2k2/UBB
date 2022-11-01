package repository;
import domain.User;
import exceptions.RepoException;
import utils.Constants;


import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Optional;
import java.util.Vector;

public class FileRepository implements Repository<User>{
    private Vector<User> userList;
    private static String filepath;

    public FileRepository(String _filepath) {
        userList=new Vector<User>();
        filepath=_filepath;
        loadData();
    }

    /**
     * Loads data in memory from the persistence of application
     */
    private void loadData(){
        userList.clear();
        Path path= Paths.get(filepath);
        try {
            List<String> lines = Files.readAllLines(path);
            for (String line : lines) {
                String[] words = line.split(";");
                User user = new User(Integer.parseInt(words[0]), words[1], words[2], words[3]);
                userList.add(user);
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    /**
     * Stores data from memory to the persistence layer
     */
    private void storeData(){
        Path path=Paths.get(filepath);

        try{
            StringBuilder info= new StringBuilder();
            for (User user : userList) {
                info.append(user.getId())
                        .append(";")
                        .append(user.getLastName())
                        .append(";")
                        .append(user.getFirstName())
                        .append(";")
                        .append(user.getEmail())
                        .append("\n");

            }
            Files.writeString(path, info.toString());
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    /**
     * Adds an user to the repository
     * @param obj User
     */
    @Override
    public void add(User obj) {

        loadData();
        userList.add(obj);
        storeData();
    }

    /**
     * Removes an user from the repository by giving its id, returns the deleted user
     * @param id int
     * @return User
     * @throws RepoException if there is no user with given id
     */
    @Override
    public User remove(int id) throws RepoException {
        loadData();
        User user=find(id);
        if (user!=null)
        {
            userList.remove(user);
            storeData();
            return user;
        }
        else throw new RepoException(Constants.REPO_REMOVE_USER);
    }

    /**
     * Finds the user with given id in the repository and returns it
     * @param id int
     * @return User
     * @throws RepoException if the user doesn't exist in the repository
     */
    @Override
    public User findElement(int id) throws RepoException{
        User user=find(id);
        if (user==null)
            throw new RepoException(Constants.REPO_NO_ELEMENT_FOUND);
        else return user;
    }

    /**
     * Returns the user with given id as parameter exists in the repository or null if not
     * @param id int
     * @return True/False
     */
    private User find(int id) {
        loadData();
        Optional<User> usersWithGivenID=userList.stream().filter(user -> user.getId()==id).findFirst();
        if (usersWithGivenID.isPresent())
            return usersWithGivenID.get();
        else return null;
    }

    /**
     *
     * @return vector of all users
     */
    @Override
    public Vector<User> getAll() {
        return userList;
    }

}
