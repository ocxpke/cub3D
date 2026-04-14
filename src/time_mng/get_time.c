#include "../../include/cub3d.h"

/**
 * @brief We obtain the total time passed since Epoch(When timer counter started)
 *
 * @note We transform seconds and microseconds obtained into miliseconds
 *
 * @return Total time passed since Epoch (In milliseconds)
 */
inline long long get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
