package repository;

import domain.Entity;
import exceptions.RepoException;

import java.util.HashSet;
import java.util.Vector;

public interface Repository<E extends Entity<Integer>> {


    void add(E obj) throws RepoException;
    //void update(E obj,int id);
    E remove(int id) throws Exception;
    E remove(E entity) throws Exception;
    void loadData();
    int size();
    void storeData();
    E findElement(int id) throws RepoException;
    Vector<E> getAll();
    int getLastID();
}
