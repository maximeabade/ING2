package dev.max.iloveskate.controller;

import dev.max.iloveskate.exceptions.AlreadyExistException;
import dev.max.iloveskate.exceptions.InvalidFormatException;
import dev.max.iloveskate.exceptions.NotFoundException;
import dev.max.iloveskate.exceptions.PermissionLevelException;
import dev.max.iloveskate.model.Tag;
import dev.max.iloveskate.model.Thread;
import dev.max.iloveskate.model.User;
import dev.max.iloveskate.service.TagService;
import dev.max.iloveskate.service.ThreadService;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.List;

@Controller
public class TagController {
    private final TagService tagService;
    private final ThreadService threadService;

    public TagController(TagService tagService, ThreadService threadService) {
        this.tagService = tagService;
        this.threadService = threadService;
    }

    /**
     * GET - Tag page mapping
     */
    @GetMapping("/tags/{id}")
    public String tag(@PathVariable("id") String id,
                      @RequestParam(defaultValue = "0", required = false) int page,
                      @RequestParam(defaultValue = "10", required = false) int size,
                      @RequestParam(name = "removed", required = false, defaultValue = "false") boolean removed,
                      Model model,
                      HttpServletRequest request) {
        User user = (User) request.getSession().getAttribute("user");

        try {
            Tag tag = tagService.get(id);
            List<Thread> threads = threadService.getAllByTag(tag, 0, 10, false, user);
            request.setAttribute("pageTitle", tag.getDisplayName());
            request.setAttribute("pageSubTitle", tag.getDescription());
            request.setAttribute("nbPages", threadService.getNumberOfPagesByTag(tag, size, removed, null));
            request.setAttribute("currentPage", page);
            request.setAttribute("pageSize", size);
            request.setAttribute("threads", threads);
            return "content/explore";
        } catch (NotFoundException e) {
            model.addAttribute("error", e.getMessage());
            return "errors/notAvailable";
        } catch (PermissionLevelException e) {
            model.addAttribute("error", e.getMessage());
            return "errors/notPermitted";
        }
    }

    /**
     * POST - Create a new tag
     */
    @PostMapping("/tags")
    @ResponseBody
    public String createTag(String id, String name, String description, HttpServletResponse response, HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "redirect:/login";
        }

        Tag tag = new Tag();
        tag.setId(id);
        tag.setDescription(description);
        tag.setDisplayName(name);

        try {
            tagService.save(tag, user);

        } catch (AlreadyExistException | InvalidFormatException e) {
            response.setStatus(HttpStatus.NOT_ACCEPTABLE.value());
            return e.getMessage();
        } catch (PermissionLevelException e) {
            response.setStatus(HttpStatus.FORBIDDEN.value());
            return "redirect:/error";
        }

        return "";
    }

    /**
     * PUT - Update a tag
     */
    @PutMapping("/tags/{id}")
    @ResponseBody
    public String updateTag(@PathVariable String id,
                            @RequestParam(required = false, defaultValue = "") String name,
                            @RequestParam(required = false, defaultValue = "") String description,
                            Model model,
                            HttpServletResponse response,
                            HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "redirect:/login";
        }


        try {
            Tag tag = tagService.get(id);
            tag.setDescription(description);
            tag.setDisplayName(name);
            tagService.update(tag, user);
        } catch (PermissionLevelException e) {
            response.setStatus(HttpStatus.FORBIDDEN.value());
            return e.getMessage();
        } catch (NotFoundException e) {
            response.setStatus(HttpStatus.NOT_FOUND.value());
            return e.getMessage();
        }

        return "";
    }

    /**
     * DELETE - Delete a tag
     */
    @DeleteMapping("/tags/{id}")
    @ResponseBody
    public String deleteTag(@PathVariable String id, HttpServletResponse response, HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.setStatus(HttpStatus.UNAUTHORIZED.value());
            return "redirect:/login";
        }


        try {
            Tag tag = tagService.get(id);
            tagService.delete(tag, user);
        } catch (PermissionLevelException e) {
            response.setStatus(HttpStatus.FORBIDDEN.value());
            return "redirect:/error";
        } catch (NotFoundException e) {
            response.setStatus(HttpStatus.NOT_FOUND.value());
            return "redirect:/tags";
        }

        return "";
    }

    @GetMapping("/tags")
    public String manageTags(Model model, HttpSession session) {
        User user = (User) session.getAttribute("user");
        if (user == null) {
            return "redirect:/login";
        }
        if (!user.isAdmin()) {
            return "errors/notPermitted";
        }

        try {
            List<Tag> tags = tagService.getAll(0, 1000, user);
            model.addAttribute("tags", tags);
            return "content/admin_edit_tags";
        } catch (PermissionLevelException e) {
            return "errors/notPermitted";
        }
    }
}
