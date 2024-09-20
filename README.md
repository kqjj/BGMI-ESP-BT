# PUBG Game Enhancement (ESP, Aimbot, Bullet Track, Safe Zone Prediction)

![Menu Screenshot](images/menu-screenshot.png)

This project is a standalone executable designed to enhance PUBG Mobile with features like player ESP, bullet tracking, aimbot, safe zone prediction, enemy visibility checks, item ESP, and an intuitive ImGui menu for easy configuration.

## Features

- **Player ESP**: Displays the location of enemies on the screen with color-coded distance indicators.
- **Bullet Track**: Allows bullets to track enemies, with customizable hit percentage and legit tracking for random bone hit positions.
- **Aimbot with Bullet Rotation**: Automatically adjusts aim and bullet trajectory towards enemies.
- **Safe Zone Prediction**: Predicts and highlights the future safe zone to help with strategic movement.
- **Enemy Visibility Check**: Aimbot will only target visible enemies, avoiding obstacles like walls.
- **Item ESP**: Displays the location of lootable items such as weapons, armor, and medical supplies.
- **ImGui Menu**: An intuitive in-game menu for configuring features such as ESP, aimbot settings, bullet tracking, and more.

## Setup Instructions

### Install Dependencies:
Ensure you have the required DirectX or OpenGL libraries installed.

### Compile the Project:

1. **Open the project in Visual Studio.**
2. **Set the configuration to `Release`.**
3. **Build the solution** to generate the `.exe` file.

### Run the Executable:

1. Start PUBG Mobile using your emulator or directly on PC.
2. Run the compiled executable with **Administrator** privileges.
3. The executable will automatically detect the game window (`TXGuiFoundation` for window class, `Gameloop(64beta)` for window name).

### In-Game Usage:

- Once the executable is running, the **ImGui menu** will appear in the game, allowing you to toggle features like ESP, Aimbot, Bullet Tracking, and Safe Zone Prediction.
- You can configure the bullet track hit percentage and random bone hit behavior from the menu.

## Usage

- **Player ESP**: Shows the positions of enemies, color-coded by distance and visibility status.
- **Item ESP**: Highlights important items such as weapons, armor, and health packs.
- **Aimbot**: Automatically aims at enemies within a set FOV and rotates bullets towards them for more accurate shots.
- **Bullet Track**: Tracks enemy positions with customizable hit percentage and legit random bone targeting.
- **Safe Zone Prediction**: Displays the predicted safe zone location, helping you stay within the circle.
- **Enemy Visibility Check**: Ensures the aimbot only targets visible enemies that are not obstructed by walls or other objects.

### Bullet Track Settings

- **Hit Percentage**: Adjust the likelihood of bullets hitting a target. Higher percentages result in more accurate hits, while lower percentages simulate more "legit" behavior.
- **Legit Tracking**: Randomly selects bones on enemies (such as the head, torso, arms, or legs) to hit, making the aimbot harder to detect.
- **Random Bone Hit**: You can customize how often hits will target random bones, adding a level of unpredictability to aiming.

## ImGui Menu

The in-game menu allows you to customize settings in real-time:

- **ESP Options**: Toggle player and item ESP, and configure colors.
- **Aimbot Settings**: Adjust aim speed, FOV, smoothness, and bullet rotation.
- **Bullet Track Settings**: Configure hit percentage and enable/disable legit tracking with random bone targeting.
- **Safe Zone Prediction**: Toggle safe zone prediction On/Off.
- **Visibility Check**: Enable/Disable visibility check to avoid shooting through walls.

## Hotkeys

- `F1` - Toggle ESP On/Off
- `F2` - Enable/Disable Aimbot
- `F3` - Activate Bullet Track
- `F4` - Toggle Safe Zone Prediction
- `F5` - Toggle Visibility Check

## Configuration

The project includes an external configuration file or allows for dynamic changes through the ImGui menu to adjust:

- **ESP Colors**: Customize the colors for enemies, items, and visibility status.
- **Aimbot Settings**: Fine-tune parameters like FOV, aim speed, and smoothness.
- **Bullet Track Settings**: Configure hit percentage, legit tracking, and random bone targeting frequency.
- **Safe Zone Prediction**: Modify the behavior of the safe zone indicator.
- **Visibility Check Parameters**: Adjust how obstacles and walls are factored into visibility checks.

## Contributing

Contributions are welcome! You can fork the repository, improve existing features, or add new ones. Suggestions for enhancements include:

- Improving aimbot accuracy and legit play
- Adding more prediction algorithms (such as advanced enemy movement prediction)
- Refining the random bone targeting system in Bullet Track

## Disclaimer

This project is for educational purposes only. Modifying games with cheats may violate their terms of service and can result in bans. Use the software at your own risk.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
