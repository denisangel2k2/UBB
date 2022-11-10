package repository;

import domain.User;

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

    @Override
    protected User extractEntity() {
        return null;
    }
}
