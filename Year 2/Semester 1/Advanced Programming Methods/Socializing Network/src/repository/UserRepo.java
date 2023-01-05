package repository;

import domain.User;
import exceptions.RepoException;

public class UserRepo extends AbstractRepo<User>{

    public UserRepo(String filepath) {
        super(filepath);
        loadData();
    }
    @Override
    protected User extractEntity(String line) {
        String[] words=line.split(";");
        User user=new User(words[1],words[2],words[3]);
        user.setId(Integer.parseInt(words[0]));
        return user;
    }

    public void update(User u1) throws RepoException {
        User current_user=super.findElement(u1.getId());
        current_user.setEmail(u1.getEmail());
        current_user.setFirstName(u1.getFirstName());
        current_user.setLastName(u1.getLastName());
        super.storeData();
    }


}
