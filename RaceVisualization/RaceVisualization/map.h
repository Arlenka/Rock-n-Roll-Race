#include <vector>

class Map
{
	Map(std::vector<std::vector<int>> map_data);
	OpenGLObject get_map();

private:
	std::vector<std::vector<int>> map; // TODO ����� ��� ������� �� � ���� 2������� �������?
};