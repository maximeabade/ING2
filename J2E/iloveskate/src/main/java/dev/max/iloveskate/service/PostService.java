package dev.max.iloveskate.service;

import dev.max.iloveskate.exceptions.NotAvailableException;
import dev.max.iloveskate.exceptions.NotFoundException;
import dev.max.iloveskate.exceptions.PermissionLevelException;
import dev.max.iloveskate.model.Post;
import dev.max.iloveskate.model.User;

import java.util.List;
import java.util.UUID;

public interface PostService {
    /**
     * Get the post using its id.
     * If the post is marked as deleted the body will be
     * replaced by "[removed]".
     *
     * @return The post
     * @throws NotAvailableException Parent thread as been deleted
     * @throws NotFoundException     Post doesn't exist
     */
    Post get(UUID id) throws NotAvailableException, NotFoundException;

    /**
     * Create a new post in the database
     *
     * @param post The post to create
     */
    void save(Post post) throws PermissionLevelException;

    /**
     * Mark a thread a deleted, the user performing the
     * action need to be the author of the post or an admin
     *
     * @param post Post to delete
     * @param user The user requesting the deletion
     */
    void delete(Post post, User user) throws PermissionLevelException;

    /**
     * Update a post from the database, the user performing the
     * action need to be the author of the post or an admin
     *
     * @param post Post to update
     * @param user The user requesting the update
     */
    void update(Post post, User user) throws PermissionLevelException, NotAvailableException;

    List<Post> getAllByUser(User user);

    boolean toggleVote(Post post, User user);
}
