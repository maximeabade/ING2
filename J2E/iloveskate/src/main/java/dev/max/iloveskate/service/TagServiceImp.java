package dev.max.iloveskate.service;

import dev.max.iloveskate.dao.TagDao;
import dev.max.iloveskate.exceptions.AlreadyExistException;
import dev.max.iloveskate.exceptions.InvalidFormatException;
import dev.max.iloveskate.exceptions.NotFoundException;
import dev.max.iloveskate.exceptions.PermissionLevelException;
import dev.max.iloveskate.model.Tag;
import dev.max.iloveskate.model.User;
import org.springframework.stereotype.Service;
import org.springframework.web.util.HtmlUtils;

import java.util.List;

@Service
public class TagServiceImp implements TagService {

    private final TagDao tagDao;


    public TagServiceImp(TagDao tagDao) {
        this.tagDao = tagDao;
    }

    @Override
    public Tag get(String id) throws NotFoundException {
        return tagDao.get(id).orElseThrow(NotFoundException::new);
    }

    @Override
    public void save(Tag tag, User user) throws AlreadyExistException, PermissionLevelException, InvalidFormatException {
        if (!user.isAdmin()) {
            throw new PermissionLevelException();
        }
        if (tagDao.get(tag.getId()).isPresent()) {
            throw new AlreadyExistException("Tag with same id already exists");
        }

        final String regex = "[a-z\\d]+";
        if (!tag.getId().matches(regex)) {
            throw new InvalidFormatException("Tag id must be alphanumeric and lowercase");
        }

        tag.setDisplayName(HtmlUtils.htmlEscape(tag.getDisplayName()));
        tagDao.save(tag);
    }

    @Override
    public void delete(Tag tag, User user) throws PermissionLevelException {
        if (!user.isAdmin()) {
            throw new PermissionLevelException();
        }
        tagDao.delete(tag);
    }

    @Override
    public void update(Tag tag, User user) throws PermissionLevelException {
        if (!user.isAdmin()) {
            throw new PermissionLevelException("User is not an admin");
        }
        tag.setDisplayName(HtmlUtils.htmlEscape(tag.getDisplayName()));
        tagDao.update(tag);
    }

    @Override
    public List<Tag> getAll(int page, int size, User user) throws PermissionLevelException {
        if (!user.isAdmin()) {
            throw new PermissionLevelException();
        }
        return tagDao.getAll(page, size);
    }

    @Override
    public List<Tag> getPublicTags(int page, int size) {
        return tagDao.getPublicTags(page, size);
    }
}
