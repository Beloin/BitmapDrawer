# Bitmap drawer

A simple app using NCurses to draw and save a bitmap file using colors.

Uses the `#pack push(...)` and `#pack pop` to save a struct into a
file using direct cast to `*char`.

Example:
<div style="place-items: center; height: 100%;  width: 100%;">
<img src="draw_example.png" alt="Created bitmap">
</div>

Converts to
<div style="height: 200px; width: auto">
<img style="height: 100%; width: 100%; object-fit: contain" src="draw_example.bmp" alt="Saved Bitmap">
</div>

