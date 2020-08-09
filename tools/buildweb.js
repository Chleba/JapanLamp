var fs = require("fs");
var uglifyjs = require("uglify-js");
var uglifycss = require("uglifycss");

var webPath = "../web/";

// -- JS MINIFY
var jsFiles = [
  "jquery.js",
  "popper.js",
  "bootstrap.min.js",
  "toggle.min.js",
  "reinvented-color-wheel.min.js",
  "main.js",
];
var minFiles = {};
for (var i = 0; i < jsFiles.length; i++) {
  minFiles[jsFiles[i]] = fs.readFileSync(webPath + jsFiles[i], "utf8");
}
console.log(jsFiles);
var uglifiedJS = uglifyjs.minify(minFiles);
if (uglifiedJS.error) {
  console.log(uglifiedJS.error);
} else {
  fs.writeFile(webPath + "main_release.min.js", uglifiedJS.code, function(err) {
    if (err) {
      console.log("ERROR", err);
    } else {
      console.log(
        "All files is minified and compressed in - main_release.min.js"
      );
    }
  });
}

// -- CSS MINIFY
var cssFiles = [
  "style.css",
  "reinvented-color-wheel.min.css",
  "bootstrap.min.css",
];
minFiles = {};
for (var i = 0; i < cssFiles.length; i++) {
  cssFiles[i] = webPath + cssFiles[i];
  // minFiles[cssFiles[i]] = fs.readFileSync(webPath + cssFiles[i], "utf8");
}
console.log(cssFiles);
// var uglifiedCSS = uglifycss.processFiles(minFiles);
var uglifiedCSS = uglifycss.processFiles(cssFiles);
fs.writeFile(webPath + "main_release.min.css", uglifiedCSS, function(err) {
  if (err) {
    console.log(err);
  } else {
    console.log(
      "All files is minified and compressed in - main_release.min.css"
    );
  }
});
