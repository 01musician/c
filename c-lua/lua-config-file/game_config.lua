-- game_config.lua
config = {
    graphics = {
        resolution = { width = 1920, height = 1080 },
        fullscreen = false,
        vsync = true
    },
    input = {
        key_bindings = {
            move_forward = "W",
            move_backward = "S",
            strafe_left = "A",
            strafe_right = "D",
            jump = "Space"
        }
    },
    game = {
        difficulty = "normal",
        max_players = 4
    }
}

