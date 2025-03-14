Voronoi Diagram
====================================================
Vicente Javier Viera Guízar

[Documentation](docs/Introduction.md)

#### Notes for future me :P
##### App Context
I made A weird move in the app context to manage ImGui components. The components need to be informed about the app context, instead of the app context noticing the ImGui components. This would be an implementation of the Observer pattern. I did not noticed this until I finished the app setting, so fixing it would have needed a painful rework of the hole ImGui logic. Just a reminder to address this mistake in future projects.