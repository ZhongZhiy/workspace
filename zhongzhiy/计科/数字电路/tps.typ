#import "@preview/typsidian:0.0.1": *
#show: typsidian.with(
  theme: "light",
  title: "My Document",
  course: "CS4999",
  show-index: true,
  index-entry-list: (
    (
      key: "example",
      short: "An example index entry"
    ),
  )
)

#set text(fill: rgb("#%THEMECOLOR%"), size: %FONTSIZE%)
#set page(fill: rgb("#%BGCOLOR%"), width: %LINEWIDTH%)


#set page(
  heading:[slkfjlskf]
)


this is typst