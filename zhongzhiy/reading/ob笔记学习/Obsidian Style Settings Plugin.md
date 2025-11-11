# Obsidian Style Settings Plugin

This plugin allows snippet, theme, and plugin CSS files to define a set of configuration options. It then allows users to see all the tweakable settings in one settings pane. Style Settings allows both toggling classes on and off the `body` element, as well as setting numeric, string, and color CSS variables.

**[This CSS Snippet](app://obsidian.md/obsidian-default-theme.css) can be used to adjust every CSS variable of the default Obsidian theme.**

Configurable settings are defined by comments within CSS files beginning with `/* @settings`. These comments must contain YAML with `name`, `id`, and `settings` properties. Style Settings will scan for these comments in all CSS loaded by Obsidian from the `snippets`, `themes`, and `plugins` directories under your vault's configuration directory (`%yourVault%/.obsidian/`). Please see the [Obsidian Docs](https://help.obsidian.md/Home) for more information.

For example, adding this to a CSS snippet in your vault's snippets directory (`%yourVault%/.obsidian/snippets`):

```css
/* @settings

name: Your Section Name Here
id: a-unique-id
settings:
    - 
        id: my-title
        title: My Settings
        type: heading
        level: 3
    - 
        id: accent
        title: Accent Color
        type: variable-color
        format: hsl-split
        default: '#007AFF'
    - 
        id: text
        title: UI font
        description: Font used for the user interface
        type: variable-text
        default: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Oxygen-Sans, Ubuntu, Cantarell, "Helvetica Neue", sans-serif

*/
```

will result in:

![Example output of plugin](https://raw.githubusercontent.com/mgmeyers/obsidian-style-settings/main/screenshots/example01.png)

Each setting definition must be separated by a dash (`-`). There are 7 setting types.

All settings definitions must have these parameters:

- `id`: A unique id for the setting parameter
- `title`: The name of the setting
- `description` (optional): a description of the setting
- `type`: The type of setting. Can be one of:
    - `heading`: a heading element for organizing settings
    - `class-toggle`: a switch to toggle classes on the `body` element
    - `class-select`: a dropdown menu of predefined options to add classes on the `body` element
    - `variable-text`: a text-based CSS variable
    - `variable-number`: a numeric CSS variable
    - `variable-number-slider`: a numeric CSS variable represented by a slider
    - `variable-select`: a text-based CSS variable displayed as a dropdown menu of predefined options
    - `variable-color`: a color CSS variable with corresponding color picker

## `heading`

`heading`s can be used to organize and group settings into collapsable nested sections. Along with the required attributes, `heading`s must contain a `level` attribute between `1` and `6`, and can optionally contain a `collapsed` attribute:

```css
/* @settings

name: Your Section Name Here
id: a-unique-id
settings:
    - 
        id: this-is-a-heading
        title: My Heading
        type: heading
        level: 2
        collapsed: true

*/
```

## `info-text`

`info-text` displays arbitrary informational text to users. The `description` may contain markdown if `markdown` is set to `true`.

```css
/* @settings

name: Your Section Name Here
id: a-unique-id
settings:
```