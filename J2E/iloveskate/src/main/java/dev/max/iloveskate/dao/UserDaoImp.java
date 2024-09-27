package dev.max.iloveskate.dao;

import dev.max.iloveskate.model.User;
import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import javax.transaction.Transactional;
import java.util.List;
import java.util.Optional;
import java.util.UUID;

@Repository
@Transactional
public class UserDaoImp implements UserDao {

    @Autowired
    private SessionFactory sessionFactory;

    @Override
    public Optional<User> get(UUID id) {
        return Optional.ofNullable(sessionFactory.getCurrentSession().get(User.class, id));
    }

    @Override
    @SuppressWarnings("unchecked")
    public List<User> getAll(int page, int size) {
        return sessionFactory.getCurrentSession().createQuery("from User").list();
    }

    @Override
    public void save(User user) {
        sessionFactory.getCurrentSession().save(user);
    }

    @Override
    public void update(User user) {
        sessionFactory.getCurrentSession().update(user);
    }

    @Override
    public void delete(User user) {
        sessionFactory.getCurrentSession().delete(user);
    }

    @Override
    public User findByUsername(String username) {
        return (User) sessionFactory.getCurrentSession().createQuery("from User where username = :username")
                .setParameter("username", username)
                .uniqueResult();
    }

    @Override
    public User findByEmail(String email) {
        return (User) sessionFactory.getCurrentSession().createQuery("from User where email = :email")
                .setParameter("email", email)
                .uniqueResult();
    }

    public int countUserVotes(User user) {
        // Query the number of post where the user voted
        return ((Long) sessionFactory.getCurrentSession()
                .createQuery("select count(*) from Post where :user in elements(votes)")
                .setParameter("user", user)
                .uniqueResult()).intValue();
    }
}
