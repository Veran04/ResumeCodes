// code taken from https://blog.shhdharmen.me/toggle-light-and-dark-themes-in-bootstrap?guid=none&deviceId=3c98155c-dfb2-4b71-be7f-a0ebb588a609

// you can use app's unique identifier here
const LOCAL_STORAGE_KEY = "toggle-bootstrap-theme";

const LOCAL_META_DATA = JSON.parse(localStorage.getItem(LOCAL_STORAGE_KEY));

// you can change this url as needed
const DARK_THEME_PATH = "https://bootswatch.com/4/cyborg/bootstrap.min.css";

const DARK_FIX_PATH = "../css/stylesDark.css";

const DARK_STYLE_LINK = $("#dark-theme-style");

const DARK_FIX_LINK = $("#dark-fix-style");

const THEME_TOGGLER = $("#theme-toggler");

let isDark = LOCAL_META_DATA && LOCAL_META_DATA.isDark;

// check if user has already selected dark theme earlier
if (isDark) {
    enableDarkTheme();
} else {
    disableDarkTheme();
}

/**
 * Apart from toggling themes, this will also store user's theme preference in local storage.
 * So when user visits next time, we can load the same theme.
 *
 */
function toggleTheme() {
    isDark = !isDark;
    if (isDark) {
        enableDarkTheme();
    } else {
        disableDarkTheme();
    }
    const META = {
        isDark,
    };
    localStorage.setItem(LOCAL_STORAGE_KEY, JSON.stringify(META));
}

function enableDarkTheme() {
    DARK_STYLE_LINK.attr("href", DARK_THEME_PATH);
    DARK_FIX_LINK.attr("href", DARK_FIX_PATH);
    var page = window.location.pathname.split("/").pop();
    if (page === "main.html") {
        THEME_TOGGLER.html("Light <i class='fas fa-sun'></i>"); // 🌞
    }
}

function disableDarkTheme() {
    DARK_STYLE_LINK.attr("href", "");
    DARK_FIX_LINK.attr("href", "");
    var page = window.location.pathname.split("/").pop();
    if (page === "main.html") {
        THEME_TOGGLER.html("Dark <i class='fas fa-moon'></i>"); // 🌙
    }
}
