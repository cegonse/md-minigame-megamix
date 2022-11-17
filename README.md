# md-minigame-megamix

Mega Drive Minigame Megamix Vol. 1

A collection of Mega Drive mini-games created by the MEGADRIVE DEV Telegram community

# Toolchain

- [SGDK v1.70](https://github.com/Stephane-D/SGDK)

# Building

Using Linux / macOS

- Run `make`
- Output file is `out/rom.bin`

# License and authors

All code, graphics, music and any other assets are property of their respective authors.

| Minigame | Authors |
|----------|---------|
| Slipstream | [moon-watcher](https://github.com/moon-watcher) |
| SDK | [cegonse](https://github.com/cegonse), [paspallas](https://github.com/paspallas), [moon-watcher](https://github.com/moon-watcher) |

# Contributing

If you are going to contribute occasionally:

1. Fork the repository.
2. Add your minigame code in `src/minigames/<minigame-folder-name>`
3. Add your binary resources in `data/<minigame-folder-name>`
4. Define the resources in `res/<minigame-name>.res`
5. Register your minigame in `src/minigames_registry.h` (check the file comments for instructions)
6. Create a pull request with your mini game
7. When merged, the mini game will automatically show up in the menu

If you want to become a maintainer, join us in Telegram MEGADRIVE DEV
