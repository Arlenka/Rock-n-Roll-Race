#include <vector>

class Map
{
	Map(std::vector<std::vector<int>> map_data);
	OpenGLObject get_map();

private:
	std::vector<std::vector<int>> map; // TODO может тут хранить не в виде 2мерного массива?
};