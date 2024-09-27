package dev.max.iloveskate.dao;

import dev.max.iloveskate.model.Post;
import dev.max.iloveskate.model.User;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

public interface PostDao extends Dao<Post> {
    Optional<Post> get(UUID id);

    List<Post> getAllByUser(User user);
}
