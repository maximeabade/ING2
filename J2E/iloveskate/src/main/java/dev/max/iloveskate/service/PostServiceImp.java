package dev.max.iloveskate.service;

import dev.max.iloveskate.dao.PostDao;
import dev.max.iloveskate.exceptions.NotAvailableException;
import dev.max.iloveskate.exceptions.NotFoundException;
import dev.max.iloveskate.exceptions.PermissionLevelException;
import dev.max.iloveskate.model.Post;
import dev.max.iloveskate.model.User;
import org.springframework.stereotype.Service;
import org.springframework.web.util.HtmlUtils;

import java.util.List;
import java.util.UUID;

@Service
public class PostServiceImp implements PostService {
    private final PostDao postDao;

    public PostServiceImp(PostDao postDao) {
        this.postDao = postDao;
    }

    @Override
    public Post get(UUID id) throws NotAvailableException, NotFoundException {
        Post post = postDao.get(id).orElseThrow(NotFoundException::new);

        if (post.getThread().isRemoved()) {
            throw new NotAvailableException();
        }
        return post;
    }

    @Override
    public void save(Post post) throws PermissionLevelException {
        if (post.getThread().isLocked()) {
            throw new PermissionLevelException("Thread is locked");
        }
        if (post.getThread().isRemoved()) {
            throw new PermissionLevelException("Thread is removed");
        }
        post.setContent(HtmlUtils.htmlEscape(post.getContent()));
        postDao.save(post);
    }

    @Override
    public void delete(Post post, User user) throws PermissionLevelException {
        if (post.getAuthor().equals(user) || user.isAdmin()) {
            post.setRemoved(true);
            post.setContent("[removed]");
            postDao.update(post);
        } else {
            throw new PermissionLevelException();
        }
    }

    @Override
    public void update(Post post, User user) throws PermissionLevelException, NotAvailableException {
        if (post.isRemoved()) {
            throw new NotAvailableException();
        }

        if (post.getAuthor().equals(user)) {
            post.setContent(HtmlUtils.htmlEscape(post.getContent()));
            postDao.update(post);
        } else {
            throw new PermissionLevelException();
        }
    }

    @Override
    public List<Post> getAllByUser(User user) {
        return postDao.getAllByUser(user);
    }

    public boolean toggleVote(Post post, User user) {
        boolean r = post.toggleVote(user);
        postDao.update(post);
        return r;
    }
}
