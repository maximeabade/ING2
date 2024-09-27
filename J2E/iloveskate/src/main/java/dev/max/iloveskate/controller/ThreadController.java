package dev.max.iloveskate.controller;

import dev.max.iloveskate.exceptions.NotAvailableException;
import dev.max.iloveskate.exceptions.NotFoundException;
import dev.max.iloveskate.exceptions.PermissionLevelException;
import dev.max.iloveskate.model.Post;
import dev.max.iloveskate.model.Thread;
import dev.max.iloveskate.model.User;
import dev.max.iloveskate.service.PostService;
import dev.max.iloveskate.service.TagService;
import dev.max.iloveskate.service.ThreadService;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.List;
import java.util.UUID;

@Controller
public class ThreadController {

    private final ThreadService threadService;
    private final TagService tagService;

    private final PostService postService;

    public ThreadController(ThreadService threadService, TagService tagService, PostService postService) {
        this.threadService = threadService;
        this.tagService = tagService;
        this.postService = postService;
    }


    @GetMapping("/threads/{id}")
    public String thread(@PathVariable String id, Model model, HttpServletResponse response, HttpSession session) {
        User user = (User) session.getAttribute("user");
        UUID uuid = UUID.fromString(id);

        try {
            Thread thread = this.threadService.get(uuid, user);
            model.addAttribute("pageTitle", thread.getTitle());
            model.addAttribute("thread", thread);
        } catch (NotFoundException | NotAvailableException e) {
            response.setStatus(HttpStatus.NOT_FOUND.value());
            model.addAttribute("error", e.getMessage());
            return "errors/notAvailable";
        }
        return "content/thread";
    }


    @PostMapping("/threads")
    public String newThread(String title, String content, @RequestParam(name = "tag", required = false) List<String> Tags, Model model, HttpServletResponse response, HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "redirect:/login";
        }


        Post post = new Post();
        post.setContent(content);
        post.setAuthor(user);

        Thread thread = new Thread();
        thread.setTitle(title);
        thread.setEntry(post);

        if (Tags != null) {
            for (String tag : Tags) {
                try {
                    thread.addTag(this.tagService.get(tag));
                } catch (NotFoundException e) {
                    response.setStatus(HttpStatus.NOT_FOUND.value());
                    return "redirect:/";
                }
            }
        }

        post.setThread(thread);

        try {
            this.threadService.save(thread);
            postService.save(post);
            return "redirect:/threads/" + thread.getId();
        } catch (Exception e) {
            response.setStatus(HttpStatus.BAD_REQUEST.value());
            model.addAttribute("tags", this.tagService.getPublicTags(0, 100));
            model.addAttribute("title", title);
            model.addAttribute("content", content);
            model.addAttribute("error", e.getMessage());
            return "content/new";
        }

    }

 
    @PutMapping("/threads/{id}")
    public String updateThread(@PathVariable String id, String title, Model model, HttpServletResponse response, HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "redirect:/login";
        }

        UUID uuid = UUID.fromString(id);

        try {
            Thread thread = this.threadService.get(uuid);

            thread.setTitle(title);
            this.threadService.update(thread, user);

        } catch (NotFoundException | NotAvailableException e) {
            return "redirect:/errors/notAvailable";
        } catch (PermissionLevelException e) {
            response.setStatus(HttpStatus.FORBIDDEN.value());
            model.addAttribute("error", "You don't have permission to do this");
            return "errors/notPermitted";
        }

        return "redirect:/threads/" + id;
    }


  
    @DeleteMapping("/threads/{id}")
    @ResponseBody
    public String deleteThread(@PathVariable String id, Model model, HttpServletResponse response, HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "Unauthorized";
        }
        try {
            threadService.delete(threadService.get(UUID.fromString(id), user), user);
        } catch (PermissionLevelException e) {
            model.addAttribute("error", e.getMessage());
            response.setStatus(HttpStatus.FORBIDDEN.value());
            return e.getMessage();
        } catch (NotFoundException | NotAvailableException e) {
            model.addAttribute("error", e.getMessage());
            response.setStatus(HttpStatus.NOT_FOUND.value());
            return e.getMessage();
        }

        return "";
    }

    @PostMapping("/threads/{id}/lock")
    public String lockThread(@PathVariable String id, Model model, HttpServletResponse response, HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "redirect:/login";
        }

        UUID uuid = UUID.fromString(id);

        try {
            Thread thread = this.threadService.get(uuid, user);
            this.threadService.lock(thread, user);
        } catch (NotFoundException | NotAvailableException e) {
            response.setStatus(HttpStatus.NOT_FOUND.value());
            model.addAttribute("error", e.getMessage());
            return "errors/notAvailable";
        } catch (PermissionLevelException e) {
            response.setStatus(HttpStatus.FORBIDDEN.value());
            model.addAttribute("error", e.getMessage());
            return "errors/notPermitted";
        }

        return "redirect:/threads/" + id;
    }
}
