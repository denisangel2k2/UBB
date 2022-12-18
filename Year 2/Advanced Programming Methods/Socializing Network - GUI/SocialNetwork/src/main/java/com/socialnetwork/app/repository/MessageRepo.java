package com.socialnetwork.app.repository;

import com.socialnetwork.app.domain.Message;
import com.socialnetwork.app.exceptions.RepoException;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

public class MessageRepo extends AbstractRepo<Message> {
    public MessageRepo(String url, String userName, String password) {
        super(url, userName, password);
    }

    @Override
    protected Message extractEntity(String line) {
        return null;
    }

    @Override
    protected List<Message> extractEntity(ResultSet set) throws SQLException {
        return null;
    }

    @Override
    protected PreparedStatement ps_getAll(Connection connection) throws SQLException {
        return null;
    }

    @Override
    protected void storeEntity(Message entity, Connection connection) throws SQLException, RepoException {

    }

    @Override
    protected void deleteEntity(Message entity, Connection connection) throws SQLException {

    }

    @Override
    protected void updateEntity(Message entity, Connection connection) throws SQLException {

    }
}
