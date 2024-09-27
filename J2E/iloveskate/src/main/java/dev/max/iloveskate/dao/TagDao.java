package dev.max.iloveskate.dao;

import dev.max.iloveskate.model.Tag;

import java.util.List;
import java.util.Optional;

public interface TagDao extends Dao<Tag> {
    Optional<Tag> get(String id);

    List<Tag> getPublicTags(int page, int size);
}
