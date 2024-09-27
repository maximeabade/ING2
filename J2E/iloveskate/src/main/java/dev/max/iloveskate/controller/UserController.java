package dev.max.iloveskate.controller;

import dev.max.iloveskate.exceptions.AlreadyExistException;
import dev.max.iloveskate.exceptions.InvalidFormatException;
import dev.max.iloveskate.exceptions.NotFoundException;
import dev.max.iloveskate.exceptions.PermissionLevelException;
import dev.max.iloveskate.model.User;
import dev.max.iloveskate.service.PostService;
import dev.max.iloveskate.service.ThreadService;
import dev.max.iloveskate.service.UserService;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.Optional;

@Controller
public class UserController {

    private final UserService userService;
    private final ThreadService threadService;

    private final PostService postService;

    public UserController(UserService userService, ThreadService threadService, PostService postService) {
        this.userService = userService;
        this.threadService = threadService;
        this.postService = postService;
    }

    /**
     * GET - Login page mapping
     * <p>
     * If user is already logged in, return to "/"
     * </p>
     */
    @GetMapping("/login")
    public String login(HttpSession session) {
        if (session.getAttribute("user") != null) {
            return "redirect:/";
        }
        return "account/login";
    }

    /**
     * GET - Register page mapping
     * <p>
     * If user is already logged in, return to "/"
     * </p>
     */
    @GetMapping("/register")
    public String register(HttpSession session) {
        if (session.getAttribute("user") != null) {
            return "redirect:/";
        }
        return "account/register";
    }

    /**
     * POST - Process login information and connect the user
     * <ul>
     *      <li>
     *          If user is already logged in, return to "/".
     *      </li>
     *      <li>
     *          On successful login redirect user to "/".
     *      </li>
     *      <li>
     *          In case of wrong login information, redirect user to login
     *          page with information on what went wrong.
     *      </li>
     * </ul>
     */
    @PostMapping("/login")
    public String login(String login, String password, Model model, HttpSession session) {
        if (session.getAttribute("user") != null) {
            return "redirect:/";
        }

        try {
            User user = userService.getUserFromCredentials(login, password);
            session.setAttribute("user", user);
            return "redirect:/";
        } catch (NotFoundException ex) {
            model.addAttribute("error", "Wrong credentials");
            model.addAttribute("login", login);
            return "account/login";
        }
    }

    /**
     * POST - Register a new user
     * <ul>
     *     <li>
     *         If user is already connected redirect to "/".
     *     </li>
     *     <li>
     *         In case of wrong register information, redirect user to
     *         register page with information on what went wrong.
     *     </li>
     *     <li>
     *         On successful register, connect user and redirect to "/".
     *     </li>
     * </ul>
     */
    @PostMapping("/register")
    public String register(String username, String email, String password, Model model, HttpSession session) {
        if (session.getAttribute("user") != null) {
            return "redirect:/";
        }
        User user = new User();
        user.setUsername(username);
        user.setEmail(email);
        try {
            userService.save(user, password);
            session.setAttribute("user", user);
            return "redirect:/";
        } catch (AlreadyExistException | InvalidFormatException e) {
            model.addAttribute("error", e.getMessage());
            model.addAttribute("username", username);
            model.addAttribute("email", email);
        }
        return "account/register";
    }

    /**
     * GET - Check if a username is available
     *
     * @return boolean in string form
     */
    @GetMapping("/check-username-available/{username}")
    @ResponseBody
    public String checkUsername(@PathVariable String username) {
        return userService.findByUsername(username).isPresent() ? "false" : "true";
    }

    /**
     * POST - Logout user by invalidating its session, then redirect to "/"
     */
    @PostMapping("/logout")
    public String logout(HttpSession session) {
        session.invalidate();
        return "redirect:/";
    }

    /**
     * GET - Edit page mapping
     * <p>
     * If user is not logged in, redirect to "/login"
     * </p>
     */
    @GetMapping("/account")
    public String editAccount(HttpSession session) {
        if (session.getAttribute("user") == null) {
            return ("redirect:/login");
        }

        return ("account/edit");
    }

    /**
     * PUT - Register a new user
     * <ul>
     *     <li>
     *         If user is already connected redirect to "/".
     *     </li>
     *     <li>
     *         On successful update, update session and redirect to "/".
     *     </li>
     *     <li>
     *         In case of wrong information, redirect user to
     *         edit-account page with information on what went wrong.
     *     </li>
     * </ul>
     */
    @PostMapping("/account")
    public String editAccount(
            @RequestParam(required = false, defaultValue = "") String email,
            @RequestParam(required = false, defaultValue = "") String username,
            @RequestParam(required = false, defaultValue = "") String newPassword,
            @RequestParam(required = false, defaultValue = "") String currentPassword,
            Model model,
            HttpServletResponse response,
            HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "account/login";
        }

        try {
            userService.update(user, currentPassword, newPassword, email, username);
            return "redirect:/";
        } catch (AlreadyExistException | PermissionLevelException | InvalidFormatException e) {
            model.addAttribute("error", e.getMessage());
            model.addAttribute("username", username);
            model.addAttribute("email", email);
            response.setStatus(HttpStatus.BAD_REQUEST.value());
            return "account/edit";
        }
    }

    /**
     * GET - User Thread list
     */
    @GetMapping("/users/{username}")
    public String userThreads(@PathVariable String username, @RequestParam(required = false, defaultValue = "false") boolean removed, Model model, HttpSession session) {
        User currentUser = (User) session.getAttribute("user");
        Optional<User> user = userService.findByUsername(username);
        if (user.isPresent()) {
            model.addAttribute("viewUser", user.get());
            try {
                model.addAttribute("pageTitle", user.get().getUsername());
                model.addAttribute("threads", threadService.getAllByUser(user.get(), 0, 10, removed, currentUser));
            } catch (PermissionLevelException e) {
                model.addAttribute("error", e.getMessage());
            }
            return "content/user";
        } else {

            return "errors/notAvailable";
        }
    }

    /**
     * GET - Profile page mapping
     */
    @GetMapping("/profile")
    public String profile(HttpSession session) {
        if (session.getAttribute("user") == null) {
            return ("redirect:/login");
        }

        return ("redirect:/users/" + ((User) session.getAttribute("user")).getUsername());
    }

    /**
     * GET - User posts list
     */
    @GetMapping("/users/{username}/posts")
    public String userPosts(@PathVariable String username, @RequestParam(required = false, defaultValue = "false") boolean removed, Model model, HttpSession session) {
        User currentUser = (User) session.getAttribute("user");
        Optional<User> user = userService.findByUsername(username);
        if (user.isPresent()) {
            model.addAttribute("pageTitle", user.get().getUsername());
            model.addAttribute("viewUser", user.get());
            model.addAttribute("posts", postService.getAllByUser(user.get()));

            return "content/user_posts";
        } else {

            return "errors/notAvailable";
        }
    }
}
