# Bitmap drawer

A simple app using NCurses to draw and save a bitmap file using colors.

Uses the `#pack push(...)` and `#pack pop` to save a struct into a
file using direct cast to `*char`.

Example:

<div style="display: grid; grid-template-columns: 1fr 1fr 1fr; column-gap: 20px; place-items: center;">
<img src="draw_example.png" alt="Created bitmap">
<img src="draw_example.bmp" alt="Saved Bitmap">
</div>

