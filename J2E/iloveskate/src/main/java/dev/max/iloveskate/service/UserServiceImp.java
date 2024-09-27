package dev.max.iloveskate.service;

import dev.max.iloveskate.dao.UserDao;
import dev.max.iloveskate.exceptions.AlreadyExistException;
import dev.max.iloveskate.exceptions.InvalidFormatException;
import dev.max.iloveskate.exceptions.NotFoundException;
import dev.max.iloveskate.exceptions.PermissionLevelException;
import dev.max.iloveskate.model.User;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;
import java.util.Optional;
import java.util.UUID;

@Service
public class UserServiceImp implements UserService {
    private final UserDao userDao;

    public UserServiceImp(UserDao userDao) {
        this.userDao = userDao;
    }

    @Transactional
    public User get(UUID id) throws NotFoundException {
        if (id == null) {
            throw new NotFoundException();
        }
        return userDao.get(id).orElseThrow(NotFoundException::new);
    }

    @Transactional
    public void save(User user, String originalPassword) throws AlreadyExistException, InvalidFormatException {
        if (userDao.findByUsername(user.getUsername()) != null) {
            throw new AlreadyExistException("Username already exists");
        }
        if (!checkUsername(user.getUsername())) {
            throw new InvalidFormatException("Username is not valid");
        }
        if (userDao.findByEmail(user.getEmail()) != null) {
            throw new AlreadyExistException("Email already exists");
        }
        if (!checkEmail(user.getEmail())) {
            throw new InvalidFormatException("Email is not valid");
        }
        if (!checkPassword(originalPassword)) {
            throw new InvalidFormatException("Password is not valid");
        }
        user.setPassword(new BCryptPasswordEncoder().encode(originalPassword));

        userDao.save(user);
    }

    /**
     * Check if the username is valid
     * Username is valid if it contains only letters and numbers and "_"
     * and it's length is between 4 and 16
     *
     * @param username Username to check
     * @return true if the username is valid
     */
    private boolean checkUsername(String username) {
        return username != null && username.matches("^[a-zA-Z0-9_]{4,16}$");
    }

    /**
     * Check if the email is valid
     *
     * @param email Email to check
     * @return true if the email is valid
     */
    private boolean checkEmail(String email) {
        return email != null && email.matches("^(?=.{1,64}@)[A-Za-z0-9_-]+(\\.[A-Za-z0-9_-]+)*@" + "[^-][A-Za-z0-9-]+(\\.[A-Za-z0-9-]+)*(\\.[A-Za-z]{2,})$");
    }

    /**
     * Check if the password is valid
     * Password is valid if it has at least 8 characters, one uppercase, one lowercase
     * one number and one special character
     *
     * @param password Password to check
     * @return true if the password is valid
     */
    private boolean checkPassword(String password) {
        return password != null && password.matches("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    }

    @Transactional
    public void delete(User user, User userRequesting) throws PermissionLevelException {
        if (!userRequesting.isAdmin() && !userRequesting.equals(user)) {
            throw new PermissionLevelException();
        }
        userDao.delete(user);
    }

    @Transactional
    public void update(User user, String originalPassword, String newPassword, String email, String username) throws PermissionLevelException, InvalidFormatException, AlreadyExistException {

        if (!new BCryptPasswordEncoder().matches(originalPassword, user.getPassword())) {
            throw new PermissionLevelException("Password does not match");
        }

        if (!newPassword.isBlank()) {
            if (!checkPassword(newPassword)) {
                throw new InvalidFormatException("New password is not valid");
            }
            user.setPassword(new BCryptPasswordEncoder().encode(newPassword));
        }

        if (!email.equals(user.getEmail())) {
            if (!checkEmail(email)) {
                throw new InvalidFormatException("Email is not valid");
            }
            if (userDao.findByEmail(email) != null) {
                throw new AlreadyExistException("Email already used");
            }
            user.setEmail(email);
        }

        if (!username.equals(user.getUsername())) {
            if (!checkUsername(username)) {
                throw new InvalidFormatException("Username is not valid");
            }
            if (userDao.findByUsername(username) != null) {
                throw new AlreadyExistException("Username already taken");
            }
            user.setUsername(username);
        }

        // Everything is valid, save it
        userDao.update(user);
    }

    @Transactional
    public Optional<User> findByUsername(String username) {
        User user = userDao.findByUsername(username);
        return Optional.ofNullable(user);
    }

    @Transactional
    public Optional<User> findByEmail(String email) {
        User user = userDao.findByEmail(email);
        return Optional.ofNullable(user);
    }


    @Transactional
    public List<User> getAll(int page, int size) {
        return userDao.getAll(page, size);
    }

    @Transactional
    public User getUserFromCredentials(String login, String password) throws NotFoundException {
        User user;

        Optional<User> result = findByEmail(login);
        if (result.isPresent()) {
            user = result.get();
        } else {
            result = findByUsername(login);
            if (result.isPresent()) {
                user = result.get();
            } else {
                throw new NotFoundException();
            }
        }
        if (!new BCryptPasswordEncoder().matches(password, user.getPassword())) {
            throw new NotFoundException();
        }
        return user;
    }

    public int countUserVotes(User user) {
        user.setPoints(userDao.countUserVotes(user));
        userDao.update(user);
        return user.getPoints();

    }
}
