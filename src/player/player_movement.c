#include "../../include/cub3d.h"

void move_forward(t_game *game_wrap, t_player *player_info)
{
	int nextX = (player_info->posX + player_info->dirX + (0.25 * player_info->look_ns));
	int nextY = (player_info->posY + player_info->dirY + (0.25 * player_info->look_ns));
	if (game_wrap->map[(int)player_info->posY][nextX] == '0')
		player_info->posX += player_info->dirX;
	if (game_wrap->map[nextY][(int)player_info->posX] == '0')
		player_info->posY += player_info->dirY;
}

void move_backwards(t_game *game_wrap, t_player *player_info)
{
	int nextX = (player_info->posX - (player_info->dirX + (0.25 * player_info->look_ns)));
	int nextY = (player_info->posY - (player_info->dirY + (0.25 * player_info->look_ns)));
	if (game_wrap->map[(int)player_info->posY][nextX] == '0')
		player_info->posX -= player_info->dirX;
	if (game_wrap->map[nextY][(int)player_info->posX] == '0')
		player_info->posY -= player_info->dirY;
}

// Esta mierda esta mal
void move_to_left(t_game *game_wrap, t_player *player_info)
{
	int nextX = (player_info->posX + player_info->dirY + (0.25 * player_info->look_ew));
	int nextY = (player_info->posY - (player_info->dirX + (0.25 * player_info->look_ew)));
	if (game_wrap->map[(int)player_info->posY][nextX] == '0')
		player_info->posX += player_info->dirY;
	if (game_wrap->map[nextY][(int)player_info->posX] == '0')
		player_info->posY -= player_info->dirX;
}

//Esta otra mierda tambien
void move_to_right(t_game *game_wrap, t_player *player_info)
{
	int nextX = (player_info->posX - (player_info->dirY + (0.25 * player_info->look_ew)));
	int nextY = (player_info->posY + player_info->dirX + (0.25 * player_info->look_ew));
	if (game_wrap->map[(int)player_info->posY][nextX] == '0')
		player_info->posX -= player_info->dirY;
	if (game_wrap->map[nextY][(int)player_info->posX] == '0')
		player_info->posY += player_info->dirX;
}
