const preview_btn = document.getElementById("preview-btn");
const preview_div = document.getElementById("preview-content");
const content_div = document.getElementById("content");
const md = window.markdownit({
    html: false,
    linkify: true,
    typographer: true,
    breaks: true
});
const prsm = window.Prism;
const strprs = window.S;
preview_btn.addEventListener("click", () => {
    preview_div.classList.toggle("hidden");
    content_div.classList.toggle("hidden");
    if (preview_btn.checked) {
        preview_div.innerHTML = md.render(content_div.value)
        prsm.highlightAllUnder(preview_div)
    }
})