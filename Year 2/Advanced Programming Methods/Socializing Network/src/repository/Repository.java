package repository;

import exceptions.RepoException;

import java.util.Vector;

public interface Repository<T> {

    void add(T obj);
    T remove(int id) throws Exception;

    T findElement(int id) throws RepoException;
    Vector<T> getAll();
}
