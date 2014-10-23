The level file will be a series of commands that specify the elements of the level.

The level commands are structured as follows:

`C <arg1> <arg2> ...`

Where C is a character specifying the command to use, and arg1, arg2, and so forth are arbitrary length strings.

The ids should be unique.

Commands
--------

- Commenting:

  `# this is a comment`

- Specify the coordinates of an invisible bounding box:

  `b <id> <x> <y> <width> <height>`

- Specify a static sprite with collision:

  `s <id> <image> <x> <y> <width> <height>`

- Specify a static sprite without collision:

  `S <id> <image> <x> <y> <width> <height>`
