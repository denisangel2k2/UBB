package repository;

import domain.Friendship;
import domain.User;
import exceptions.RepoException;

import java.util.Optional;
import java.util.Vector;

public class FriendshipRepo extends AbstractRepo<Friendship> {
    private UserRepo repoUser;
    @Override
    protected Friendship extractEntity(String line) {
        String[] words=line.split(";");
        try{
        Friendship friendship=new Friendship(repoUser.findElement(Integer.parseInt(words[1])),
                repoUser.findElement(Integer.parseInt(words[2])));
        friendship.setId(Integer.parseInt(words[0]));
        friendship.setFriendsFrom(words[3]);
        return friendship;
        }
        catch (RepoException ex){
            ex.printStackTrace();
        }
        return null;
    }

    @Override
    protected Friendship extractEntity() {
        return null;
    }

    public FriendshipRepo(String filepath, UserRepo repoUser) {
        super(filepath);
        this.repoUser=repoUser;
        loadData();
    }
    public void removeAllFriendshipsByUser(User user){
        Vector<Friendship> friendships=super.getAll();
        for (Friendship friendship : friendships)
            if (friendship.getUser1().getId() == user.getId())
                friendships.remove(friendship);

        for (Friendship friendship : friendships)
            if (friendship.getUser2().getId()==user.getId())
                friendships.remove(friendship);

        storeData();
    }



}
