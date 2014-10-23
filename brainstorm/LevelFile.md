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

  `b <entity id> <x> <y> <width> <height>`

- Specify a static sprite with collision:

  `s <entity id> <image> <x> <y> <width> <height>`

- Specify a static sprite without collision:

  `S <entity id> <image> <x> <y> <width> <height>`

- Specifies a condition for a trigger to occur:

  `c <trigger id> <condition> <arg ...>`

- Specifies a result of the pulling of a trigger

  `r <trigger id> <result> <arg ...>`

Trigger Conditions
------------------

`x-before <value>` occurs when the x position of the player is greater than the given value.
`x-after <value>` occurs when the x position of the player is less than the given value.
`y-before <value>` occurs when the y position of the player is greater than the given value.
`y-after <value>` occurs when the y position of the player is less than the given value.
`can-see <x> <y>` occurs when the player can see the point given.
`timer <time>` occurs after some time elapse

Trigger Results
---------------

`top-dialogue` display uninterrupting dialogue to the top of the screen.
`dialogue` displays interrupting dialogue to the bottom of the screen, the arg looks like "speaker:text".
`complete-level` completes the level.
`cutscene` enables cutscene mode.
`gameplay` enables gameplay mode.
`delta <entity id> <delta-x> <delta-y>` sets the delta for the entity.
`enable` enables a trigger.
`disable` disables a trigger.
`remove` removes a trigger (cannot be reanabled).
