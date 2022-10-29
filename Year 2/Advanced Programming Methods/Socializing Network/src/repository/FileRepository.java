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
    private void storeData(){
        Path path=Paths.get(filepath);

        try{
            String info="";
            for (User user : userList) {
                info += Integer.toString(user.getId()) + ";" + user.getLastName() + ";" + user.getFirstName() + ";" + user.getEmail() + "\n";

            }
            Files.writeString(path, info);
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    @Override
    public void add(User obj) {

        loadData();
        userList.add(obj);
        storeData();
    }

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
    @Override
    public User findElement(int id) throws RepoException{
        User user=find(id);
        if (user==null)
            throw new RepoException(Constants.REPO_NO_ELEMENT_FOUND);
        else return user;
    }
    private User find(int id) {
        loadData();
        Optional<User> usersWithGivenID=userList.stream().filter(user -> user.getId()==id).findFirst();
        if (usersWithGivenID.isPresent())
            return usersWithGivenID.get();
        else return null;
    }

    @Override
    public Vector<User> getAll() {
        return userList;
    }

}
